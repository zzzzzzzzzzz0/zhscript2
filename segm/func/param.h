/*
 * param.h
 *
 *  Created on: 2016年9月19日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_FUNC_PARAM_H_
#define SEGM_FUNC_PARAM_H_

#include "../mod.h"
#include "callex.h"

namespace segm {
namespace func {
namespace param {

using Item2 = unsigned long int;
using List2 = std::vector<Item2>;

enum class Typ {
	Void,
	Int,
	UInt,
	Long,
	ULong,
	Char,
	Chars,
	CharAddr,
	Addr,
	Not,

	IntVal,
	UIntVal,
	StringVal,

	Buf,
	Siz,
	AddrRet,
	VectorAddr,
	Ret,
	Trace,
	Err,
	Z,
	Callback,
};

class Item {
public:
	Typ typ_;
	Item(Typ typ) : typ_(typ) {}
	virtual Result2 z__(Qv *qv, ::segm::List &ls, List2 &ls2, CallEx &ce) {return Ok(true);}
};

class IntValItem : Item {
public:
	long val_;
	IntValItem(long val) : Item(Typ::IntVal), val_(val) {}
};
class UIntValItem : Item {
public:
	unsigned long val_;
	UIntValItem(unsigned long val) : Item(Typ::UIntVal), val_(val) {}
};

class StringValItem : Item {
public:
	std::string val_;
	StringValItem(const std::string &val) : Item(Typ::StringVal), val_(val) {}
};

}}} /* namespace segm */

#endif /* SEGM_FUNC_PARAM_H_ */
