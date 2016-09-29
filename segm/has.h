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
	const keyword::Item& kw2__() {return keyword::NO;}
	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_HAS_H_ */
