/*
 * all.cpp
 *
 *  Created on: 2016年8月20日
 *      Author: zzzzzzzzzzz
 */

#include <algorithm>
#include "all.h"
#include "../debug.h"
#include "no.h"
#include "text.h"
#include "item1.h"

namespace segm {

const keyword::List All::var_power_kw_ = {
		&keyword::VAR_BEGIN, &keyword::VAR_END, &keyword::TAG_BEGIN, &keyword::TAG_END,
};

All::~All() {
	for(auto i : a_) {
		delete i;
	}
}

bool All::push1__(keyword::Id kw1, const keyword::List *all_kw) {
	const keyword::Item* kw = keyword::has__(kw1, all_kw ? all_kw : &keyword::ALL_RESERVED);
	if(!kw)
		return false;
	a_.push_back((Item*)new Item1(kw));
	return true;
}

Result2 All::z7__(KwBy& kw_by, Qv *qv, List &ls, Ret &ret, size_t &i2, const size_t *end,
		Z7_fn1 fn1,
		bool use_part, bool use_part2, size_t argc_max, std::vector<std::string> *dunhao3) {
	kw_by.begin_ = i2;
	size_t argc = 0;
	Z7_data1 data1;
	data1.argc_max_ = argc_max;
	auto xxargc_out = [&]() {
		++argc;
		if(data1.argc_max_ != SIZE_MAX && argc >= data1.argc_max_) {
			i2--;
			return true;
		}
		return false;
	};
	for(; i2 < a_.size(); i2++) {
		if(end && i2 >= *end)
			break;
		kw_by.i_ = i2;
		Item* i = a_[i2];
		if(debug_.o_liucheng_) {
			switch(i->kw__()) {
			case keyword::Id::No:
			case keyword::Id::YuanyangBegin:
			case keyword::Id::CodeBegin:
			case keyword::Id::TextBegin2:
			case keyword::Id::TextBegin:
			case keyword::Id::VarBegin:
			case keyword::Id::TagBegin:
			case keyword::Id::Juhao:
			case keyword::Id::Douhao:
			case keyword::Id::Dunhao:
				break;
			default: o__('k', i->str__()); o_n__(); break;
			}
		}
		switch(i->kw__()) {
		case keyword::Id::Juhao:
			if(use_part)
				return Ok(true);
			argc = 0;
			break;
		case keyword::Id::Douhao:
			if(use_part2)
				return Ok(true);
			argc = 0;
			break;
		case keyword::Id::Dunhao:
			if(xxargc_out())
				return Ok(true);
			break;
		case keyword::Id::No:
			if(dunhao3) {
				no::Item* i4 = (no::Item*)i;
				size_t from = 0, i9 = 0;
				for(size_t i3 = argc; i3 < dunhao3->size(); i3++) {
					const std::string& s = dunhao3->at(i3);
					if(s.empty()) {
						if(++i9 > 1)
							break;
						continue;
					} else
						i9 = 0;
					if(i4->sub__(s, from, ret)) {
						if(xxargc_out() || xxargc_out()) {
							i4->sub__(from, ret);
							i2++;
							return Ok(true);
						}
						i3 = argc;
					} else
						break;
				}
				if(from > 0) {
					i4->sub__(from, ret);
					continue;
				}
			}
			break;
		default: break;
		}
		Result2 r2;
		if(fn1) {
			data1.i_ = i;
			switch(fn1(&data1, r2)) {
			case 1:
				continue;
			case -1:
				return Ok(true);
			case -2:
				return r2;
			}
		}
		{
			const Z2_Data* zd = i->need_use_z2__(kw_by, this, i2, qv, ret);
			if(zd) {
				r2 = i->z2__(zd, this, i2, end, kw_by, qv, ls, ret);
				delete zd;
				if(i2 < a_.size())
					switch(a_[i2]->kw__()) {
					case keyword::Id::Juhao:
					case keyword::Id::Douhao:
						i2--;
						break;
					default: break;
					}
			} else {
				r2 = i->z__(kw_by, qv, ls, ret);
			}
		}
		if(false__(r2)) {
			if(falsetrue__(r2)) {
				r2->err_ += keyword::MAOHAO;
				r2->err_ += ERR_NL;
				r2->err_ += keyword::TEXT_BEGIN;
				size_t end3 = end ? *end : a_.size();
				for(size_t i3 = kw_by.begin_; i3 <= kw_by.i_ && i3 < end3; i3++) {
					r2->err_ += a_[i3]->str__();
				}
				r2->err_ += keyword::TEXT_END;
			}
			return r2;
		}
	}
	return Ok(true);
}

bool can_cache__(All* a, bool in_var, std::string &s, Tag_List& tags, size_t to, bool in_tag) {
	if(to == std::string::npos)
		to = a->a__().size();
	for(size_t i2 = 0; i2 < to; i2++) {
		auto i = a->a__()[i2];
		switch(i->kw__()) {
		case keyword::Id::Begin:
			if(!can_cache__(i->a__(), in_var, s, tags))
				return false;
			break;
		case keyword::Id::No:
			if(!in_var)
				return false;
		case keyword::Id::TextBegin:
			if(in_tag) {
				std::string tag;
				i->s__(tag);
				tags.push_back(tag);
			} else
				i->s__(s);
			break;
		case keyword::Id::TagBegin:
			if(!can_cache__(i->a__(), in_var, s, tags, std::string::npos, true))
				return false;
			break;
		default:
			return false;
		}
	}
	return true;
}

static void item2str__(const keyword::Item& kw, All* a, std::string& s, bool is1 = false) {
	if(is1 || !a || (a && a->a__().size() > 0))
		s += kw;
	if(a)
		for(auto i : a->a__())
			s += i->str__();
}
std::string item2str__(Item* item) {
	std::string s;
	item2str__(item->kw__(), item->a__(), s, true);
	item2str__(item->kw2__(), item->a2__(), s);
	item2str__(item->kw3__(), item->a3__(), s);
	return s;
}

char qv4tags__(const std::string& s2, bool use_en, List& ls, ModList* mods, Is_my_tag is_my_tag, Qv **qv2) {
	//if(debug_.o_liucheng_) o__('T', s2);
	if(qv2) {
		if(keyword::TOP.is__(s2, use_en)) {
			*qv2 = &ls.qv_top_;
			return 't';
		}
		if(keyword::UP.is__(s2, use_en)) {
			if(!(*qv2)->up_)
				return 'U';
			*qv2 = (*qv2)->up_;
			return 'u';
		}
		if(mods) {
			if(std::find_if(mods->begin(), mods->end(), [&](Qv *qv3) {
				if(qv3->name_ == s2) {
					*qv2 = qv3;
					return true;
				}
				return false;
			}) != mods->end()) {
				return 'm';
			}
		}
		Qv *qv = *qv2;
		for(;qv;) {
			if(qv->name_ == s2) {
				*qv2 = qv;
				return 'n';
			}
			qv = qv->up_;
		}
	}
	if(is_my_tag && is_my_tag(s2)) {
		return '~';
	}
	return 0;
}

Result2 qv4tags__(const Tag_List& tags, bool use_en, List& ls, ModList* mods, Is_my_tag is_my_tag, Qv **qv2, bool is_test) {
	for(auto s2 : tags) {
		switch(qv4tags__(s2, use_en, ls, mods, is_my_tag, qv2)) {
		case 'U':
			if(is_test) {
				if(is_my_tag) {
					is_my_tag(s2);
					return Ok(true);
				}
			}
			return err__('?', 't', s2);
		case 0:
			return err__('X', 't', s2);
		}
	}
	return Ok(true);
}

Result2 mem4tags__(const All &a1,
		std::function<Result2(size_t, const std::string&)> fn_fix,
		std::function<Result2(size_t)> fn_nofix,
		size_t &ret_i2) {
	const All_List& a = a1.a__();
	for(size_t i = 0; i < a.size(); i++) {
		segm::Item* item = a[i];
		const All_List& a2 = item->a__()->a__();
		if(item->kw__() == keyword::TAG_BEGIN) {
			if(a2.size() == 1 && a2[0]->kw__() == keyword::TEXT_BEGIN) {
				Result2 r2 = fn_fix(i, ((text::Item*)a2[0])->val__());
				if(false__(r2))
					return r2;
			} else {
				if(fn_nofix) {
					Result2 r2 = fn_nofix(i);
					if(false__(r2))
						return r2;
				} else
					return err__('X', 't');
			}
			ret_i2++;
			continue;
		}
		break;
	}
	return Ok(true);
}

Result2 atoi__(const All &a, size_t i, KwBy& kw_by, Qv *qv, List &ls, std::function<Result2(const std::string&)> fn) {
	Ret ret2;
	Result2 r2 = a.a__()[i]->a__()->z__(kw_by, qv, ls, ret2);
	ret2.one__();
	if(!false__(r2)) {
		if(ret2.a_.size() > 0) {
			return fn(ret2.a_[0].val_);
		}
	}
	return r2;
}

} /* namespace segm */
