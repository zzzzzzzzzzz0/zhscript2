/*
 * switch.h
 *
 *  Created on: 2017年1月20日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_SWITCH_H_
#define SEGM_SWITCH_H_

#include "all.h"

namespace segm {
namespace switch_ {

class Case {
public:
	size_t i_, begin_, end_;
	bool is_fix_ = false, is_default_ = false;
	std::string tag_;
};

class Item : segm::Item {
private:
	All a_;
	std::vector<Case> case_;
public:
	const keyword::Item& kw__() {return keyword::SWITCH;}
	All* a__() {return &a_;}
	bool hold_maohao__(size_t cnt);
	int enough__(size_t cnt, const keyword::Item* kw);
	Result2 alt__(segm::Item *&item, bool use_en);
	Result2 z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret);

	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_SWITCH_H_ */
