/*
 * Mod.cpp
 *
 *  Created on: 2016年8月19日
 *      Author: zzzzzzzzzzz
 */

#include <map>
#include <algorithm>
#include "mod.h"
#include "../util.h"
#include "../buf.h"
#include "../defer.h"
#include "../clpars.h"
#include "../textpars.h"
#include "debug.h"

#include "no.h"
#include "text.h"
#include "print.h"
#include "var.h"
#include "block.h"
#include "for.h"
#include "load.h"
#include "eval.h"
#include "set.h"
#include "mod_.h"
#include "eval2.h"
#include "tag.h"
#include "def.h"
#include "exec.h"
#include "break.h"
#include "continue.h"
#include "range.h"
#include "break2.h"
#include "continue2.h"
#include "if.h"
#include "exit.h"
#include "return.h"
#include "dl.h"
#include "func.h"
#include "call.h"
#include "alias.h"
#include "has.h"
#include "name.h"
#include "mod_free.h"
#include "switch.h"
#include "with.h"
#include "guandaojie.h"
#include "guandaodu.h"

namespace segm {

Result2 List::parse_z__(const std::string &s, size_t &i, size_t lvl, All *a, bool use_en, Item* item_by,
		Ret_kw_List &ret_kw_list, keyword::Id &ret_kw, size_t &ret_lvl, char& ret_who) {
	Textpars textpars;
	size_t kw_len = 0;
	Buf buf([&](const std::string &val) {
		if(textpars.is_text__() || textpars.in_text__() || is__(item_by, keyword::Id::TagBegin)) {
			a->push__(text::Item::new__(val));
		} else {
			a->push__(no::Item::new__(val));
		}
	}, [&](char c) {
		if(is__(item_by, keyword::Id::VarBegin) && c == ' ') return true;
		return textpars.can_add__(c);
	});
	auto submit = [&]() {
		buf.clear__();
		textpars.submit__();
	};

	for(;i < s.length();) {
		//o__('c', s.substr(0, i)); o_n__();
		const keyword::Item* kw;
		{
			bool no = false;
			kw = textpars.kw_get__(s, use_en, i, kw_len, no);
			if(no)
				kw = ret_kw_list.kw_get__(s, use_en, i, kw_len);
		}
		if(ret_kw_list.enough__(kw, ret_who, ret_lvl)) {
			submit();
			return Ok(true);
		}
		if(kw) {
			//o__('k', kw->val_);

			if(ret_kw_list.find__(*kw, ret_lvl)) {
				ret_kw = *kw;
				//o__('r', kw->val_);
				submit();
				if(!kw->is_fix_pos_)
					i += kw_len;
				return Ok(true);
			}
			i += kw_len;
			if(textpars.kw_use__(kw, buf))
				continue;
			switch(*kw) {
			case keyword::Id::Maohao:
				if(ret_kw_list.hold_maohao__()) {
					submit();
					a->push1__(*kw);
				} else {
					if(buf.empty__())
						a->push__(text::Item::new__(""));
					else
						submit();
				}
				continue;
			default: break;
			}

			submit();
			switch(*kw) {
			default:
			{
				Item* item;
				switch(*kw) {
				case keyword::Id::Eval2:
					item = eval2::Item::new__();
					break;
				case keyword::Id::Call:
					item = call::Item::new__();
					break;
				case keyword::Id::Print:
					item = print::Item::new__();
					break;
				case keyword::Id::Exec:
					item = exec::Item::new__();
					break;
				case keyword::Id::Begin:
					item = block::Item::new__();
					break;
				case keyword::Id::VarBegin:
					item = var::Item::new__();
					break;
				case keyword::Id::For:
					item = for_::Item::new__();
					break;
				case keyword::Id::Break:
					item = break_::Item::new__();
					break;
				case keyword::Id::Continue:
					item = continue_::Item::new__();
					break;
				case keyword::Id::Range:
					item = range::Item::new__();
					break;
				case keyword::Id::Break2:
					item = break2::Item::new__();
					break;
				case keyword::Id::Continue2:
					item = continue2::Item::new__();
					break;
				case keyword::Id::Return:
					item = return_::Item::new__();
					break;
				case keyword::Id::If:
					item = if_::Item::new__();
					break;
				case keyword::Id::Switch:
					item = switch_::Item::new__();
					break;
				case keyword::Id::With:
					item = with::Item::new__();
					break;
				case keyword::Id::Guandaojie:
					item = guandaojie::Item::new__();
					break;
				case keyword::Id::Guandaodu:
					item = guandaodu::Item::new__();
					break;
				case keyword::Id::Eval:
					item = eval::Item::new__();
					break;
				case keyword::Id::Set:
					item = set::Item::new__();
					break;
				case keyword::Id::Def:
					item = def::Item::new__();
					break;
				case keyword::Id::Alias:
					item = alias::Item::new__();
					break;
				case keyword::Id::Has:
					item = has::Item::new__();
					break;
				case keyword::Id::TagBegin:
					item = tag::Item::new__();
					break;
				case keyword::Id::Load:
					item = load::Item::new__();
					break;
				case keyword::Id::Exit:
					item = exit::Item::new__();
					break;
				case keyword::Id::Dl:
					item = dl::Item::new__();
					break;
				case keyword::Id::Func:
					item = func::Item::new__();
					break;
				case keyword::Id::ModFree:
					item = mod_free::Item::new__();
					break;
				case keyword::Id::Mod:
					item = mod::Item::new__();
					break;
				case keyword::Id::Name:
					item = name::Item::new__();
					break;
				default:
					return err__("未预期的", kw->val_);
				}
				size_t lvl2 = lvl + 1;
				keyword::Id ret_kw2;
				{
					const keyword::Item& kw2 = item->kw2__();
					All* a2 = item->a__();
					Ret_kw_Item rki(item, lvl2, &ret_kw_list);
					for(size_t i2 = 1;;) {
						char ret_who = 0;
						Result2 r2 = parse_z__(s, i, lvl2, a2, use_en, item, ret_kw_list, ret_kw2, ret_lvl, ret_who);
						if(false__(r2))
							return r2;
						if(ret_who == 'e')
							break;
						auto fn = [&](All* a3) {
							if(a3) {
								a2 = a3;
								rki.use2_ = true;
								i2++;
								return true;
							}
							return false;
						};
						if(ret_kw2 == kw2) {
							if(fn(item->a2__()))
								continue;
						}
						if(ret_kw2 == item->kw3__()) {
							if(fn(item->a3__()))
								continue;
						}
						if(i2 == 1) {
							if(item->is_kw2__(ret_kw2))
								continue;
							if(item->a2__() || item->a3__())
								return err__(item->str__(), '@', kw2.val_);
						}
						break;
					}
				}
				Result2 r2 = item->alt__(item, use_en);
				if(false__(r2))
					return r2;
				a->push__(item);
				ret_kw = ret_kw2;
				if(ret_lvl < lvl2) {
					//o__('r', ret_lvl, "<", lvl2);
					return Ok(true);
				}
				break;
			}
			case keyword::Id::Dunhao:
			case keyword::Id::Juhao: case keyword::Id::Douhao:
			case keyword::Id::DebugPoint:
				a->push1__(*kw);
				break;
			case keyword::Id::DebugParsePoint: {
				bool o_H_o = true;
				break; }
			}
			continue;
		} else {
			if(textpars.is_text__() && !textpars.in_text__())
				submit();
		}
		i += step__(s, i, [&](unsigned char c) {buf.add__(c);});
	}
	ret_kw = keyword::NO;
	submit();
	return Ok(true);
}

bool List::ok__(Result2 r2) {
	if(false__(r2)) {
		switch(load::Item::is_return__(r2)) {
		case 1:
			//能设is_exit_吗？
			return true;
		case 2:
			exit_code_ = std::stoi(r2->val2_);
			return true;
		}
		if(!err_.empty())
			err_ += ERR_NL;
		err_ += r2->val_.err_ + r2->err_;
		return false;
	}
	return true;
}

bool Ret_kw_List::enough__(const keyword::Item* kw, char& ret_who, size_t &ret_lvl) {
	size_t end = a_.size();
	if(end > 0) {
		--end;
		for(size_t i = 0; i <= end; i++) {
			Ret_kw_Item* ri = a_[i];
			int ret = ri->i_->enough__(end - i, kw);
			if(ret) {
				ret_who = 'e';
				switch(ret) {
				case 1: {
					size_t i2 = i + 1;
					if(i2 > end)
						i2 = end;
					ret_lvl = a_[i2]->lvl_;
					break; }
				case 2:
					ret_lvl = ri->lvl_;
					break;
				}
				return true;
			}
		}
	}
	return false;
}

bool Ret_kw_List::hold_maohao__() {
	size_t end = a_.size();
	if(end > 0) {
		--end;
		for(size_t i = 0; i <= end; i++) {
			if(a_[i]->i_->hold_maohao__(end - i))
				return true;
		}
	}
	return false;
}

bool Ret_kw_List::find__(keyword::Id kw, size_t &ret_lvl) {
	auto fn = [&](Ret_kw_Item* rwi) {
		ret_lvl = rwi->lvl_;
	};
	if(a_.size() > 0) {
		size_t i2 = a_.size() - 1;
		Ret_kw_Item* rwi = a_[i2];
		auto i = rwi->i_;
		if(rwi->use2_) {
			if(keyword::has__(kw, i->end_kw2__())) {
				fn(rwi);
				return true;
			}
			if(keyword::has__(kw, i->end_kw2_2__())) {
				fn(rwi);
				return true;
			}
		} else {
			if(keyword::has__(kw, i->end_kw__())) {
				fn(rwi);
				return true;
			}
			if(keyword::has__(kw, i->end_kw_2__())) {
				fn(rwi);
				return true;
			}
		}
	}
	return std::find_if(a_.rbegin(), a_.rend(), [&](Ret_kw_Item* rwi) {
		auto i = rwi->i_;
		if(kw == i->kw2__() || kw == i->kw3__()) {
			fn(rwi);
			return true;
		}
		if(rwi->use2_) {
		} else {
			if(keyword::has__(kw, i->other_kw__())) {
				fn(rwi);
				return true;
			}
		}
		return false;
	}) != a_.rend();
}

const keyword::Item *Ret_kw_List::kw_get__(const std::string &s, bool use_en, size_t i, size_t &kw_len) {
	const keyword::Item *kw;
	if(std::find_if(a_.rbegin(), a_.rend(), [&](Ret_kw_Item* rwi) {
		if(rwi->use2_)
			return false;
		auto i2 = rwi->i_;
		if((kw = keyword::get__(s, use_en, i, kw_len, i2->kw__(), i2->power_kw__())))
			return true;
		if(!i2->can_up__()) {
			kw = nullptr;
			return true;
		}
		return false;
	}) != a_.rend())
		return kw;
	return keyword::get__(s, use_en, i, kw_len, keyword::Id::No, nullptr);
}

#ifdef ver_debug_
static void b1__(int i, const char* s, bool& b) {
	bool b2 = !(i == 0 || i == 1);
	if(b2) {
		if(!b)
			printf("\ndebug_.o_");
		printf("%s_%d,", s, i);
		b = true;
	}
}
#endif
Result2 List::z2__(const KwBy& kw_by, arg::List *args, Qv *qv_up, void* attr_1, void* attr_2, Ret &ret) {
#ifdef ver_debug_
	{
		bool b = false;
		b1__(debug_.o_ansi_,"ansi",b);
		b1__(debug_.o_tree_,"tree",b);
		b1__(debug_.o_cache_,"cache",b);
		b1__(debug_.o_args_,"args",b);
		b1__(debug_.o_path_,"path",b);
		b1__(debug_.o_liucheng_,"liucheng",b);
		b1__(debug_.o_if_,"if",b);
		b1__(debug_.o_ret_,"ret",b);
		if(b)
			printf("\n");
	}
#endif
	if(debug_.o_args_) debug_.o_args__(args);
	defer defer;

	All* a = nullptr;
	if(args->src_is_file_) {
		std::string src = file_.ok_path__(args->src_);
		if(src.empty())
			return err__(args->src_, "无法打开");
		args->src2_ = file_.abs__(src);
		if(src_base_.empty()) {
			src_base_ = file_.dir__(args->src2_);
			if(!src_base_.empty())
				file_.known_path_add__(args->src2_);
		}
		file_.known_path_add__(args->src2_);
		defer.i__([&]() {
			file_.known_path_pop__();
		});
		if(std::find_if(mods_.begin(), mods_.end(), [&](Qv *qv) {return qv->src2_ == args->src2_;}) != mods_.end())
			return Ok(true);
		std::string src2, head;
		file_.get_contents__(src, src2, head);
		if(!head.empty()) {
			size_t i = head.find(' ');
			if(i != std::string::npos) {
				Clpars clpars;
				clpars.z__(head.substr(i + 1), *args);
			}
		}
		Result2 r2 = parse__(src2, args->use_en_, &a);
		if(false__(r2))
			return r2;
	} else {
		Result2 r2 = parse__(args->src_, args->use_en_, &a);
		if(false__(r2))
			return r2;
	}

	Qv qv(args, qv_up);
	qv.mods_ = &mods_;
	if(attr_1) {
		auto info = std::make_shared<func::Info>();
		info->addr_ = attr_1;
		//"-V-E-$u" + std::to_string((func::param::Item2)attr_2) + "-Z"
		info->push__(func::param::Typ::VectorAddr);
		info->push__(func::param::Typ::Err);
		info->push__((func::param::Item2)attr_2);
		info->push__(func::param::Typ::Z);
		func::Item::set__(ATTR_FUNCNAME, info, false, &qv, ret);
	}
	KwBy kw_by2 {keyword::NO, a, &kw_by};
	Result2 r2 = a->z__(kw_by2, &qv, *this, ret);
	if(qv.is_mod_) {
		mod::Item::other__(&qv, *this);
		mods_.push_back(new Qv(static_cast<Qv&&>(qv)));
		qv.is_mod_ = false;
	}
	return r2;
}

std::map<size_t, All*> cache_;
Result2 List::parse__(const std::string &s, bool use_en, All **ret_a) {
	All* a = nullptr;
	{
		bool has_cache = false;
		auto cache = [&](size_t hash) {
			auto i = cache_.find(hash);
			if(i == cache_.end()) {
				a = new All();
				cache_[hash] = a;
			} else {
				a = cache_[hash];
				has_cache = true;
			}
			if(debug_.o_cache_) {
				o_n__();
				o__(has_cache ? 'C' : 'c', "hash=", hash);
				o_n__();
			}
		};
		cache(std::hash<std::string>()(s));
		if(ret_a) *ret_a = a;
		if(has_cache) {
			return Ok(true);
		}
	}

	size_t i = 0;
	Ret_kw_List ret_kw_list;
	keyword::Id ret_kw;
	size_t ret_lvl = 0;
	char ret_who = 0;
	Result2 r2 = parse_z__(s, i, 0, a, use_en, nullptr, ret_kw_list, ret_kw, ret_lvl, ret_who);
	if(debug_.o_tree_) {o_n__(); debug2_.ptree__(a, false);}
	if(false__(r2))
		r2->err_ += keyword::MAOHAO + "\r\n" + keyword::TEXT_BEGIN + s.substr(0, i) + keyword::TEXT_END;
	return r2;
}

} /* namespace segm */
