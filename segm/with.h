/*
 * with.h
 *
 *  Created on: 2017年12月22日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_WITH_H_
#define SEGM_WITH_H_

#include "all.h"

namespace segm {
namespace with {

class Item : segm::Item {
private:
	All a_;
public:
	const keyword::Item& kw__() {return keyword::WITH;}
	All* a__() {return &a_;}
	Result2 alt__(segm::Item *&item, bool use_en);
	Result2 z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret);

	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_WITH_H_ */
