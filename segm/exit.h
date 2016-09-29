/*
 * exit.h
 *
 *  Created on: 2016年9月13日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_EXIT_H_
#define SEGM_EXIT_H_

#include "for/base2.h"

namespace segm {
namespace exit {

class Item : for_::Base2 {
private:
	int is__() {return IS_EXIT;}
public:
	const keyword::Item& kw__() {return keyword::EXIT;}
	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_EXIT_H_ */
