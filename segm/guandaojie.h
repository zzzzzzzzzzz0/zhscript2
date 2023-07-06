/*
 * guandaojie.h
 *
 *  Created on: 2018年2月25日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_GUANDAOJIE_H_
#define SEGM_GUANDAOJIE_H_

#include "all.h"

namespace segm {
namespace guandaojie {

class Range {
public:
	size_t from_, to_ = SIZE_MAX;
	bool from_fix_ = true, to_fix_ = true;
	size_t from_i_, to_i_;
};

class Item : segm::Item {
private:
	All a_;
	size_t i2_ = 0;
	Range range_;
	Result2 stoi__(const std::string& s, size_t & i);
protected:
	virtual bool is_jie__() {return true;}
public:
	const keyword::Item& kw__() {return keyword::GUANDAOJIE;}
	All* a__() {return &a_;}
	Result2 alt__(segm::Item *&item, bool use_en);
	Result2 z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret);

	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_GUANDAOJIE_H_ */
