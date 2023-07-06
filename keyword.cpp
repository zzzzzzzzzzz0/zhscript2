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
	NO = {"", "", Id::No},
	TEXT_BEGIN = {"“", "(\"", Id::TextBegin},
	TEXT_END   = {"”", "\")", Id::TextEnd},
	VAR_BEGIN = {"‘", "$(", Id::VarBegin},
	VAR_END   = {"’", ")$", Id::VarEnd},
	REM_BEGIN = {"（", "/*", Id::RemBegin},
	REM_END   = {"）", "*/", Id::RemEnd},
	TAG_BEGIN = {"【", "[", Id::TagBegin},
	TAG_END   = {"】", "]", Id::TagEnd},
	JUHAO = {"。", ";", Id::Juhao, true},
	DOUHAO = {"，", "AND", Id::Douhao, true},
	MAOHAO = {"：", "->", Id::Maohao},
	DUNHAO  = {"、", ",", Id::Dunhao},
	DUNHAO2 = {"为", ":", Id::Dunhao},
	DUNHAO3  = {"隔", "sp", Id::Dunhao},
	BEGIN = {"先", "{", Id::Begin},
	END   = {"了", "}", Id::End},

	CODE_BEGIN = {"下代码", "BEGIN", Id::CodeBegin},
	CODE_END   = {"上代码", "END", Id::CodeEnd},
	YUANYANG_BEGIN = {"下原样", "('", Id::YuanyangBegin},
	YUANYANG_END   = {"上原样", "')", Id::YuanyangEnd},
	TEXT_BEGIN2 = {"下文本", "(`", Id::TextBegin2},
	TEXT_END2   = {"上文本", "`)", Id::TextEnd2},

	DENGYU = {"等于", "==", Id::Dengyu},
	XIAOYUDENGYU = {"小于等于", "<=", Id::Xiaoyudengyu},
	XIAOYU = {"小于", "<", Id::Xiaoyu},
	DAYUDENGYU = {"大于等于", ">=", Id::Dayudengyu},
	DAYU = {"大于", ">", Id::Dayu},
	NOT = {"不", "!", Id::Not},
	AND = {"并且", "&&", Id::And},
	OR = {"或者", "||", Id::Or},
	IF = {"如果", "IF", Id::If},
	THEN = {"那么", "THEN", Id::Then},
	ELSE = {"否则", "ELSE", Id::Else},

	SWITCH = {"分支", "SWITCH", Id::Switch},

	WITH = {"基于", "WITH", Id::With},

	EXIT = {"结束", "EXIT", Id::Exit},
	RETURN = {"退出", "RETURN", Id::Return},

	FOR = {"循环", "FOR", Id::For},
	BREAK = {"跳出", "BREAK", Id::Break},
	CONTINUE = {"再来", "CONTINUE", Id::Continue},

	RANGE = {"圈子", "RANGE", Id::Range},
	BREAK2 = {"遁出", "OUT", Id::Break2},
	CONTINUE2 = {"重来", "AGAIN", Id::Continue2},

	SET = {"赋予", "SET", Id::Set},
	EQU = {"以", "=", Id::Equ},
	TOP = {"顶", "top", Id::Top},
	UP = {"上", "up", Id::Up},
	PRIV = {"私", "priv", Id::Priv},
	VAL = {"值", "val", Id::Val},

	DEF = {"定义", "DEF", Id::Def},
	NO_ARG = {"无参", "noarg", Id::Noarg},
	NO_ARGC = {"不定", "noargc", Id::Noargc},
	BACK_ARG = {"倒挂", "backarg", Id::Backarg},
	THROUGH = {"穿透", "through", Id::Through},
	BY = {"前由", "by", Id::By},

	ALIAS = {"别名", "ALIAS", Id::Alias},
	HAS = {"存在", "HAS", Id::Has},

	NAME = {"命名", "NAME", Id::Name},
	MOD = {"模块", "MOD", Id::Mod},
	MOD_FREE = {"释放模块", "FREEMOD", Id::ModFree},

	DL = {"函数集", "FUNCS", Id::Dl},
	FUNC = {"函数", "FUNC", Id::Func},
	CALL = {"调用", "CALL", Id::Call},

	EVAL = {"算术", "EXPL", Id::Eval},

	EVAL2 = {"解释", "EVAL", Id::Eval2},
	LOAD = {"加载", "LOAD", Id::Load},

	PRINT = {"显示", "PRINT", Id::Print},
	EXEC = {"执行", "EXEC", Id::Exec},

	ARG = {"参数", "arg", Id::Arg},
	ARGS = {"参数栈", "args", Id::Args},
	LENGTH = {"数目", ".length", Id::Length},

	ATTR = {"属性", "attr", Id::Attr},
	QV = {"变量区", "vars", Id::Qv},
	RESERVED = {"保留字", "reserved", Id::Reserved},

	LF = {"回车", "LF", Id::Lf},
	CR = {"换行", "CR", Id::Cr},
	TAB = {"制表符", "TAB", Id::Tab},
	ESC = {"ESC", "ESC", Id::Esc},

	SYSTEM = {"窗口", "window", Id::System},
	SHELL = {"外壳", "shell", Id::Shell},

	GUANDAOJIE = {"管道接", "<<<<", Id::Guandaojie},
	GUANDAODU  = {"管道堵", "<<<|", Id::Guandaodu},

	DBGPOT = {"这断点", "DBGPOT", Id::DebugPoint},
	DBGPARPOT = {"这析断点", "DBGPARPOT", Id::DebugParsePoint};

