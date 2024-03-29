/*
 * return.h
 *
 *  Created on: 2016年9月13日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_RETURN_H_
#define SEGM_RETURN_H_

#include "for/base2.h"

namespace segm {
namespace return_ {

class Item : for_::Base2 {
private:
	int is__() {return IS_RETURN;}
	const keyword::Item& for__() {return keyword::NO;}
	void z_2__(const std::string &name, const KwBy& kw_by, List &ls, bool &is_true) {
		if(name.empty())
			is_true = false;
	}
public:
	const keyword::Item& kw__() {return keyword::RETURN;}
	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_RETURN_H_ */
