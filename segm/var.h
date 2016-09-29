/*
 * var.h
 *
 *  Created on: 2016年8月29日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_VAR_H_
#define SEGM_VAR_H_

#include "var/base.h"

namespace segm {
namespace var {

class Item : Base {
private:
	All a_;
	Result2 z_2__(const Ret &ret2, const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret);
protected:
	virtual bool is_test() {return false;}
public:
	All* a__() {return &a_;}

	void alt__(segm::Item *&item);
	Result2 z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret);

	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_VAR_H_ */
