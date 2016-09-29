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
public:
	Item(const std::string& val) {val_ = val;}
	const keyword::Item& kw__() {return keyword::NO;}

	Result2 z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret) {
		ret.push__(val_);
		return Ok(true);
	}
	const Z2_Data* need_use_z2(const keyword::Item& kw_by, Qv &qv);
	Result2 z2__(const Z2_Data* zd, All* a, size_t &i2, Qv &qv, List &ls, Ret &ret);

	std::string s__() {return val_;}
	std::string str__() {return s__();}
	void s__(std::string& s) {s += val_;}

	static segm::Item *new__(const std::string& val) {return (segm::Item*)new Item(val);}
};

}} /* namespace segm */

#endif /* SEGM_NO_H_ */
