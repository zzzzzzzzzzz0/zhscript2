/*
 * switch.cpp
 *
 *  Created on: 2017年1月20日
 *      Author: zzzzzzzzzzz
 */

#include "switch.h"
#include "../debug.h"

namespace segm {
namespace switch_ {

int Item::enough__(size_t cnt, const keyword::Item* kw) {
	//o__(0, b ? "*" : " ", cnt, "\t", item2str__(this), "\t", kw->val_); o_n__();
	size_t end = a_.a__().size();
	if(kw && *kw == keyword::Id::Begin && cnt > 0 && end == 0)
		return 1;
	if(end >= 2) {
		--end;
		if(a_.a__()[end]->kw__() == keyword::Id::Begin)
			return 2;
	}
	return 0;
}

bool Item::hold_maohao__(size_t cnt) {
	return cnt == 1;
}

Result2 Item::alt__(segm::Item *&item, bool use_en) {
	size_t end = a_.a__().size();
	if(end < 2)
		return err__(kw__().val_, '.');
	segm::Item* end2 = a_.a__()[--end];
	if(end2->kw__() != keyword::Id::Begin)
		return err__(kw__().val_, '@', keyword::BEGIN.val_);
	const All_List& a = end2->a__()->a__();
	size_t len = 0, maohao = std::string::npos;
	bool b = false, add = false, is_default;
	std::vector<size_t> a_i, a_end2;
	auto to_case = [&](size_t end) {
		if(a_i.empty() || end == 0)
			return;
		for(auto i : a_i) {
			Case c {i, end - 1};
			size_t end2;
			if(maohao == std::string::npos) {
				end2 = c.begin_;
			} else {
				end2 = maohao;
				c.begin_ = maohao + 1;
			}
			if(!a_end2.empty()) {
				end2 = a_end2[0];
				a_end2.erase(a_end2.begin());
			}
			c.end_ = end2;
			c.is_default_ = is_default;
			//o__(0, c.i_, "/", c.end2_, "\t", c.end_, "\t", c.is_default_, " ");
			if(!c.is_default_) {
				bool is_fix = true;
				std::string s;
				for(auto i2 = i; i2 < end2; i2++) {
					segm::Item* item = a[i2];
					if(item->kw__() == keyword::Id::TextBegin)
						item->s__(s);
					else {
						is_fix = false;
						break;
					}
				}
				c.is_fix_ = is_fix;
				if(is_fix) {
					c.tag_ = s;
					//o__(0, c.is_fix_, " ", c.tag_, "\t");
				}
			}
			//o__(0, a[end2]->kw__().val_); o_n__();
			case_.push_back(std::move(c));
		}
		a_i.clear();
		a_end2.clear();
		maohao = std::string::npos;
	};
	for(size_t i = 0, i3 = 0;; i++) {
		bool b2 = i >= a.size(), is_juhao = false;
		if(!b2)
			switch(a[i]->kw__()) {
			case keyword::Id::Juhao: case keyword::Id::Douhao:
				is_juhao = true;
				break;
			case keyword::Id::Maohao:
				maohao = i;
				len++;
				break;
			case keyword::Id::Dunhao:
				if(maohao == std::string::npos) {
					a_end2.push_back(i);
					a_i.push_back(i + 1);
					break;
				}
			default:
				if(!add) {
					add = true;
					a_i.push_back(i);
				}
				len++;
				break;
			}
		if(b2 || is_juhao) {
			if(is_juhao && len == 0) {
				b = true;
				break;
			}
			is_default = false;
			if(len == 1) {
				if(++i3 > 1)
					return err__(kw__().val_, "只能有一个其他");
				is_default = true;
			}
			len = 0;
			if(b2)
				break;
			add = false;
			to_case(i);
		}
	}
	if(b || len == 1)
		return err__(kw__().val_, '.');
	to_case(a.size());
	return Ok(true);
}

Result2 Item::z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	size_t end1 = a_.a__().size() - 1;
	All* a1 = a_.a__()[end1]->a__();
	KwBy kw_by21 {kw__(), a1, &kw_by};
	std::vector<Case> case1(case_);
	for(auto& i : case1) {
		if(i.is_fix_ || i.is_default_) {
			continue;
		}
		size_t i2 = i.i_, end = i.end_;
		Ret ret2;
		Result2 r2 = a1->z7__(kw_by21, qv, ls, ret2, i2, &end);
		ret2.one__();
		if(false__(r2))
			return r2;
		for(auto s : ret2.a_) {
			i.tag_ += s.val_;
		}
		/*for(auto& ii : case1) {
			if(ii.i_ >= i.i_)
				break;
			if(ii.is_default_)
				continue;
			if(ii.tag_ == i.tag_)
				return err__(kw__().val_, "有多个", i.tag_);
		}*/
		//o__(0, i.i_, "/", i.end2_, "\t", i.end_, "\t", i.tag_); o_n__();
	}
	std::string left_val;
	{
		size_t i2 = 0, end = end1;
		Ret ret2;
		KwBy kw_by2 {kw__(), &a_, &kw_by};
		Result2 r2 = a_.z7__(kw_by2, qv, ls, ret2, i2, &end);
		ret2.one__();
		if(false__(r2))
			return r2;
		for(auto s : ret2.a_)
			left_val += s.val_;
	}
	size_t begin = std::string::npos;
	std::vector<size_t> begin2;
	for(auto& i : case1) {
		if(i.is_default_) {
			begin = i.begin_;
			continue;
		}
		if(i.tag_ == left_val) {
			begin2.push_back(i.begin_);
		}
	}
	auto fn = [&](size_t &i2) {
		return a1->z7__(kw_by21, qv, ls, ret, i2, nullptr, nullptr, true);
	};
	if(!begin2.empty()) {
		for(auto i : begin2) {
			Result2 r2 = fn(i);
			if(false__(r2))
				return r2;
		}
	}
	else if(begin != std::string::npos) {
		Result2 r2 = fn(begin);
		if(false__(r2))
			return r2;
	}
	return Ok(true);
}

}} /* namespace segm */
