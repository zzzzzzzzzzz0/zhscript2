/*
 * eval2.h
 *
 *  Created on: 2016年8月31日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_EVAL2_H_
#define SEGM_EVAL2_H_

#include "load.h"

namespace segm {
namespace eval2 {

class Item : load::Item {
public:
	const keyword::Item& kw__() {return keyword::EVAL2;}
	Result2 z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {return z_2__(false, kw_by, qv, ls, ret);}

	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_EVAL2_H_ */
