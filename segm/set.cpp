/*
 * set.cpp
 *
 *  Created on: 2016年8月30日
 *      Author: zzzzzzzzzzz
 */

#include "set.h"
#include "../debug.h"

namespace segm {
namespace set {

Result2 Item::z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret) {
	Ret ret2, ret3;
	{
		Result2 r2 = a_.z__(kw__(), qv, ls, ret2);
		if(false__(r2))
			return r2;
		ret2.one__();

		r2 = a2_.z__(kw2__(), qv, ls, ret3);
		if(false__(r2))
			return r2;
		ret3.one__();
	}
	return z_2__(ret2, ret3, qv, ls);
}

void Item::z_3__(var::Item* v, const Ret_Item& ri) {
	v->val_ = ri.val_;
	v->typ_ = ri.typ_;
	v->val2_ = ri.val2_;
}

Result2 Item::z_2__(Ret &ret2, Ret &ret3, Qv &qv, List &ls) {
	size_t len = ret3.a_.size(), len2 = ret2.a_.size();
	auto fn = [&](const std::string& name, size_t i, bool is_priv, Qv *qv2) {
		if(debug_.o_liucheng_) o__({name}, 'N');
		var::Item* v = qv2->var_get__(name, false, VarTyp::Var, true, false);
		if(len > 0) {
			v->is_priv_ = is_priv;
			const Ret_Item& ri = ret3.a_[i < len ? i : len - 1];
			z_3__(v, ri);
			if(debug_.o_liucheng_) o__({ri.val_}, 'e');
		}
	};
	if(len2 == 0) {
		fn("", 0, false, &qv);
	} else {
		for(size_t i = 0; i < len2; i++) {
			auto s = ret2.a_[i];
			const std::string& name = s.val_;
			Qv *qv2 = &qv;
			bool is_priv = false;
			Result2 r2 = qv4tags__(s.tags_, ls, qv2->mods_, [&](const std::string &s) {
				if(s == keyword::PRIV) {
					is_priv = true;
					return true;
				}
				return false;
			}, qv2);
			if(false__(r2))
				return r2;
			fn(name, i, is_priv, qv2);
		}
	}
	return Ok(true);
}

}} /* namespace segm */
