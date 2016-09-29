/*
 * def.cpp
 *
 *  Created on: 2016年9月2日
 *      Author: zzzzzzzzzzz
 */

#include "def.h"
#include "../util.h"
#include "../debug.h"

namespace segm {
namespace def {

Result2 Item::z_2__(Ret &ret2, Ret &ret3, Qv &qv, List &ls) {
	if(ret2.a_.size() == 0)
		return err__('n');
	const Ret_Item& ri0 = ret2.a_[0];
	const std::string& name = ri0.val_;
	if(name.empty())
		return err__("名空");
	if(debug_.o_liucheng_) o__({name}, 'N');

	Qv *qv2 = &qv;
	bool is_no_arg = false, is_priv = false;
	size_t qian_arg = 0;
	Result2 r2 = qv4tags__(ri0.tags_, ls, qv2->mods_, [&](const std::string &s) {
		if(s == keyword::PRIV) {
			is_priv = true;
			return true;
		}
		if(s == keyword::NO_ARG) {
			is_no_arg = true;
			return true;
		}
		if(startswith__(s, keyword::QIAN_ARG)) {
			std::string s2 = s.substr(keyword::QIAN_ARG.val_.length());
			if(s2.empty()) {
				qian_arg = 1;
				return true;
			}
			if(can_stoi__(s2)) {
				qian_arg = std::stoi(s2);
				return true;
			}
		}
		return false;
	}, qv2);
	if(false__(r2))
		return r2;

	if(qv.for_def__([&](::def::Item* item) {
		return startswith__(name, item->name_) == 2;
	}))
		return err__("名", name, "被覆盖");

	var::Item* v = qv2->var_get__(name, false, VarTyp::Def, true, false);

	::def::Item* di = (::def::Item*)v;
	di->is_no_arg_ = is_no_arg;
	di->qian_arg_ = qian_arg;

	for(auto i : ret3.a_) {
		if(debug_.o_liucheng_) o__({i.val_}, 'e');
		v->val_ = i.val_;
	}

	for(size_t i = 1; i < ret2.a_.size(); i++) {
		di->arg_names_.push_back(ret2.a_[i].val_);
	}

	return Ok(true);
}

}} /* namespace segm */
