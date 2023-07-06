/*
 * guandaodu.h
 *
 *  Created on: 2018年2月25日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_GUANDAODU_H_
#define SEGM_GUANDAODU_H_

#include "guandaojie.h"

namespace segm {
namespace guandaodu {

class Item : guandaojie::Item {
private:
	bool is_jie__() {return false;}
public:
	const keyword::Item& kw__() {return keyword::GUANDAODU;}

	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_GUANDAODU_H_ */
