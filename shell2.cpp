/*
 * shell2.cpp
 *
 *  Created on: 2017年6月22日
 *      Author: zzzzzzzzzzz
 */

#include "shell2.h"
#include <cstdarg>
#include "keyword.h"
#include "util.h"
#include "ret.h"

extern std::string null_;

extern "C" {

void mk_suidao__(Qv *qv, const char *name, unsigned long fnaddr, int ret, size_t argc, ...) {
	std::string code = keyword::CALL + keyword::TEXT_BEGIN + "/" + std::to_string(fnaddr) + "/";
	switch(ret) {
	case 1: case 'a':
		code += "-A-S-$ce";
		break;
	case 2: case 'v':
		code += "-V";
		break;
	default:
		code += "-R";
		break;
	}
	code += "-$qv";
	{
		va_list argv;
		va_start(argv, argc);
		for (size_t i = 0; i < argc; ++i)
			code += "-&";
		code += "-Z" + keyword::TEXT_END;
		for (size_t i = 0; i < argc; ++i)
			code += keyword::DUNHAO + keyword::TEXT_BEGIN + std::to_string(va_arg(argv, unsigned long)) + keyword::TEXT_END;
		va_end(argv);
	}
	code += keyword::DUNHAO + keyword::VAR_BEGIN + keyword::ARGS + keyword::VAR_END + keyword::JUHAO;
	qv->def_get2__(name, SIZE_MAX)->val_ = code;
}

void ret_push__(Ret *ret, const char *s, bool one) {
	if(one)
		ret->one__();
	ret->push__(s ? s : null_);
}

}
