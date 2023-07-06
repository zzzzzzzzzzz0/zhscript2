/*
 * main.cpp
 *
 *  Created on: 2016年8月19日
 *      Author: zzzzzzzzzzz
 */

#include "shell.h"
#include <iostream>
#include "debug.h"

void out__(const std::string &s) {
	o__(0, s, R"(\\\\)"); o_n__();
}

#define ret___ std::vector<std::string>

void z__(std::function<bool(ret___&)> fn, bool out_ret, void* l4) {
	ret___ ret;
	if(!fn(ret)) {
		if(l4_is_end__(l4))
			std::exit(l4_exit_code__(l4));
		o__(0, l4_err__(l4));
		o_n__();
		std::exit(255);
	}

	if(out_ret) {
		o_n__(); o_n__();
		out__("");
		for(auto s : ret) {
			out__(s);
		}
	}
}

int main(int argc, const char **argv) {
	void* l4 = l4_new__();
	l4_cmdline_parse__(l4, argc, argv);
	if(l4_has_src__(l4)) {
		z__([&](ret___& ret) {
			return l4_jieshi3__(l4, nullptr, &ret);
		}, debug_.o_ret_, l4);
	} else {
		for(;;) {
			o__(0, "////"); o_n__();
			std::string s;
			std::cin >> s;
			if(std::cin.eof())
				break;
			z__([&](ret___& ret) {
				return l4_jieshi4__(l4, s.c_str(), false, nullptr, nullptr, 0, nullptr, &ret);
			}, true, l4);
		}
	}
	//l4_delete__(l4);
	return l4_exit_code__(l4);
}

