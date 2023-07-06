/*
 * break.h
 *
 *  Created on: 2016年9月10日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_BREAK2_H_
#define SEGM_BREAK2_H_

#include "for/base2.h"

namespace segm {
namespace break2 {

class Item : for_::Base2 {
private:
	int is__() {return IS_BREAK2;}
	const keyword::Item& for__() {return keyword::RANGE;}
public:
	const keyword::Item& kw__() {return keyword::BREAK2;}
	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_BREAK_H_ */
