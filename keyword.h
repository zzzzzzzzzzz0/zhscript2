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
	Maohao,
	Dunhao,
	Begin, End,
	CodeBegin, CodeEnd,
	YuanyangBegin, YuanyangEnd,
	Dengyu, Xiaoyudengyu, Xiaoyu, Dayudengyu, Dayu,
	Not, And, Or,
	If, Then, Else,
	Exit, Return,
	For, Break, Continue,
	Range, Break2, Continue2,
	Set, Equ, Top, Up, Priv,
	Def, Noarg, Qianarg,
	Alias,
	Has,
	Name, Mod,
	Dl, Func, Call,
	Eval,
	Eval2, Load,
	Print, Exec,
	Arg, Args, Length,
	Cr, Lf, Tab, Esc,
};

class Item {
public:
	std::string val_;
	Id val2_;
	operator const std::string&() const {return val_;}
	operator Id() const {return val2_;}
	//friend std::string operator+= (const std::string& s, const Item& i) {return s + i.val_;}
	friend std::string operator+ (const std::string& s, const Item& i) {return s + i.val_;}
	friend std::string operator+ (const Item& i, const std::string& s) {return i.val_ + s;}
	friend std::string operator+ (const Item& i, const Item& i2) {return i.val_ + i2.val_;}
	friend bool operator== (const std::string& s, const Item& i) {return s == i.val_;}
	//friend bool operator== (const Item& i2, const Item& i) {return i2.val2_ == i.val2_;}
	//friend bool operator!= (const Item& i2, const Item& i) {return i2.val2_ != i.val2_;}
};

extern const Item NO,
	JUHAO,
	TEXT_BEGIN, TEXT_END,
	CR, LF, TAB, ESC,
	PRINT,
	EVAL, EVAL2, LOAD,
	CODE_BEGIN, CODE_END,
	YUANYANG_BEGIN, YUANYANG_END,
	VAR_BEGIN, VAR_END,
	TAG_BEGIN, TAG_END,
	MAOHAO,
	DUNHAO,
	BEGIN, END,
	REM_BEGIN, REM_END,
	SET, EQU, TOP, UP, PRIV,
	DEF, NO_ARG, QIAN_ARG,
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
	DL, FUNC, CALL;

const Item *get__(const std::string &s, size_t i, size_t &i3, Id kw_by);

using List = std::vector<const Item*>;

extern const List ALL_JUHAO, ALL_IF;

const Item* has__(const Id kw, const List *all_kw);

} /* namespace keyword */

#endif /* KEYWORD_H_ */
