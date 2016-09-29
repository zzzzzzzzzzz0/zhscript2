/*
 * def.h
 *
 *  Created on: 2016年9月2日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_DEF_H_
#define SEGM_DEF_H_

#include "set.h"

namespace segm {
namespace def {

class Item : set::Item {
private:
	Result2 z_2__(Ret &ret2, Ret &ret3, Qv &qv, List &ls);
public:
	const keyword::Item& kw__() {return keyword::DEF;}
	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_DEF_H_ */
