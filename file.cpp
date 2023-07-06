/*
 * file.cpp
 *
 *  Created on: 2016年9月1日
 *      Author: zzzzzzzzzzz
 */

#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include "file.h"
#include "debug.h"

#ifdef ver_no_fs_
#include <unistd.h>
#include <sys/stat.h>
bool exists__(const std::string &filename) {
	return access(filename.c_str(), F_OK) != -1;
}
bool is_symlink__(const std::string &filename) {
	struct stat buf;
	return lstat(filename.c_str(), &buf) == 0 && S_ISLNK(buf.st_mode);
}
std::string read_symlink__(const std::string &filename) {
	char buf[512] = "";
	readlink(filename.c_str() ,buf,512);
	return buf;
}
#elif ver_ex_file_get_
bool exists__(const std::string &filename);
bool is_symlink__(const std::string &filename);
std::string read_symlink__(const std::string &filename);
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#define exists__ fs::exists
#define is_symlink__ fs::is_symlink
#define read_symlink__ fs::read_symlink
#endif

#ifdef ver_ex_file_get_
std::string file_get__(const std::string& src);
std::string file_abs__(const std::string& src);
#endif

std::string File::abs__(const std::string& src) {
#ifdef ver_no_fs_
	char buf[512] = "";
	realpath(src.c_str(), buf);
	return buf;
#elif ver_ex_file_get_
	return file_abs__(src);
#else
	return fs::canonical(src);
#endif
}

std::string File::rel__(const std::string& src, const std::string& base, bool rm_ext) {
	std::string s;
	size_t pos = 0;
	for(size_t i = 0;; i++) {
		if(i >= base.size()) {
			pos = i;
			break;
		}
		if(i >= src.size()) {
			break;
		}
		if(src[i] == '/')
			pos = i + 1;
		if(src[i] != base[i]) {
			break;
		}
	}
	s = src.substr(pos);
	if(rm_ext) {
		pos = s.rfind('.');
		if(pos != std::string::npos)
			s = s.substr(0, pos);
	}
	return s;
}

std::string File::dir__(const std::string& src) {
	size_t pos = src.rfind('/');
	if(pos != std::string::npos)
		return src.substr(0, pos + 1);
	return "";
}

void File::get_contents__(const std::string& src, std::string& body, std::string& head) {
#ifdef ver_ex_file_get_
	const std::string& s = file_get__(src);
#else
	std::ifstream ifs(src);
	std::stringstream ss;
	ss << ifs.rdbuf();
	ifs.close();
	const std::string& s = ss.str();
#endif
	if(s.length() > 2 && s[0] == '#' && s[1] == '!') {
		size_t i = s.find('\n');
		if(i != std::string::npos) {
			body = s.substr(i + 1);
			head = s.substr(0, i);
		} else {
			body = s;
		}
	} else {
		body = s;
	}
}

void File::known_path2_add__(const std::string& src) {
	std::string dir = dir__(good_path__(src));
	if(std::find(known_path2_.begin(), known_path2_.end(), dir) == known_path2_.end())
		known_path2_.push_back(dir);
}

std::string File::good_path__(const std::string& src) {
	std::string src2;
	if(src.find('/') == std::string::npos) {
		char* env = std::getenv("PATH");
		if(env) {
			std::string env2 = env;
			for(size_t i = 0, i2; i < env2.size();) {
				i2 = env2.find(':', i);
				if(i2 == std::string::npos)
					i2 = env2.size();
				if(i < i2) {
					src2 = env2.substr(i, i2 - i) + "/" + src;
					if(exists__(src2))
						break;
				}
				i = i2 + 1;
			}
		} else
			src2 = src;
	} else
		src2 = src;
	src2 = abs__(src2);
	for(;is_symlink__(src2);) {
		std::string src3 = read_symlink__(src2);
		if(src3[0] != '/')
			src3 = dir__(src2) + src3;
		src2 = src3;
	}
	return src2;
}

std::string File::ok_path__(const std::string& src) {
	if(src.empty())
		return src;
	std::string src2;
	auto fn = [&](const std::string& s) {
		if(debug_.o_path_) {o__('n', s); o_n__();}
		try {
			if(exists__(s)) {
				src2 = s;
				return true;
			}
		} catch(...) {}
		return false;
	};
	if(src[0] == '/') {
		fn(src);
		return src2;
	}
	if(src[0] == '.') {
		if(fn(src))
			return src2;
	}
	for(auto dir : known_path2_) {
		if(fn(dir + src))
			return src2;
	}
	for(auto dir = known_path_.rbegin(); dir != known_path_.rend(); dir++) {
		if(fn(*dir + src))
			return src2;
	}
	if(fn(src))
		return src2;
	return src2;
}

