/*
 * tag.h
 *
 *  Created on: 2016年8月31日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_TAG_H_
#define SEGM_TAG_H_

#include "all.h"

namespace segm {
namespace tag {

class Item : segm::Item {
private:
	All a_;
public:
	const keyword::Item& kw__() {return keyword::TAG_BEGIN;}
	const keyword::Item& kw2__() {return keyword::TAG_END;}
	All* a__() {return &a_;}

	Result2 z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret);

	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_TAG_H_ */
