/*
 * Mod.h
 *
 *  Created on: 2016年8月19日
 *      Author: zzzzzzzzzzz
 */

#include "all.h"
#include "../file.h"

#ifndef SEGM_MOD_H_
#define SEGM_MOD_H_

#define ERR_NL "\r\n"
#define ATTR_FUNCNAME "  attr  "

namespace segm {

class Ret_kw_Item;
class Ret_kw_List {
private:
	std::vector<Ret_kw_Item*> a_;
public:
	void push__(Ret_kw_Item* rwi) {a_.push_back(rwi);}
	void pop__() {a_.pop_back();}
	bool find__(keyword::Id kw, size_t &ret_lvl);
	const keyword::Item *kw_get__(const std::string &s, bool use_en, size_t i, size_t &kw_len);
	bool enough__(const keyword::Item* kw, char& ret_who, size_t &ret_lvl);
	bool hold_maohao__();
};

class Ret_kw_Item {
private:
	Ret_kw_List *ls_;
public:
	Item *i_;
	size_t lvl_;
	bool use2_ = false;
	Ret_kw_Item(Item *i, size_t lvl, Ret_kw_List *ls) : i_(i), lvl_(lvl)/*, ls_(ls)*/ {
		ls_ = ls;
		ls_->push__(this);
	}
	~Ret_kw_Item() {ls_->pop__();}
};

class List {
private:
	std::string src_base_;

	Result2 parse_z__(const std::string &s, size_t &i, size_t lvl, All *a, bool use_en, Item* item_by,
			Ret_kw_List &ret_kw_list, keyword::Id &ret_kw, size_t &ret_lvl, char& ret_who);
	bool is__(Item* i, keyword::Id i2) {return i && i->kw__() == i2;}
public:
	Qv qv_top_ = "顶";
	Qv *qv_main_ = nullptr;
	ModList mods_;
	File file_;

	int exit_code_;
	bool is_exit_;
	void reset__() {
		is_exit_ = false;
		exit_code_ = 0;
	}

	List() {
		reset__();
	}

	Result2 z2__(const KwBy& kw_by, arg::List *args, Qv *qv_up, void* attr_1, void* attr_2, Ret &ret);
	Result2 parse__(const std::string &s, bool use_en, All **ret_a);

	std::string mk_modname__(const std::string& src) {
		return file_.rel__(src, src_base_, true);
	}

	std::string err_, errinfo_;
	bool ok__(Result2 r2);
};

} /* namespace segm */

#endif /* SEGM_MOD_H_ */
