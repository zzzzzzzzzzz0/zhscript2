/*
 * item1.h
 *
 *  Created on: 2016年9月11日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_ITEM1_H_
#define SEGM_ITEM1_H_

#include "item.h"

namespace segm {

class Item1 : Item {
private:
	const keyword::Item* kw_;
public:
	Item1(const keyword::Item* kw) {kw_ = kw;}
	const keyword::Item& kw__() {return *kw_;}

	Result2 z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret);
};

} /* namespace segm */

#endif /* SEGM_ITEM1_H_ */
