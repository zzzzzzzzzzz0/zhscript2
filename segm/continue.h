/*
 * continue.h
 *
 *  Created on: 2016年9月10日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_CONTINUE_H_
#define SEGM_CONTINUE_H_

#include "for/base2.h"

namespace segm {
namespace continue_ {

class Item : for_::Base2 {
private:
	int is__() {return IS_CONTINUE;}
	const keyword::Item& for__() {return keyword::FOR;}
public:
	const keyword::Item& kw__() {return keyword::CONTINUE;}
	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_CONTINUE_H_ */
