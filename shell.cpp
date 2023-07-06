/*
 * l4.cpp
 *
 *  Created on: 2016年10月2日
 *      Author: zzzzzzzzzzz
 */

#include <cstdarg>

#include "lib.h"
#include "segm/func/old.h"
#include "shell.h"

extern std::string null_;
std::string callback_ = "回调";

extern "C" {

void* l4_new__() {
	return new Lib();
}

void l4_delete__(void* l4) {
	delete (Lib*)l4;
}

void l4_cmdline_parse__(void* l4, int argc, const char** argv) {
	((Lib*)l4)->cmdline_parse__(argc, argv, 1);
}
void l4_cmdline_parse2__(Lib* l4, const char* cmdline) {
	l4->cmdline_parse__(cmdline);
}

bool l4_has_src__(void* l4) {
	return ((Lib*)l4)->has_src__();
}

int l4_exit_code__(void* l4) {
	return ((Lib*)l4)->ls__()->exit_code_;
}
bool l4_is_end__(void* l4) {
	return ((Lib*)l4)->ls__()->is_exit_;
}

Qv* l4_new_main_qu__(Lib* l4) {
	return l4->new_main_qu__();
}

const char* l4_err__(void* l4) {
	return ((Lib*)l4)->ls__()->err_.c_str();
}

void l4_set_path__(Lib* l4, const char* s) {
	l4->set_path__(s);
}

void l4_add_path__(const char* s) {

}
void l4_del_path__(const char* s) {

}

void l4_add_arg3__(Lib* l4, int argc, const char** argv, int from) {
	l4->cmdline_parse__(argc, argv, from);
}

void l4_add_arg__(Lib* l4, const char* cmdline) {
	std::string s = cmdline, s2 = "-S syn-zh -E err-zh";
	size_t pos = s.find(s2);
	if(pos != std::string::npos)
		s.replace(pos, pos + s2.length(), "");
	l4->cmdline_parse__(s);
}

int l4_parse_args__(void* l4) {
	return 0;
}

void l4_go__(Lib* l4, int kw) {

}

int ex_var_new__(::segm::List* jsq, Qv* qu, const char* name, const char* val, bool readonly, int type, bool is_noparam);
int l4_var_new__(Lib* l4,Qv* qu,const char* name,const char* val,bool readonly,int type,bool is_noparam) {
	switch(type) {
	case vartype_def_:
	{
		unsigned long suidao, thi;
		const std::string fmt = keyword::CALL
				+ keyword::TEXT_BEGIN + "ASZ/%lx/&-$11-&" + keyword::TEXT_END + keyword::DUNHAO
				+ keyword::TEXT_BEGIN + "%lx" + keyword::TEXT_END + keyword::DUNHAO
				+ keyword::VAR_BEGIN
				+ keyword::TAG_BEGIN + keyword::UP + keyword::TAG_END
				+ callback_ + "1"
				+ keyword::VAR_END + keyword::DUNHAO
				+ keyword::VAR_BEGIN + keyword::ARGS + keyword::VAR_END + keyword::JUHAO;
		if(sscanf(val, fmt.c_str(), &suidao, &thi) == 2) {
			qu->def_get2__(name, is_noparam ? 0 : SIZE_MAX)->val_ = keyword::CALL + keyword::BEGIN
					+ keyword::FUNC + keyword::EQU
					+ keyword::TEXT_BEGIN + "&" + keyword::TEXT_END + keyword::DUNHAO
					+ keyword::TEXT_BEGIN + std::to_string(suidao) + keyword::TEXT_END + keyword::DUNHAO
					+ keyword::TEXT_BEGIN + "-A-S-&-$11-$14-Z" + keyword::TEXT_END
					+ keyword::END + keyword::DUNHAO
					+ keyword::TEXT_BEGIN + std::to_string(thi) + keyword::TEXT_END + keyword::DUNHAO
					+ keyword::VAR_BEGIN + keyword::ARGS + keyword::VAR_END + keyword::JUHAO;
			return 0;
		}
		break;
	}
	}
	return ex_var_new__(l4->ls__(), qu, name, val, readonly, type, is_noparam);
}

const char* l4_keyword__(Lib* l4,int kw) {
	switch(kw) {
	case keyword_null_:
		return null_.c_str();
	case keyword_call_:
		return keyword::CALL.val_.c_str();
	case keyword_kaiyinhao_:
		return keyword::TEXT_BEGIN.val_.c_str();
	case keyword_biyinhao_:
		return keyword::TEXT_END.val_.c_str();
	case keyword_dunhao_:
		return keyword::DUNHAO.val_.c_str();
	case keyword_bianliangshi_:
		return keyword::VAR_BEGIN.val_.c_str();
	case keyword_bianliangzhong_:
		return keyword::VAR_END.val_.c_str();
	case keyword_params_:
		return keyword::ARGS.val_.c_str();
	case keyword_juhao_:
		return keyword::JUHAO.val_.c_str();
	case keyword_callback_:
		return callback_.c_str();
	case keyword_zhujieshi_:
		return keyword::TAG_BEGIN.val_.c_str();
	case keyword_zhujiezhong_:
		return keyword::TAG_END.val_.c_str();
	case keyword_shangji_:
		return keyword::UP.val_.c_str();
	case keyword_jieheshi_:
		return keyword::BEGIN.val_.c_str();
	case keyword_jiehezhong_:
		return keyword::END.val_.c_str();
	case -1:
		return keyword::FUNC.val_.c_str();
	case keyword_equ_:
		return keyword::EQU.val_.c_str();
	default:
		return nullptr;
	}
}

}
