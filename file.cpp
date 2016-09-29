/*
 * file.cpp
 *
 *  Created on: 2016年9月1日
 *      Author: zzzzzzzzzzz
 */

#include <fstream>
#include <sstream>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#include <algorithm>
#include <cstdlib>
#include "file.h"
#include "debug.h"

std::string File::abs__(const std::string& src) {
	return fs::canonical(src);
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

std::string File::get_contents__(const std::string& src) {
	std::ifstream ifs(src);
	std::stringstream ss;
	ss << ifs.rdbuf();
	ifs.close();
	const std::string& s = ss.str();
	if(s.length() > 2 && s[0] == '#' && s[1] == '!') {
		size_t i = s.find('\n');
		if(i != std::string::npos) {
			return s.substr(i + 1);
		} else {
			return s;
		}
	} else {
		return s;
	}
}

void File::known_path2_add__(const std::string& src) {
	std::string src2;
	if(src.find('/') == std::string::npos) {
		char* env = std::getenv("PATH");
		if(!env)
			return;
		std::string env2 = env;
		for(size_t i = 0, i2; i < env2.size();) {
			i2 = env2.find(':', i);
			if(i2 == std::string::npos)
				i2 = env2.size() - 1;
			if(i < i2) {
				src2 = env2.substr(i, i2 - i) + "/" + src;
				if(fs::exists(src2))
					break;
			}
			i = i2 + 1;
		}
	} else
		src2 = src;
	src2 = abs__(src2);
	for(;fs::is_symlink(src2);) {
		std::string src3 = fs::read_symlink(src2);
		if(src3[0] != '/')
			src3 = dir__(src2) + src3;
		src2 = src3;
	}
	std::string dir = dir__(src2);
	if(std::find(known_path2_.begin(), known_path2_.end(), dir) == known_path2_.end())
		known_path2_.push_back(dir);
}

std::string File::ok_path__(const std::string& src) {
	if(src.empty())
		return src;
	std::string src2;
	auto fn = [&](const std::string& s) {
		if(debug_.o_path_) {o__({s}, 'n'); o_n__();}
		if(fs::exists(s)) {
			src2 = s;
			return true;
		}
		return false;
	};
	if(fn(src))
		return src2;
	if(src[0] == '/') {
		fn(src);
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
	return src2;
}

File file_;
