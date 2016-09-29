/*
 * func.h
 *
 *  Created on: 2016年9月13日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_FUNC_H_
#define SEGM_FUNC_H_

#include "all.h"
#include "func/param.h"

namespace segm {
namespace func {

using VV = void(*)();
using UV = param::Item2(*)();
using VA = void(*)(...);
using UA = param::Item2(*)(...);

using ParamList = std::vector<param::Item*>;

class Info : public Sptr {
public:
	void *addr_ = nullptr;
	param::Typ ret_ = param::Typ::Void;
	ParamList params_;

	Result2 parse2__(const std::string &s, param::Typ *ret, ParamList &params);
	Result2 parse__(const std::string &s) {return parse2__(s, &ret_, params_);}
};

class Item : segm::Item {
private:
	All a_;
public:
	const keyword::Item& kw__() {return keyword::FUNC;}
	All* a__() {return &a_;}

	Result2 z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret);

	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_FUNC_H_ */
