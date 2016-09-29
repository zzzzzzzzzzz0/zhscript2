/*
 * break.h
 *
 *  Created on: 2016年9月10日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_BREAK_H_
#define SEGM_BREAK_H_

#include "for/base2.h"
#include "../is.h"

namespace segm {
namespace break_ {

class Item : for_::Base2 {
private:
	int is__() {return IS_BREAK;}
public:
	const keyword::Item& kw__() {return keyword::BREAK;}
	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_BREAK_H_ */
