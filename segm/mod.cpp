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
#include "../debug.h"
#include "../buf.h"
#include "../file.h"
#include "../defer.h"

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
#include "item1.h"
#include "exit.h"
#include "return.h"
#include "dl.h"
#include "func.h"
#include "call.h"
#include "alias.h"
#include "has.h"
#include "name.h"

namespace segm {

Result2 List::parse_z__(const std::string &s, size_t &i, All *a, Ret_kw_List &ret_kw_list, keyword::Id &ret_kw, size_t &ret_lvl,
		size_t lvl, keyword::Id kw_by2) {
	int in_text = 0, in_code = 0, in_yuanyang = 0, in_rem = 0;
	auto in__text = [&]() {return in_text > 0 || in_code > 0 || in_yuanyang > 0;};
	size_t kw_len = 0;
	Buf buf([&](const std::string &val) {
		if(in__text()) {
			a->push__(text::Item::new__(val));
		} else {
			a->push__(no::Item::new__(val));
		}
	}, [&](char c) {
		if(in_rem > 0)
			return false;
		if(c >= 0 && c < ' ')
			return in_yuanyang > 0;
		if(c == ' ')
			return in_text > 0 || in_yuanyang > 0;
		return true;
	});
	auto buf_add = [&](const keyword::Item* kw) {buf.add__(kw->val_);};
	auto err4 = [&](const char* s1, const std::string& s2) {
		Result2 r2 = err__(s1, s2);
		r2->err_ += keyword::MAOHAO + keyword::TEXT_BEGIN + s.substr(0, i) + keyword::TEXT_END;
		return r2;
	};

	for(;i < s.length();) {
		//o__({s.substr(i)}, 'c'); o_n__();
		keyword::Id kw_by;
		for(;;) {
			if(in_rem      > 0) {kw_by = keyword::Id::RemBegin; break;}
			if(in_yuanyang > 0) {kw_by = keyword::Id::YuanyangBegin; break;}
			if(in_code     > 0) {kw_by = keyword::Id::CodeBegin; break;}
			if(in_text     > 0) {kw_by = keyword::Id::TextBegin; break;}
			kw_by = kw_by2; break;
		}
		const keyword::Item* kw = keyword::get__(s, i, kw_len, kw_by);
		if(kw) {
			//o__({kw->val_}, 'k');

			if(ret_kw_list.find__(*kw, ret_kw, ret_lvl)) {
				//o__({kw->val_}, 'r');
				buf.clear__();
				if(ret_kw != keyword::JUHAO)
					i += kw_len;
				return Ok(true);
			}
			i += kw_len;
			switch(*kw) {
			case keyword::Id::TextBegin:     if(!in__text()) buf.clear__(); if(in_text++ || in_code > 0 || in_yuanyang > 0) buf_add(kw); continue;
			case keyword::Id::CodeBegin:     if(!in__text()) buf.clear__(); if(in_code++ || in_text > 0 || in_yuanyang > 0) buf_add(kw); continue;
			case keyword::Id::YuanyangBegin: if(!in__text()) buf.clear__(); if(in_yuanyang++ || in_text > 0 || in_code > 0) buf_add(kw); continue;
			case keyword::Id::TextEnd:     if(in_text - 1 == 0 && in_code == 0 && in_yuanyang == 0) buf.clear__(); if(--in_text || in_code > 0 || in_yuanyang > 0) buf_add(kw); continue;
			case keyword::Id::CodeEnd:     if(in_text == 0 && in_code - 1 == 0 && in_yuanyang == 0) buf.clear__(); if(--in_code || in_text > 0 || in_yuanyang > 0) buf_add(kw); continue;
			case keyword::Id::YuanyangEnd: if(in_text == 0 && in_code == 0 && in_yuanyang - 1 == 0) buf.clear__(); if(--in_yuanyang || in_text > 0 || in_code > 0) buf_add(kw); continue;
			case keyword::Id::RemBegin: in_rem++; continue;
			case keyword::Id::RemEnd:   in_rem--; continue;
			default: break;
			}

			buf.clear__();
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
				case keyword::Id::Name:
					item = name::Item::new__();
					break;
				case keyword::Id::Mod:
					item = mod::Item::new__();
					break;
				default:
					return err4("未预期的", *kw);
				}
				const keyword::Item& kw2 = item->kw2__();
				const keyword::Item& kw3 = item->kw3__();
				All* a2 = item->a__();
				size_t lvl2 = lvl + 1;
				keyword::Id ret_kw2 = keyword::NO;
				Ret_kw_Item rki(item->ret_kw__(), kw2, kw3, lvl2, item->ret_kw__() == nullptr, &ret_kw_list);
				keyword::Id kw_by3 = *kw;
				for(size_t i2 = 1;;) {
					Result2 r2 = parse_z__(s, i, a2, ret_kw_list, ret_kw2, ret_lvl, lvl2, kw_by3);
					if(false__(r2))
						return r2;
					auto fn = [&](All* a3) {
						if(a3) {
							a2 = a3;
							rki.kws_ = &keyword::ALL_JUHAO;
							kw_by3 = ret_kw2;
							i2++;
							return true;
						}
						return false;
					};
					if(ret_kw2 == kw2) {
						if(fn(item->a2__()))
							continue;
					}
					if(ret_kw2 == kw3) {
						if(fn(item->a3__()))
							continue;
					}
					if(i2 == 1) {
						if(item->continue1__(ret_kw2))
							continue;
						if(item->a2__() || item->a3__())
							return err4("期待", kw2);
					}
					break;
				}
				item->alt__(item);
				a->push__(item);
				ret_kw = ret_kw2;
				if(ret_lvl < lvl2) {
					//o__({std::to_string(ret_lvl), std::string("<"), std::to_string(lvl2)}, 'r');
					return Ok(true);
				}
				/*if(ret_kw2 == keyword::JUHAO)
					a->push__((Item*)new Item1(&keyword::JUHAO));*/
				break;
			}
			case keyword::Id::Maohao:
			{
				int debug_liucheng = 1;
			}
			case keyword::Id::Juhao:
			case keyword::Id::Dunhao:
			case keyword::Id::Lf: case keyword::Id::Cr: case keyword::Id::Tab: case keyword::Id::Esc:
				a->push__((Item*)new Item1(kw));
				break;
			}
			continue;
		}

		i += step__(s, i, [&](unsigned char c) {buf.add__(c);});
	}
	buf.clear__();
	return Ok(true);
}

