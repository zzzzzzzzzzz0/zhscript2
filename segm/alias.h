/*
 * alias.h
 *
 *  Created on: 2016年9月24日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_ALIAS_H_
#define SEGM_ALIAS_H_

#include "set.h"

namespace segm {
namespace alias {

class Info : public Sptr {
public:
	Ret ret_;
};

class Item : set::Item {
private:
	void z_3__(::var::Item* v, const Ret_Item& ri);
public:
	const keyword::Item& kw__() {return keyword::ALIAS;}
	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_ALIAS_H_ */
