/*
 * continue.h
 *
 *  Created on: 2016年9月10日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_CONTINUE2_H_
#define SEGM_CONTINUE2_H_

#include "for/base2.h"

namespace segm {
namespace continue2 {

class Item : for_::Base2 {
private:
	int is__() {return IS_CONTINUE2;}
	const keyword::Item& for__() {return keyword::RANGE;}
public:
	const keyword::Item& kw__() {return keyword::CONTINUE2;}
	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_CONTINUE_H_ */
