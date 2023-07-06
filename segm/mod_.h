/*
 * mod_.h
 *
 *  Created on: 2016年8月31日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_MOD__H_
#define SEGM_MOD__H_

#include "all.h"

namespace segm {
namespace mod {

class Item : segm::Item {
private:
	All a_;
public:
	const keyword::Item& kw__() {return keyword::MOD;}
	All* a__() {return &a_;}

	Result2 z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret);

	static segm::Item *new__() {return (segm::Item*)new Item();}
	static void other__(Qv *qv, List &ls);
};

}} /* namespace segm */

#endif /* SEGM_MOD__H_ */
