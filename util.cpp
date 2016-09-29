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

std::string bad__(unsigned char c) {
	std::string ret;
	ret += "非法字符 ";
	if(std::isprint(c))
		ret += c;
	else
		ret += "ascii" + std::to_string(c);
	return ret;
}
