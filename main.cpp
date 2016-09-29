/*
 * main.cpp
 *
 *  Created on: 2016年8月19日
 *      Author: zzzzzzzzzzz
 */

#include <iostream>
#include "lib.h"
#include "is.h"
#include "util.h"
#include "debug.h"

void out__(std::initializer_list<const char*> a) {
	o__(a/*, 'e'*/);
	o__({R"(\\\\)"}); o_n__();
}

void z__(std::function<Result2 (Ret&)> fn, bool out_ret) {
	Ret ret;
	{
		Result2 r2 = fn(ret);
		if(false__(r2)) {
			if(r2->val_->val_ == IS_EXIT) {
				const std::string &s = r2->val_->err_;
				if(s.empty()) {
					std::exit(0);
					return;
				}
				if(can_stoi__(s)) {
					std::exit(std::stoi(s));
					return;
				}
			}
			o__({r2->val_->err_, r2->err_}/*, 'E'*/);
			o_n__();
			return;
		}
	}
	ret.one__();

	if(out_ret) {
		o_n__(); o_n__();
		out__({});
		for(auto s : ret.a_) {
			out__({s.val_.c_str()});
		}
	}
}

int main(int argc, const char **argv) {
	Lib lib;
	lib.cmdline_parse__(argc, argv);
	if(lib.has_src__()) {
		z__([&](Ret& ret) {
			return lib.z__(ret);
		}, debug_.o_ret_);
	} else {
		for(;;) {
			o__({"////"}); o_n__();
			std::string s;
			std::cin >> s;
			if(std::cin.eof())
				break;
			z__([&](Ret& ret) {
				return lib.z__(s, ret);
			}, true);
		}
	}
	return 0;
}

