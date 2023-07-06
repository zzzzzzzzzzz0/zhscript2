/*
 * clpars.cpp
 *
 *  Created on: 2017年6月14日
 *      Author: zzzzzzzzzzz
 */

#include "clpars.h"
#include "keyword.h"
#include "debug.h"
#include "buf.h"
#include "util.h"

/*constexpr std::string shebang_flag_  = "--" + keyword::JUHAO,
                      shebang_flag2_ = "--" + keyword::JUHAO.val_en_;*/

void Clpars::z__(int argc, const char** argv, int from, arg::List& args) {
	for(int i = from; i < argc; i++) {
		std::string s = argv[i];
		if(s == "-zhscript-x") {
			break;
		}
		z2__(s, args);
	}
	if(debug_.o_args_) debug_.o_args__(argc, argv, 1);
}

void Clpars::z__(const std::string& s, arg::List& args) {
	Buf buf([&](const std::string& val) {
		z2__(val, args);
	}, [&](char c) {
		return true;
	});

	for(size_t i = 0; i < s.length(); i++) {
		char c = s[i];
		switch(c) {
		case ' ':
			buf.clear__();
			continue;
		case '"': case '\'':
			for(i++; i < s.length(); i++) {
				char c2 = s[i];
				if(c2 == c)
					break;
				buf.add__(c2);
			}
			continue;
		}
		buf.add__(c);
	}
	buf.clear__();
}

void Clpars::z2__(const std::string& s, arg::List& args) {
	if(s == "----") {
		all_is_param_ = !all_is_param_;
		return;
	}
	if(all_is_param_) {
		args.push__(s);
		return;
	}

	if(debug_.parse__(s)) {
		return;
	}
	if(s == "-zhscript-src-is-code") {
		args.src_is_file_ = false;
		return;
	}
	if(s == "-zhscript-en") {
		args.use_en_ = true;
		return;
	}

	std::string shebang_flag  = "--" + keyword::JUHAO,
	            shebang_flag2 = "--" + keyword::JUHAO.val_en_;
	{
		auto fn = [&](const std::string &s, const std::string &shebang_flag) {
			if(s.length() > shebang_flag.size()) {
				size_t pos = s.length() - shebang_flag.size();
				if(s.rfind(shebang_flag) == pos) {
					//z__(s.substr(0, pos - 1), args);
					return true;
				}
			}
			return false;
		};
		if(fn(s, shebang_flag) || (/*keyword::use_en_ && */fn(s, shebang_flag2)))
			return;
	}
	if(s == shebang_flag || (/*keyword::use_en_ && */s == shebang_flag2)) {
		return;
	}

	if(startswith__(s, "-zhscript-")) {
		return;
	}
	args.parse__(s);
}
