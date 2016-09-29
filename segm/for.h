/*
 * for.h
 *
 *  Created on: 2016年8月26日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_FOR_H_
#define SEGM_FOR_H_

#include "for/base.h"

namespace segm {
namespace for_ {

class Item : Base {
public:
	const keyword::Item& kw__() {return keyword::FOR;}
	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_FOR_H_ */
