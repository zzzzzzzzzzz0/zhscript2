/*
 * no.h
 *
 *  Created on: 2016年8月22日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_NO_H_
#define SEGM_NO_H_

#include "all.h"

namespace segm {
namespace no {

class Item : segm::Item {
private:
	std::string val_;

	const Z2_Data* mk_z2data(size_t from, const All* a, size_t i2, Qv *qv);
	bool dunhao3__(def::Item* item, size_t i4, size_t i5, const All* a);
public:
	Item(const std::string& val) {val_ = val;}
	const keyword::Item& kw__() {return keyword::NO;}

	Result2 z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
		ret.push__(val_);
		return Ok(true);
	}
	const Z2_Data* need_use_z2__(const KwBy& kw_by, const All* a, size_t i2, Qv *qv, Ret &ret);
	Result2 z2__(const Z2_Data* zd, All* a, size_t &i2, const size_t *end, const KwBy& kw_by, Qv *qv, List &ls, Ret &ret);

	std::string s__() {return val_;}
	std::string str__() {return s__();}
	void s__(std::string& s) {s += val_;}

	bool sub__(const std::string& s, size_t &from, Ret &ret);
	void sub__(size_t from, Ret &ret) {ret.push__(val_.substr(from));}

	static segm::Item *new__(const std::string& val) {return (segm::Item*)new Item(val);}
};

}} /* namespace segm */

#endif /* SEGM_NO_H_ */
