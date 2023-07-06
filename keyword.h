/*
 * keyword.h
 *
 *  Created on: 2016年8月20日
 *      Author: zzzzzzzzzzz
 */

#ifndef KEYWORD_H_
#define KEYWORD_H_

#include <string>
#include <vector>

namespace keyword {

enum class Id {
	No,
	TextBegin, TextEnd,
	VarBegin, VarEnd,
	RemBegin, RemEnd,
	TagBegin, TagEnd,
	Juhao,
	Douhao,
	Maohao,
	Dunhao,
	Begin, End,
	CodeBegin, CodeEnd,
	YuanyangBegin, YuanyangEnd,
	TextBegin2, TextEnd2,
	Dengyu, Xiaoyudengyu, Xiaoyu, Dayudengyu, Dayu,
	Not, And, Or,
	If, Then, Else,
	Switch,
	With,
	Exit, Return,
	For, Break, Continue,
	Range, Break2, Continue2,
	Set, Equ, Top, Up, Priv, Val,
	Def, Noarg, Noargc, Backarg, Through, By,
	Alias,
	Has,
	Name, Mod, ModFree,
	Dl, Func, Call,
	Eval,
	Eval2, Load,
	Print, Exec,
	Guandaojie, Guandaodu,
	Arg, Args, Length,
	Attr,
	Qv,
	Reserved,
	Lf, Cr, Tab, Esc,
	System, Shell,
	DebugPoint,
	DebugParsePoint,
};

class Item {
public:
#ifdef ver_no_cls_ini_
	Item(const char* val, const char* val_en, Id val2) : val_(val), val_en_(val_en), val2_(val2) {}
	Item(const char* val, const char* val_en, Id val2, bool is_fix_pos) : val_(val), val_en_(val_en), val2_(val2), is_fix_pos_(is_fix_pos) {}
#endif
	std::string val_, val_en_;
	Id val2_;
	bool is_fix_pos_ = false;
	operator const std::string&() const {return val_;}
	operator Id() const {return val2_;}
	//friend std::string operator+= (const std::string& s, const Item& i) {return s + i.val_;}
	friend std::string operator+ (const std::string& s, const Item& i) {return s + i.val_;}
	friend std::string operator+ (const Item& i, const std::string& s) {return i.val_ + s;}
	friend std::string operator+ (const Item& i, const Item& i2) {return i.val_ + i2.val_;}
	friend bool operator== (const std::string& s, const Item& i) {return s == i.val_;}
	//friend bool operator== (const Item& i2, const Item& i) {return i2.val2_ == i.val2_;}
	//friend bool operator!= (const Item& i2, const Item& i) {return i2.val2_ != i.val2_;}
	bool is__(const std::string& s, bool use_en) const;
	bool starts__(const std::string& s, bool use_en, size_t &kw_len, size_t i = 0) const;
};

extern const Item NO,
	JUHAO,
	TEXT_BEGIN, TEXT_END,
	PRINT,
	EVAL, EVAL2, LOAD,
	CODE_BEGIN, CODE_END,
	YUANYANG_BEGIN, YUANYANG_END,
	TEXT_BEGIN2, TEXT_END2,
	VAR_BEGIN, VAR_END,
	TAG_BEGIN, TAG_END,
	MAOHAO,
	DUNHAO,
	BEGIN, END,
	REM_BEGIN, REM_END,
	SET, EQU, TOP, UP, PRIV, VAL,
	DEF, NO_ARG, BACK_ARG,
	ALIAS,
	HAS,
	NAME, MOD,
	ARG, ARGS, LENGTH,
	EXEC,
	FOR, BREAK, CONTINUE,
	RANGE, BREAK2, CONTINUE2,
	DENGYU, XIAOYUDENGYU, XIAOYU, DAYUDENGYU, DAYU,
	NOT, AND, OR,
	IF, THEN, ELSE,
	EXIT, RETURN,
	DL, FUNC, CALL,
	RESERVED,
	DOUHAO,
	DUNHAO3,
	MOD_FREE,
	SWITCH,
	LF, CR, TAB, ESC,
	BY,
	SYSTEM, SHELL,
	QV,
	THROUGH,
	NO_ARGC,
	WITH,
	GUANDAOJIE, GUANDAODU,
	ATTR,
	DUNHAO2,
	DBGPOT, DBGPARPOT;

using List = std::vector<const Item*>;

const Item *get__(const std::string &s, bool use_en, size_t i, size_t &kw_len, Id kw_by, const List *power_kw);

extern const List ALL_JUHAO, ALL_DOUHAO;

const Item* has__(const Id kw, const List *all_kw);

extern const List ALL_RESERVED;

} /* namespace keyword */

#endif /* KEYWORD_H_ */
