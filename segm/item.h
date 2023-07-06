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

class Z2_Data {
public:
	size_t i_, i2_, from_;
	def::Item* di_;
};

class All;

struct KwBy {
	const keyword::Item& kw_;
	All* a_;
	const KwBy* up_ = nullptr;
	const keyword::Item* kw2_ = nullptr;
	std::string s_;
	size_t i_ = 0, begin_ = 0;
};
bool for_kwby__(const KwBy& kw_by, std::function<bool(const keyword::Item&)> fn);

class List;

class Item {
public:
	virtual ~Item() {}

	virtual const keyword::Item& kw__() = 0;
	virtual const keyword::Item& kw2__() {return keyword::NO;}
	virtual const keyword::Item& kw3__() {return keyword::NO;}
	virtual const keyword::List *power_kw__() {return nullptr;}
	virtual const keyword::List *other_kw__() {return nullptr;}
	virtual const keyword::List *end_kw__() {return &keyword::ALL_JUHAO;}
	virtual const keyword::List *end_kw_2__() {return &keyword::ALL_DOUHAO;}
	virtual const keyword::List *end_kw2__() {return &keyword::ALL_JUHAO;}
	virtual const keyword::List *end_kw2_2__() {return &keyword::ALL_DOUHAO;}
	virtual All* a__() {return nullptr;}
	virtual All* a2__() {return nullptr;}
	virtual All* a3__() {return nullptr;}

	virtual bool is_kw2__(keyword::Id ret_kw) {return false;}
	virtual bool can_up__() {return true;}
	virtual bool hold_maohao__(size_t cnt) {return false;}
	virtual int enough__(size_t cnt, const keyword::Item* kw) {return 0;}
	virtual Result2 alt__(Item *&item, bool use_en) {return Ok(true);}
	virtual Result2 z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) = 0;
	virtual const Z2_Data* need_use_z2__(const KwBy& kw_by, const All* a, size_t i2,
			Qv *qv, Ret &ret) {return nullptr;}
	virtual Result2 z2__(const Z2_Data* zd, All* a, size_t &i2, const size_t *end,
			const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {return Ok(true);}

	virtual std::string s__() {return kw__();}
	virtual std::string str__();
	virtual void s__(std::string& s) {}
};

} /* namespace segm */

#endif /* SEGM_ITEM_H_ */
