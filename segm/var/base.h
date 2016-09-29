/*
 * base.h
 *
 *  Created on: 2016年9月9日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_VAR_BASE_H_
#define SEGM_VAR_BASE_H_

#include "../all.h"

namespace segm {
namespace var {

class Base : segm::Item {
public:
	const keyword::Item& kw__() {return keyword::VAR_BEGIN;}
	const keyword::Item& kw2__() {return keyword::VAR_END;}
};

}} /* namespace segm */

#endif /* SEGM_VAR_BASE_H_ */
