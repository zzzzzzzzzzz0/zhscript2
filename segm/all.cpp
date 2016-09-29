/*
 * all.cpp
 *
 *  Created on: 2016年8月20日
 *      Author: zzzzzzzzzzz
 */

#include <algorithm>
#include "all.h"
#include "../debug.h"

namespace segm {

All::~All() {
	for(auto i : a_) {
		delete i;
	}
}

Result2 All::z2__(const keyword::Item& kw_by, bool use_part, size_t &i2, Qv &qv, List &ls, Ret &ret) {
	for(;i2 < a_.size(); i2++) {
		Item* i = a_[i2];
		if(debug_.o_liucheng_) o__({i->kw__().val_}, 'k');
		if(use_part && i->kw__() == keyword::JUHAO)
			break;
		Result2 r2;
		const Z2_Data* zd = i->need_use_z2(kw_by, qv);
		if(zd)
			r2 = i->z2__(zd, this, i2, qv, ls, ret);
		else
			r2 = i->z__(kw_by, qv, ls, ret);
		if(false__(r2)) {
			//if(falsetrue__(r2))
			{
				r2->err_ += keyword::MAOHAO;
				r2->err_ += '\n';
				r2->err_ += keyword::TEXT_BEGIN;
				for(size_t i3 = 0; i3 <= i2 && i3 < a_.size(); i3++) {
					r2->err_ += a_[i3]->str__();
				}
				r2->err_ += keyword::TEXT_END;
			}
			return r2;
		}
	}
	return Ok(true);
}
Result2 All::z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret) {
	size_t i2 = 0;
	return z2__(kw_by, false, i2, qv, ls, ret);
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

std::string item2str__(Item* item) {
	std::string s;

	s += item->kw__();
	All* a = item->a__();
	if(a) {
		for(auto i : a->a__())
			s += i->str__();
	}

	s += item->kw2__();
	a = item->a2__();
	if(a) {
		for(auto i : a->a__())
			s += i->str__();
	}

	s += item->kw3__();
	a = item->a3__();
	if(a) {
		for(auto i : a->a__())
			s += i->str__();
	}
	return s;
}

int qv4tags__(const std::string& s2, List& ls, ModList* mods, Is_my_tag is_my_tag, Qv *&qv2) {
	if(debug_.o_liucheng_) o__({s2}, 'T');
	if(s2 == keyword::TOP) {
		qv2 = &ls.qv_top_;
		return 1;
	}
	if(s2 == keyword::UP) {
		if(!qv2->up_)
			return -1;
		qv2 = qv2->up_;
		return 2;
	}
	if(mods) {
		if(std::find_if(mods->begin(), mods->end(), [&](auto qv3) {
			if(qv3->name_ == s2) {
				qv2 = qv3;
				return true;
			}
			return false;
		}) != mods->end()) {
			return 1;
		}
	}
	{
		Qv *qv = qv2;
		for(;qv;) {
			if(qv->name_ == s2) {
				qv2 = qv;
				return 1;
			}
			qv = qv->up_;
		}
	}
	if(is_my_tag && is_my_tag(s2)) {
		return 2;
	}
	return 0;
}

Result2 qv4tags__(const Tag_List& tags, List& ls, ModList* mods, Is_my_tag is_my_tag, Qv *&qv2) {
	for(auto s2 : tags) {
		switch(qv4tags__(s2, ls, mods, is_my_tag, qv2)) {
		case 1:
			return Ok(true);
		case 2:
			continue;
		case -1:
			return err__("无法的标注", s2);
		}
		return err__("无效的标注", s2);
	}
	return Ok(true);
}

} /* namespace segm */
