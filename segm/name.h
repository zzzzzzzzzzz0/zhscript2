/*
 * name.h
 *
 *  Created on: 2016年9月26日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_NAME_H_
#define SEGM_NAME_H_

#include "all.h"

namespace segm {
namespace name {

class Item : segm::Item {
private:
	All a_;
public:
	const keyword::Item& kw__() {return keyword::NAME;}
	All* a__() {return &a_;}

	Result2 z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret);

	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_NAME_H_ */
