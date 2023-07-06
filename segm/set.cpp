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

const keyword::List Item::power_kw_ = {&keyword::EQU};

Result2 Item::z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	Ret ret2, ret3;
	{
		Result2 r2;
		{
			KwBy kw_by2 {kw__(), &a_, &kw_by};
			r2 = a_.z__(kw_by2, qv, ls, ret2);
			ret2.one__();
			if(false__(r2))
				return r2;
		}
		{
			KwBy kw_by2 {kw2__(), &a2_, &kw_by};
			r2 = a2_.z__(kw_by2, qv, ls, ret3);
			ret3.one__();
			if(false__(r2))
				return r2;
		}
	}
	return z_2__(ret2, ret3, kw_by, qv, ls, ret);
}

void Item::z_3__(var::Item* v, const Ret_Item& ri) {
	v->val_ = ri.val_;
	v->tags_ = std::move(ri.tags_);
	v->typ2_ = ri.typ2_;
	v->val2_ = ri.val2_;
}

Result2 Item::z_2__(Ret &ret2, Ret &ret3, const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	size_t len = ret3.a_.size(), len2 = ret2.a_.size();
	auto fn2 = [&](size_t i, var::Item* v) {
		const Ret_Item& ri = ret3.a_[i < len ? i : len - 1];
		if(v)
			z_3__(v, ri);
		for_kwby__(kw_by, [&](const keyword::Item& kw) {
			if(kw == keyword::Id::Guandaojie) {
				ret.push__(ri.val_);
				ret.one__(false);
				return true;
			}
			return false;
		});
	};
	auto fn = [&](const std::string& name, size_t i, bool is_priv, bool also_val, Qv *qv2) {
		//if(debug_.o_liucheng_) o__('N', name);
		bool is_new;
		var::Item* v = qv2->var_get2__(name, &is_new);
		if(is_new) {
			v->is_priv_ = is_priv;
			v->also_val_ = also_val;
		}
		if(len == 0) {
			v->val_ = "";
			v->typ2_ = Typ2::No;
			v->val2_ = nullptr;
		} else
			fn2(i, v);
		//if(debug_.o_liucheng_) o__('e', v->val_);
	};
	if(len2 == 0) {
		fn("", 0, false, false, qv);
		for(size_t i = 1; i < len; i++)
			fn2(i, nullptr);
	} else {
		bool use_en = qv->args_->use_en_;
		size_t i = 0;
		for(; i < len2; i++) {
			auto s = ret2.a_[i];
			const std::string& name = s.val_;
			Qv *qv2 = qv;
			bool is_priv = false, also_val = false;
			Result2 r2 = qv4tags__(s.tags_, use_en, ls, qv2->mods_, [&](const std::string &s) {
				if(is__(s, use_en, is_priv))
					return true;
				if(keyword::VAL.is__(s, use_en)) {
					also_val = true;
					return true;
				}
				return false;
			}, &qv2);
			if(false__(r2))
				return r2;
			fn(name, i, is_priv, also_val, qv2);
		}
		for(; i < len; i++)
			fn2(i, nullptr);
	}
	return Ok(true);
}

Result2 Item::name1__(Ret &ret2, std::string &name, Tag_List *&tags) {
	if(ret2.a_.size() == 0)
		return err__('n');
	Ret_Item& ri = ret2.a_[0];
	name = ri.val_;
	if(name.empty())
		return err__("名空");
	//if(debug_.o_liucheng_) o__('N', name);
	tags = &ri.tags_;
	return Ok(true);
}

bool Item::is__(const std::string &s, bool use_en, bool &is_priv) {
	if(keyword::PRIV.is__(s, use_en)) {
		is_priv = true;
		return true;
	}
	return false;
}

}} /* namespace segm */
