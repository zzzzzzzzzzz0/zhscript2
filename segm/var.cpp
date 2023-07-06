/*
 * var.cpp
 *
 *  Created on: 2016年8月29日
 *      Author: zzzzzzzzzzz
 */

#include "var.h"
#include "var/arg.h"
#include "var/args.h"
#include "var/attr.h"
#include "var/reserved.h"
#include "var/qv.h"
#include "alias.h"
#include "../equname.h"
#include "../debug.h"

namespace segm {
namespace var {

Result2 Item::alt2__(segm::Item *&item, bool use_en, bool is_test) {
	std::string name;
	Tag_List tags;
	if(can_cache__(&a_, true, name, tags)) {
		segm::Item *item2 = nullptr;
		for(;;) {
			if((item2 = arg::Item::mk__(name, use_en, tags, is_test)))
				break;
			if((item2 = args::Item::mk__(name, use_en, tags, is_test)))
				break;
			if((item2 = attr::Item::mk__(name, use_en, tags)))
				break;
			if((item2 = reserved::Item::mk__(name, tags)))
				break;
			if((item2 = qv::Item::mk__(name, use_en, tags)))
				break;
			return Ok(true);
		}
		delete item;
		item = item2;
	}
	return Ok(true);
}

Result2 Item::z_2__(const Ret_List &rl, bool is_test, bool also_val, bool use_up, const char* val2, const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	bool use_en = qv->args_ ? qv->args_->use_en_ : false;
	auto fn_val2 = [&](const std::string& val, bool also_val2, const char* val3) -> const char* {
		if(also_val2 && Equ_name::is__(val))
			return val3;
		return val.c_str();
	};
	std::string name;
	{
		Qv *qv2 = qv;
		for(auto s : rl) {
			name += s.val_;
			bool b = false;
			Result2 r2 = qv4tags__(s.tags_, use_en, ls, qv2->mods_,  [&](const std::string &s) {
				if(is_test)
					b = true;
				return b;
			}, &qv2, is_test);
			if(b)
				return r2;
			if(false__(r2))
				return r2;
		}
		//if(debug_.o_liucheng_) o__('R', qv2->name_, ":", qv2->src_);

		auto for_argnames = [&](::arg::List* args) {
			if(args) {
				size_t i = 0;
				if(for_arg_name__(args->names_, [&](const ::arg::Name &name2) {
					if(name2.val_ == name) {
						if(i < args->a_.size()) {
							if(is_test) {
								ret.push__("1");
								return true;
							}
							auto i2 = args->a_[i];
							if(name2.equ__(i2.val_, name, ret))
								return true;
							ret.push__(i2);
						}
						return true;
					}
					i++;
					return false;
				})) return true;
			}
			return false;
		};
		{
			::arg::List* args = qv2->args_;
			if(args && keyword::BY.is__(name, use_en)) {
				if(is_test)
					ret.push__("1");
				else
					ret.push__(args->src3_);
				return Ok(true);
			}
			/*if(for_argnames(args))
				return Ok(true);*/
			int i;
			if(arg::Item::mk_i__(name, use_en, i)) {
				if(is_test) {
					if(args && (int)args->a_.size() > i)
						ret.push__("1");
				} else
					arg::Item::z2__(i, [&](const std::string& val) {return fn_val2(val, also_val, val2);}, qv2, ls, ret);
				return Ok(true);
			}
			int i2;
			if(args::Item::mk_i__(name, use_en, i, i2)) {
				if(is_test)
					ret.push__("1");
				else
					args::Item::z2__(i, i2, kw_by, qv2, ls, ret);
				return Ok(true);
			}
		}
		{
			std::string s;
			if(attr::Item::mk_s__(name, use_en, s)) {
				if(is_test) {
					ret.push__("1");
					return Ok(true);
				} else if(attr::Item::z2__(s, qv2, kw_by, qv, ls, ret))
					return Ok(true);
			}
		}
		{
			int i;
			bool is_en;
			if(reserved::Item::mk_i__(name, i, is_en)) {
				if(is_test) {
					ret.push__("1");
				} else
					reserved::Item::z2__(i, is_en, qv2, ls, ret);
				return Ok(true);
			}
		}
		::var::Item* i;
		Qv *qv_var = qv2;
		auto fn = [&]() {
			if(i->typ2_ == Typ2::Alias) {
				Ret ret2;
				ret2.push__(i->val_);
				ret2.push__(i->tags_);
				ret2.one__();
				return z_2__(ret2.a_, is_test, also_val || i->also_val_, is_test ? false : use_up, also_val ? val2 : i->name_.c_str(), kw_by, qv_var, ls, ret);
			} else {
				if(is_test)
					ret.push__("1");
				else {
					ret.push__(fn_val2(i->val_, also_val || i->also_val_, also_val ? val2 : i->name_.c_str()));
					ret.push__(i->typ2_, i->val2_);
					ret.push__(i->tags_);
				}
			}
			return Ok(true);
		};
		if(kw_by.kw_ == keyword::CALL) {
			if((i = qv2->var_get__(name, is_test, &qv_var, VarTyp::Func)))
				return fn();
		}
		if(qv2->var_get__(name, is_test, [&](::var::Item* i2, Qv* qv_var2, bool) {
			i = i2;
			qv_var = qv_var2;
			fn();
		}, [&](Qv* qv3) -> bool {
			if(for_argnames(qv3->args_))
				return true;
			return false;
		}, VarTyp::Var, false, use_up))
			return Ok(true);
		if((i = qv2->var_get__(name, is_test, &qv_var, VarTyp::Def, false, nullptr, use_up)))
			return fn();
	}
	if(is_test)
		return Ok(true);
	return err__("变量", name, keyword::NOT.val_.c_str(), keyword::HAS.val_.c_str());
}

Result2 Item::z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	Ret ret2;
	{
		KwBy kw_by2 {kw__(), &a_, &kw_by};
		Result2 r2 = a_.z__(kw_by2, qv, ls, ret2);
		ret2.one__();
		if(false__(r2))
			return r2;
	}
	return z_2__(ret2.a_, is_test(), false, true, "", kw_by, qv, ls, ret);
}

}} /* namespace segm */
