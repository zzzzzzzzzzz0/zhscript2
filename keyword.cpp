/*
 * keyword.cpp
 *
 *  Created on: 2016年8月20日
 *      Author: zzzzzzzzzzz
 */

#include "keyword.h"
#include "util.h"

namespace keyword {

const Item
	NO = {"", Id::No},
	TEXT_BEGIN = {"“", Id::TextBegin},
	TEXT_END   = {"”", Id::TextEnd},
	VAR_BEGIN = {"‘", Id::VarBegin},
	VAR_END   = {"’", Id::VarEnd},
	REM_BEGIN = {"（", Id::RemBegin},
	REM_END   = {"）", Id::RemEnd},
	TAG_BEGIN = {"【", Id::TagBegin},
	TAG_END   = {"】", Id::TagEnd},
	JUHAO = {"。", Id::Juhao},
	MAOHAO = {"：", Id::Maohao},
	DUNHAO  = {"、", Id::Dunhao},
	DUNHAO2 = {"为", Id::Dunhao},
	BEGIN = {"先", Id::Begin},
	END   = {"了", Id::End},

	CODE_BEGIN = {"下代码", Id::CodeBegin},
	CODE_END   = {"上代码", Id::CodeEnd},
	YUANYANG_BEGIN = {"下原样", Id::YuanyangBegin},
	YUANYANG_END   = {"上原样", Id::YuanyangEnd},

	DENGYU = {"等于", Id::Dengyu},
	XIAOYUDENGYU = {"小于等于", Id::Xiaoyudengyu},
	XIAOYU = {"小于", Id::Xiaoyu},
	DAYUDENGYU = {"大于等于", Id::Dayudengyu},
	DAYU = {"大于", Id::Dayu},
	NOT = {"不", Id::Not},
	AND = {"并且", Id::And},
	OR = {"或者", Id::Or},
	IF = {"如果", Id::If},
	THEN = {"那么", Id::Then},
	ELSE = {"否则", Id::Else},

	EXIT = {"结束", Id::Exit},
	RETURN = {"退出", Id::Return},

	FOR = {"循环", Id::For},
	BREAK = {"跳出", Id::Break},
	CONTINUE = {"再来", Id::Continue},

	RANGE = {"范围", Id::Range},
	BREAK2 = {"遁出", Id::Break2},
	CONTINUE2 = {"重来", Id::Continue2},

	SET = {"赋予", Id::Set},
	EQU = {"以", Id::Equ},
	TOP = {"顶", Id::Top},
	UP = {"上", Id::Up},
	PRIV = {"私", Id::Priv},

	DEF = {"定义", Id::Def},
	NO_ARG = {"无参", Id::Noarg},
	QIAN_ARG = {"倒挂", Id::Qianarg},

	ALIAS = {"别名", Id::Alias},
	HAS = {"存在", Id::Has},

	NAME = {"命名", Id::Name},
	MOD = {"模块", Id::Mod},

	DL = {"函数集", Id::Dl},
	FUNC = {"函数", Id::Func},
	CALL = {"调用", Id::Call},

	EVAL = {"算术", Id::Eval},

	EVAL2 = {"解释", Id::Eval2},
	LOAD = {"加载", Id::Load},

	PRINT = {"显示", Id::Print},
	EXEC = {"执行", Id::Exec},

	ARG = {"参数", Id::Arg},
	ARGS = {"参数栈", Id::Args},
	LENGTH = {"数目", Id::Length},

	CR = {"回车", Id::Cr},
	LF = {"换行", Id::Lf},
	TAB = {"制表符", Id::Tab},
	ESC = {"ESC", Id::Esc};

const Item *ALL[] = {
		&EVAL2,
		&CALL,
		&PRINT, &EXEC,
		&BEGIN, &END,
		&VAR_BEGIN,
		&JUHAO,
		&MAOHAO,
		&DUNHAO, &DUNHAO2,
		&TEXT_BEGIN,
		&CODE_BEGIN,
		&YUANYANG_BEGIN,
		&CR, &LF, &TAB, &ESC,
		&FOR, &BREAK, &CONTINUE,
		&RANGE, &BREAK2, &CONTINUE2,
		&RETURN,
		&IF, &THEN, &ELSE,
		&EVAL,
		&SET, &DEF, &ALIAS, &EQU,
		&HAS,
		&TAG_BEGIN,
		&LOAD,
		&EXIT,
		&DL, &FUNC,
		&NAME, &MOD,
		&REM_BEGIN,
	};

const List
	ALL_JUHAO = {&JUHAO},
	ALL_IF = {
		&DENGYU, &XIAOYUDENGYU, &XIAOYU, &DAYUDENGYU, &DAYU,
		&NOT, &AND, &OR,
	};

const Item *get__(const std::string &s, size_t i, size_t &kw_len, Id kw_by) {
	auto fn = [&](auto i2) {
		return startswith__(s, i, i2->val_, kw_len);
	};
	switch(kw_by) {
	case Id::RemBegin:
		for(auto i2 : {&REM_BEGIN, &REM_END})
			if(fn(i2))
				return i2;
		break;
	case Id::YuanyangBegin:
		for(auto i2 : {&YUANYANG_BEGIN, &YUANYANG_END})
			if(fn(i2))
				return i2;
		break;
	case Id::CodeBegin:
		for(auto i2 : {&CODE_BEGIN, &CODE_END, &YUANYANG_BEGIN, &YUANYANG_END, &TEXT_BEGIN, &TEXT_END})
			if(fn(i2))
				return i2;
		break;
	case Id::TextBegin:
		for(auto i2 : {&TEXT_BEGIN, &TEXT_END, &VAR_BEGIN, &VAR_END})
			if(fn(i2))
				return i2;
		break;
	case Id::VarBegin: case Id::TagBegin:
		for(auto i2 : {&VAR_BEGIN, &VAR_END, &TAG_BEGIN, &TAG_END})
			if(fn(i2))
				return i2;
		break;
	default:
		switch(kw_by) {
		case Id::If:
			for(auto i2 : ALL_IF)
				if(fn(i2))
					return i2;
			break;
		default:
			break;
		}
		for(auto i2 : ALL)
			if(fn(i2))
				return i2;
		break;
	}
	return nullptr;
}

const Item* has__(const Id kw, const List *all_kw) {
	if(all_kw) {
		for(auto i : *all_kw)
			if(*i == kw)
				return i;
	}
	return nullptr;
}

} /* namespace keyword */
