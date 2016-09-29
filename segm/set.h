/*
 * set.h
 *
 *  Created on: 2016年8月30日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_SET_H_
#define SEGM_SET_H_

#include "all.h"

namespace segm {
namespace set {

class Item : segm::Item {
private:
	All a_, a2_;
protected:
	virtual Result2 z_2__(Ret &ret2, Ret &ret3, Qv &qv, List &ls);
	virtual void z_3__(::var::Item* v, const Ret_Item& ri);
public:
	const keyword::Item& kw__() {return keyword::SET;}
	const keyword::Item& kw2__() {return keyword::EQU;}
	All* a__() {return &a_;}
	All* a2__() {return &a2_;}

	bool continue1__(keyword::Id ret_kw) {return ret_kw == kw2__();}
	Result2 z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret);

	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_SET_H_ */
