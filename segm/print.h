/*
 * Print.h
 *
 *  Created on: 2016年8月19日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_PRINT_H_
#define SEGM_PRINT_H_

#include "all.h"

namespace segm {
namespace print {

class Item : segm::Item {
private:
	All a_;
public:
	const keyword::Item& kw__() {return keyword::PRINT;}
	All* a__() {return &a_;}

	Result2 z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret);

	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_PRINT_H_ */
