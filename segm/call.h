/*
 * call.h
 *
 *  Created on: 2016年9月14日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_CALL_H_
#define SEGM_CALL_H_

#include "all.h"
#include "func.h"

namespace segm {
namespace call {

class Item : segm::Item {
private:
	All a_;
public:
	const keyword::Item& kw__() {return keyword::CALL;}
	All* a__() {return &a_;}

	Result2 z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret);
	static Result2 z_2__(func::Info* fi, func::ParamList& fpl2, Ret &ret2, size_t from, const KwBy& kw_by, Qv *qv, List &ls, Ret &ret);

	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_CALL_H_ */
