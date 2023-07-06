/*
 * mod_free.h
 *
 *  Created on: 2016年12月25日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_MOD_FREE_H_
#define SEGM_MOD_FREE_H_

#include "all.h"

namespace segm {
namespace mod_free {

class Item : segm::Item {
private:
	All a_;
public:
	const keyword::Item& kw__() {return keyword::MOD_FREE;}
	All* a__() {return &a_;}

	Result2 z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret);

	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_MOD_FREE_H_ */
