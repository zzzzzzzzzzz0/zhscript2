/*
 * block.h
 *
 *  Created on: 2016年8月26日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_BLOCK_H_
#define SEGM_BLOCK_H_

#include "all.h"

namespace segm {
namespace block {

class Item : segm::Item {
private:
	All a_;
public:
	const keyword::Item& kw__() {return keyword::BEGIN;}
	const keyword::Item& kw2__() {return keyword::END;}
	virtual const keyword::List *ret_kw__() {return nullptr;}
	All* a__() {return &a_;}

	Result2 z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret) {return a_.z__(kw__(), qv, ls, ret);}

	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_BLOCK_H_ */
