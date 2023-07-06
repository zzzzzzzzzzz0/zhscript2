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
	Result2 name1__(Ret &ret2, std::string &name, Tag_List *&tags);
	bool is__(const std::string &s, bool use_en, bool &is_priv);
	virtual Result2 z_2__(Ret &ret2, Ret &ret3, const KwBy& kw_by, Qv *qv, List &ls, Ret &ret);
	virtual void z_3__(::var::Item* v, const Ret_Item& ri);
public:
	const keyword::Item& kw__() {return keyword::SET;}
	const keyword::Item& kw2__() {return keyword::EQU;}
	const keyword::List *power_kw__() {return &power_kw_;}
	All* a__() {return &a_;}
	All* a2__() {return &a2_;}

	bool is_kw2__(keyword::Id ret_kw) {return ret_kw == kw2__();}
	Result2 z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret);

	static const keyword::List power_kw_;
	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_SET_H_ */