Result2 List::parse__(const std::string &s, All *a) {
	size_t i = 0;
	Ret_kw_List ret_kw_list;
	keyword::Id ret_kw = keyword::NO;
	size_t ret_lvl = 0;
	return parse_z__(s, i, a, ret_kw_list, ret_kw, ret_lvl, 0, keyword::NO);
}

bool Ret_kw_List::find__(keyword::Id kw, keyword::Id &ret_kw, size_t &ret_lvl) {
	bool cmp1 = true;
	return std::find_if(a_.rbegin(), a_.rend(), [&](Ret_kw_Item* rwi) {
		if(rwi->block1_)
			cmp1 = false;
		if((cmp1 && keyword::has__(kw, rwi->kws_)) || kw == rwi->kw2_ || kw == rwi->kw3_) {
			ret_kw = kw;
			ret_lvl = rwi->lvl_;
			return true;
		}
		return false;
	}) != a_.rend();
}

std::string List::mk_modname__(const std::string& src) {
	return file_.rel__(src, src_base_, true);
}

std::map<size_t, All*> cache_;

Result2 List::z2__(const keyword::Item& kw_by, arg::List *args, Qv *qv_up, Ret &ret) {
	if(debug_.o_args_) debug_.o_args__(args);
	defer defer;

	All* a = nullptr;
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
		if(debug_.o_tree_) {
			o_n__();
			o__({"hash=", std::to_string(hash).c_str()}, has_cache ? 'C' : 'c');
			o_n__();
		}
	};

	if(args->src_is_file_) {
		std::string src = file_.ok_path__(args->src_);
		if(src.empty())
			return err__(args->src_, "无法打开");
		args->src2_ = file_.abs__(src);
		if(src_base_.empty()) {
			src_base_ = file_.dir__(args->src2_);
			file_.known_path_add__(args->src2_);
		}
		file_.known_path_add__(args->src2_);
		defer.i__([&]() {
			file_.known_path_pop__();
		});
		cache(std::hash<std::string>()(args->src2_));
		if(!has_cache) {
			Result2 r2 = parse__(file_.get_contents__(src), a);
			if(false__(r2))
				return r2;
		}
	} else {
		cache(std::hash<std::string>()(args->src_));
		if(!has_cache) {
			Result2 r2 = parse__(args->src_, a);
			if(false__(r2))
				return r2;
		}
	}
	if(debug_.o_tree_ && !has_cache) {o_n__(); debug_.ptree__(a, has_cache);}

	Qv qv(args, qv_up);
	qv.mods_ = &mods_;
	Result2 r2 = a->z__(kw_by, qv, *this, ret);
	if(qv.is_mod_) {
		qv.args_ = nullptr;
		qv.up_ = nullptr;
		qv.mods_ = nullptr;
		mods_.push_back(new Qv(static_cast<Qv&&>(qv)));
	}
	return r2;
}

} /* namespace segm */
