/*
 * Mod.h
 *
 *  Created on: 2016年8月19日
 *      Author: zzzzzzzzzzz
 */

#include "all.h"

#ifndef SEGM_MOD_H_
#define SEGM_MOD_H_

namespace segm {

class Ret_kw_Item;
class Ret_kw_List {
private:
	std::vector<Ret_kw_Item*> a_;
public:
	void push__(Ret_kw_Item* rwi) {a_.push_back(rwi);}
	void pop__() {a_.pop_back();}
	bool find__(keyword::Id kw, keyword::Id &ret_kw, size_t &ret_lvl);
};

class Ret_kw_Item {
private:
	Ret_kw_List *ls_;
public:
	const keyword::List *kws_;
	keyword::Id kw2_, kw3_;
	size_t lvl_;
	bool block1_;
	Ret_kw_Item(const keyword::List *kws, keyword::Id kw2, keyword::Id kw3, size_t lvl, bool block1, Ret_kw_List *ls) {
		kws_=(kws), kw2_=(kw2), kw3_=(kw3), lvl_=(lvl), block1_=(block1), ls_=(ls);
		ls_->push__(this);
	}
	~Ret_kw_Item() {ls_->pop__();}
};

class List {
private:
	std::string src_base_;

	Result2 parse_z__(const std::string &s, size_t &i, All *a, Ret_kw_List &ret_kw_list, keyword::Id &ret_kw, size_t &ret_lvl,
			size_t lvl, keyword::Id kw_by2);
	Result2 parse__(const std::string &s, All *a);
public:
	Qv qv_top_ = ("顶");
	ModList mods_;

	Result2 z2__(const keyword::Item& kw_by, arg::List *args, Qv *qv_up, Ret &ret);

	std::string mk_modname__(const std::string& src);
};

} /* namespace segm */

#endif /* SEGM_MOD_H_ */
