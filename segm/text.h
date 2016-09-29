/*
 * text.h
 *
 *  Created on: 2016年8月22日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_TEXT_H_
#define SEGM_TEXT_H_

#include "all.h"

namespace segm {
namespace text {

class Item : segm::Item {
private:
	std::string val_;
public:
	Item(const std::string& val) {val_ = val;}
	const keyword::Item& kw__() {return keyword::TEXT_BEGIN;}
	const keyword::Item& kw2__() {return keyword::TEXT_END;}

	Result2 z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret) {
		ret.push__(val_);
		return Ok(true);
	}

	std::string s__() {return kw__() + val_ + kw2__();}
	std::string str__() {return s__();}
	void s__(std::string& s) {s += val_;}

	const std::string& val__() {return val_;}

	static segm::Item *new__(const std::string& val) {return (segm::Item*)new Item(val);}
};

}} /* namespace segm */

#endif /* SEGM_TEXT_H_ */
