/*
 * attr.cpp
 *
 *  Created on: 2019年1月20日
 *      Author: zzzzzzzzzzz
 */

#include "attr.h"
#include "../call.h"
#include "../var.h"
#include "../../util.h"

namespace segm {
namespace var {
namespace attr {

segm::Item* Item::mk__(const std::string &name, bool use_en, Tag_List& tags) {
	Item *item = nullptr;
	if(keyword::ATTR.is__(name, use_en))
		item = new Item(tags);
	return (segm::Item*)item;
}

std::string Item::s__() {
	std::string s;
	s += kw__() + keyword::ATTR;
	s += s_;
	for(auto i : tags_) {
		s += keyword::TAG_BEGIN + i + keyword::TAG_END;
	}
	s += kw2__();
	return s;
}

bool Item::mk_s__(const std::string &name, bool use_en, std::string &ret) {
	auto fn = [&](const std::string& kw) -> bool {
		if(startswith__(name, kw)) {
			ret = name.substr(kw.size());
			return true;
		}
		return false;
	};
	if(fn(keyword::ATTR) || (use_en && fn(keyword::ATTR.val_en_)))
		return true;
	return false;
}

bool Item::z2__(const std::string &s, Qv *qv2, const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	::var::Item* i = qv2->var_get__(ATTR_FUNCNAME, false, nullptr, VarTyp::Func, false, nullptr, false);
	if(i && i->typ2_ == Typ2::Func) {
		func::Info* fi = static_cast<func::Info*>(i->val2_.get());
		func::ParamList fpl2;
		Ret ret2;
		ret2.push__(s);
		ret2.one__();
		Result2 r2 = call::Item::z_2__(fi, fpl2, ret2, 0, kw_by, qv, ls, ret);
		return !false__(r2);
	}
	return false;
}

Result2 Item::z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	Qv *qv2 = qv;
	bool use_en = qv->args_->use_en_;
	Result2 r2 = qv4tags__(tags_, use_en, ls, qv2->mods_, nullptr, &qv2);
	if(false__(r2))
		return r2;
	if(!z2__(s_, qv2, kw_by, qv, ls, ret)) {
		Ret ret2;
		ret2.push__((use_en ? keyword::ATTR.val_en_ : keyword::ATTR.val_) + s_);
		ret2.one__();
		return var::Item::z_2__(ret2.a_, false, false, true, "", kw_by, qv, ls, ret);
	}
	return Ok(true);
}

}}} /* namespace segm */
