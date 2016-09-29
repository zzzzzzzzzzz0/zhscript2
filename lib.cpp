/*
 * Lib.cpp
 *
 *  Created on: 2016年8月19日
 *      Author: zzzzzzzzzzz
 */

#include "lib.h"

#include "debug.h"
#include "segm/mod.h"
#include "buf.h"
#include "util.h"
#include "file.h"

const std::string shebang_flag_ = "--" + keyword::JUHAO;

void Lib::cmdline_parse__(int argc, const char** argv) {
	file_.known_path2_add__(argv[0]);
	for(int i = 1; i < argc; i++) {
		std::string s = argv[i];
		if(s == "-zhscript-x") {
			break;
		}
		if(s.length() > shebang_flag_.size()) {
			size_t pos = s.length() - shebang_flag_.size();
			if(s.rfind(shebang_flag_) == pos) {
				cmdline_parse__(s.substr(0, pos - 1));
				continue;
			}
		}
		cmdline_parse2__(s);
	}
	if(debug_.o_args_) debug_.o_args__(argc, argv, 1);
}
void Lib::cmdline_parse__(const std::string& s) {
	Buf buf([&](const std::string& val) {
		cmdline_parse2__(val);
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
void Lib::cmdline_parse2__(const std::string& s) {
	if(s == "----") {
		all_is_param_ = !all_is_param_;
		return;
	}
	if(all_is_param_) {
		args_.push__(s);
		return;
	}
	if(s == shebang_flag_) {
		return;
	}
	if(debug_.parse__(s)) {
		return;
	}
	if(s == "-zhscript-src-is-code") {
		args_.src_is_file_ = false;
		return;
	}
	if(startswith__(s, "-zhscript-")) {
		return;
	}
	args_.parse__(s);
}

Result2 Lib::z__(Ret &ret) {
	segm::List ls;
	return ls.z2__(keyword::NO, &args_, &ls.qv_top_, ret);
}

Result2 Lib::z__(const std::string &s, Ret &ret) {
	args_.src_ = s;
	args_.src_is_file_ = false;
	return z__(ret);
}
