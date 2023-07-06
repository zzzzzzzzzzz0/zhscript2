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

class Item : public for_::Base2 {
private:
	int is__() {return IS_EXIT;}
	const keyword::Item& for__() {return keyword::NO;}
	void z_2__(const std::string &name, const KwBy& kw_by, List &ls, bool &is_true);
public:
	const keyword::Item& kw__() {return keyword::EXIT;}
	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_EXIT_H_ */
