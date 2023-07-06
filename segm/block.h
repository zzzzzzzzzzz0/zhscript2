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
	const keyword::List power_kw_ = {&keyword::END};
public:
	const keyword::Item& kw__() {return keyword::BEGIN;}
	const keyword::Item& kw2__() {return keyword::END;}
	const keyword::List *power_kw__() {return &power_kw_;}
	const keyword::List *end_kw__() {return nullptr;}
	const keyword::List *end_kw_2__() {return nullptr;}
	All* a__() {return &a_;}

	Result2 z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
		KwBy kw_by2 {kw__(), &a_, &kw_by};
		return a_.z__(kw_by2, qv, ls, ret);
	}

	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_BLOCK_H_ */
