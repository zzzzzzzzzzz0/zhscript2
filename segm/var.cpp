/*
 * var.cpp
 *
 *  Created on: 2016年8月29日
 *      Author: zzzzzzzzzzz
 */

#include "var.h"
#include "var/arg.h"
#include "var/args.h"
#include "alias.h"
#include "../debug.h"

namespace segm {
namespace var {

void Item::alt__(segm::Item *&item) {
	std::string name;
	Tag_List tags;
	if(can_cache__(&a_, true, name, tags)) {
		segm::Item *item2 = nullptr;
		for(;;) {
			if((item2 = arg::Item::mk__(name, tags)))
				break;
			if((item2 = args::Item::mk__(name, tags)))
				break;
			break;
		}
		if(item2) {
			delete item;
			item = item2;
		}
	}
}

Result2 Item::z_2__(const Ret &ret2, const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret) {
	Qv *qv2 = &qv;
	std::string name;
	for(auto s : ret2.a_) {
		name += s.val_;
		bool b = false;
		Result2 r2 = qv4tags__(s.tags_, ls, qv2->mods_,  [&](const std::string &s) {
			if(is_test())
				b = true;
			return b;
		}, qv2);
		if(b)
			return r2;
		if(false__(r2))
			return r2;
	}
	//if(debug_.o_liucheng_) o__({qv2->name_, std::string(":"), qv2->src_}, 'R');

	{
		::arg::List* args = qv2->args_;
		if(args) {
			for(auto i : args->a_) {
				if(!i->name_.empty() && i->name_ == name) {
					if(is_test())
						ret.push__("1");
					else
						ret.push__(i->val_);
					return Ok(true);
				}
			}
		}
		int i;
		if(arg::Item::mk_i__(name, i)) {
			if(is_test()) {
				if(args && (int)args->a_.size() > i)
					ret.push__("1");
			} else
				arg::Item::z2__(i, qv2, ls, ret);
			return Ok(true);
		}
		int i2;
		if(args::Item::mk_i__(name, i, i2)) {
			if(is_test())
				ret.push__("1");
			else
				args::Item::z2__(i, i2, kw_by, qv2, ls, ret);
			return Ok(true);
		}
	}
	{
		::var::Item* i = qv2->var_get__(name, is_test());
		if(i) {
			if(i->typ_ == 'a') {
				return z_2__(static_cast<alias::Info*>(i->val2_.get())->ret_, kw_by, qv, ls, ret);
			} else {
				if(is_test())
					ret.push__("1");
				else {
					ret.push__(i->val_);
					ret.push__(i->typ_, i->val2_);
				}
			}
			return Ok(true);
		}
		i = qv2->var_get__(name, is_test(), VarTyp::Def);
		if(i) {
			if(is_test())
				ret.push__("1");
			else
				ret.push__(i->val_);
			return Ok(true);
		}
	}
	return err__("变量", name, "不存在");
}

Result2 Item::z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret) {
	Ret ret2;
	Result2 r2 = a_.z__(kw__(), qv, ls, ret2);
	if(false__(r2))
		return r2;
	ret2.one__();
	return z_2__(ret2, kw_by, qv, ls, ret);
}

}} /* namespace segm */
