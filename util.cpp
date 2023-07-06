/*
 * util.cpp
 *
 *  Created on: 2016年9月4日
 *      Author: zzzzzzzzzzz
 */

#include "util.h"

size_t step__(const std::string &s, size_t i, std::function<void(unsigned char c)> fn) {
	size_t step = 0;
	if(i < s.length()) {
		step++;
		if(fn)
			fn(s[i]);
	}
	for(i++;i < s.length(); i++) {
		unsigned char c = s[i];
		if((c & 0xc0) != 0x80) {
			break;
		}
		step++;
		if(fn)
			fn(c);
	}
	return step;
}

int startswith__(const std::string& s, size_t i, const std::string& s2, size_t &i2) {
	i2 = 0;
	for(;; i++, i2++) {
		if(i2 >= s2.length()) {
			return i2 == s.length() ? 1 : 2;
		}
		if(i >= s.length()) {
			break;
		}
		if(s[i] != s2[i2]) {
			break;
		}
	}
	return 0;
}
int startswith__(const std::string& s, const std::string& s2) {
	size_t i2;
	return startswith__(s, 0, s2, i2);
}

bool can_stoi__(const std::string &s, bool use_minus) {
	if(s.empty())
		return false;
	bool is = true, first = true;
	for(auto c : s) {
		if(!((c == '-' && first && use_minus) || std::isdigit(c))) {
			is = false;
			break;
		}
		if(first)
			first = false;
	}
	return is;
}

bool can_stod__(const std::string &s) {
	bool first = true;
	int i = 0, i2 = 0;
	for(auto c : s) {
		switch(c) {
		case '+': case '-':
			if(!first)
				return false;
			break;
		case '.':
			if(++i2 > 1)
				return false;
			break;
		default:
			if(!std::isdigit(c))
				return false;
			i++;
			break;
		}
		if(first)
			first = false;
	}
	return i;
}

std::string bad__(unsigned char c) {
	std::string ret;
	ret += "非法字符 ";
	if(std::isprint(c))
		ret += c;
	else
		ret += "ascii" + std::to_string(c);
	return ret;
}

#ifdef ver_no_std_to_string_
#include <sstream>
namespace std {

std::string to_string(unsigned char t) {
	std::ostringstream ss;
	ss << t;
	return ss.str();
}
std::string to_string(long t) {
	std::ostringstream ss;
	ss << t;
	return ss.str();
}
std::string to_string(unsigned long t) {
	std::ostringstream ss;
	ss << t;
	return ss.str();
}
std::string to_string(long double t) {
	std::ostringstream ss;
	ss << t;
	return ss.str();
}
std::string to_string(int t) {
	std::ostringstream ss;
	ss << t;
	return ss.str();
}
std::string to_string(unsigned int t) {
	std::ostringstream ss;
	ss << t;
	return ss.str();
}
int stoi(std::string s) {
	std::istringstream ss(s);
	int t = 0;
	ss >> t;
	return t;
}
long double stold(std::string s) {
	std::istringstream ss(s);
	long double t = 0;
	ss >> t;
	return t;
}
long stol(std::string s) {
	std::istringstream ss(s);
	long t = 0;
	ss >> t;
	return t;
}
unsigned long stoul(std::string s) {
	std::istringstream ss(s);
	unsigned long t = 0;
	ss >> t;
	return t;
}

}
#endif
