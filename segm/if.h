/*
 * if.h
 *
 *  Created on: 2016年9月11日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_IF_H_
#define SEGM_IF_H_

#include "all.h"

namespace segm {
namespace if_ {

class Item : segm::Item {
private:
	All a_, a2_, a3_;

	Result2 z_2__(All *a, std::string &left_val, bool &result, KwBy& kw_by, Qv *qv, List &ls, Ret &ret);
public:
	const keyword::Item& kw__() {return keyword::IF;}
	const keyword::Item& kw2__() {return keyword::THEN;}
	const keyword::Item& kw3__() {return keyword::ELSE;}
	const keyword::List *power_kw__() {return &power_kw_;}
	const keyword::List *other_kw__() {return &power_kw_;}
	const keyword::List *end_kw__() {return nullptr;}
	const keyword::List *end_kw2_2__() {return nullptr;}
	All* a__() {return &a_;}
	All* a2__() {return &a2_;}
	All* a3__() {return &a3_;}

	bool is_kw2__(keyword::Id ret_kw);
	Result2 z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret);

	static const keyword::List power_kw_;
	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_IF_H_ */
