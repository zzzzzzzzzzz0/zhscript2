/*
 * has.h
 *
 *  Created on: 2016年9月24日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_HAS_H_
#define SEGM_HAS_H_

#include "var.h"

namespace segm {
namespace has {

class Item : var::Item {
private:
	bool is_test() {return true;}
public:
	const keyword::Item& kw__() {return keyword::HAS;}
	//下否定 var 又
	const keyword::Item& kw2__() {return keyword::NO;}
	bool can_up__() {return true;}
	Result2 alt__(segm::Item *&item, bool use_en) {return alt2__(item, use_en, true);}
	//上
	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_HAS_H_ */