const Item
	*ALL[] = {
			&EVAL2,
			&CALL,
			&PRINT, &EXEC,
			&BEGIN, //&END,
			&VAR_BEGIN,
			&JUHAO,
			&DOUHAO,
			&MAOHAO,
			&DUNHAO, &DUNHAO2,
			&TEXT_BEGIN,
			&CODE_BEGIN,
			&YUANYANG_BEGIN,
			&TEXT_BEGIN2,
			&FOR, &BREAK, &CONTINUE,
			&RANGE, &BREAK2, &CONTINUE2,
			&RETURN,
			&IF, &THEN, &ELSE,
			&SWITCH,
			&WITH,
			&GUANDAOJIE, &GUANDAODU,
			&EVAL,
			&SET, &DEF, &ALIAS,
			&HAS,
			&TAG_BEGIN,
			&LOAD,
			&EXIT,
			&DL, &FUNC,
			&NAME, &MOD, &MOD_FREE,
			&REM_BEGIN,
			&DBGPOT, &DBGPARPOT,
	};

const List
	ALL_JUHAO = {&JUHAO,},
	ALL_DOUHAO = {&DOUHAO,},
	ALL_RESERVED = {
			&REM_BEGIN, &REM_END,
			&TEXT_BEGIN, &TEXT_END,
			&VAR_BEGIN, &VAR_END,
			&TAG_BEGIN, &TAG_END,
			&CODE_BEGIN, &CODE_END,
			&YUANYANG_BEGIN, &YUANYANG_END,
			&TEXT_BEGIN2, &TEXT_END2,
			&BEGIN, &END,
			&JUHAO,
			&DOUHAO,
			&MAOHAO,
			&DUNHAO, &DUNHAO2,
			&FOR, &BREAK, &CONTINUE,
			&RANGE, &BREAK2, &CONTINUE2,
			&RETURN,
			&EXIT,
			&IF,
			&DENGYU, &XIAOYUDENGYU, &XIAOYU, &DAYUDENGYU, &DAYU,
			&NOT, &AND, &OR,
			&THEN, &ELSE,
			&SWITCH,
			&WITH,
			&GUANDAOJIE, &GUANDAODU,
			&MOD, &MOD_FREE,
			&NAME,
			&SET, &ALIAS, &DEF, &EQU,
			&HAS,
			&EVAL2,
			&LOAD,
			&EVAL,
			&PRINT, &EXEC,
			&DL, &FUNC,
			&CALL,
			&DBGPOT, &DBGPARPOT,

			&TOP, &UP, &PRIV, &VAL,
			&NO_ARG, &NO_ARGC, &BACK_ARG, &DUNHAO3, &THROUGH, &BY,
			&ARGS,
			&ARG, &RESERVED, &LENGTH,
			&ATTR, &QV,
			&SYSTEM, &SHELL,
			&LF, &CR, &TAB, &ESC,
	};

bool Item::is__(const std::string& s, bool use_en) const {
	return s == val_ || (use_en && s == val_en_);
}
bool Item::starts__(const std::string& s, bool use_en, size_t &kw_len, size_t i) const {
	if(startswith__(s, i, val_, kw_len)) {
		return true;
	}
	if(use_en && startswith__(s, i, val_en_, kw_len)) {
		return true;
	}
	return false;
}

const Item *get__(const std::string &s, bool use_en, size_t i, size_t &kw_len, Id kw_by, const List *power_kw) {
	auto fn = [&](const Item *i2) {
		return i2->starts__(s, use_en, kw_len, i);
	};
	if(power_kw) {
		for(auto i2 : *power_kw)
			if(fn(i2))
				return i2;
	} else {
		for(auto i2 : ALL)
			if(fn(i2))
				return i2;
	}
	return nullptr;
}

const Item* has__(const Id kw, const List *all_kw) {
	if(all_kw)
		for(auto i : *all_kw)
			if(*i == kw)
				return i;
	return nullptr;
}

} /* namespace keyword */
