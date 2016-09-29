/*
 * item.h
 *
 *  Created on: 2016年8月20日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_ITEM_H_
#define SEGM_ITEM_H_

#include "../keyword.h"
#include "../ret.h"
#include "../result2.h"
#include "../qv.h"

namespace segm {

class Z2_Data : public Sptr {
public:
	size_t i_, i2_;
	void *v_;
	Z2_Data(size_t i, size_t i2, void *v) : i_(i), i2_(i2), v_(v) {}
};

class All;
class List;

class Item {
public:
	virtual ~Item() {}

	virtual const keyword::Item& kw__() = 0;
	virtual const keyword::Item& kw2__() {return keyword::NO;}
	virtual const keyword::Item& kw3__() {return keyword::NO;}
	virtual const keyword::List *ret_kw__() {return &keyword::ALL_JUHAO;}
	virtual All* a__() {return nullptr;}
	virtual All* a2__() {return nullptr;}
	virtual All* a3__() {return nullptr;}

	virtual bool continue1__(keyword::Id ret_kw) {return false;}
	virtual void alt__(Item *&item) {}
	virtual Result2 z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret) = 0;
	virtual const Z2_Data* need_use_z2(const keyword::Item& kw_by, Qv &qv) {return nullptr;}
	virtual Result2 z2__(const Z2_Data* zd, All* a, size_t &i2, Qv &qv, List &ls, Ret &ret) {return Ok(true);}

	virtual std::string s__() {return kw__();}
	virtual std::string str__();
	virtual void s__(std::string& s) {}
};

} /* namespace segm */

#endif /* SEGM_ITEM_H_ */
