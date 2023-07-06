/*
 * args.cpp
 *
 *  Created on: 2016年9月7日
 *      Author: zzzzzzzzzzz
 */

#include "args.h"
#include "../../util.h"

namespace segm {
namespace var {
namespace args {

#define I2_NONE -2

segm::Item* Item::mk__(const std::string &name, bool use_en, Tag_List& tags, bool is_test) {
	Item *item = nullptr;
	int i, i2;
	if(mk_i__(name, use_en, i, i2)) {
		item = new Item(i, i2, tags, is_test);
	}
	return (segm::Item*)item;
}

bool Item::mk_i__(const std::string &name, bool use_en, int &i, int &i2) {
	auto fn = [&](const keyword::Item& kw) -> bool {
		if(kw.is__(name, use_en)) {
			i = 0;
			i2 = I2_NONE;
			return true;
		}
		size_t kw_len;
		if(kw.starts__(name, use_en, kw_len)) {
			std::string s = name.substr(kw_len);
			size_t pos = s.find('/');
			if(pos == std::string::npos) {
				if(can_stoi__(s, true)) {
					i = stoi__(s);
					i2 = I2_NONE;
					return true;
				}
			} else {
				std::string s2 = s.substr(pos + 1);
				s = s.substr(0, pos);
				if(s.empty())
					i = 0;
				else if(can_stoi__(s, true))
					i = stoi__(s);
				else
					return false;
				if(can_stoi__(s2, true))
					i2 = stoi__(s2);
				else
					return false;
				if(i != -1 && i2 != -1)
					return true;
			}
		}
		return false;
	};
	if(fn(keyword::ARGS))
		return true;
	return false;
}

std::string Item::s__() {
	std::string s;
	if(!is_test_)
	s += kw__();
	s += keyword::ARGS;
	if(i_ != 0 || i2_ != I2_NONE)
		s += itos__(i_);
	if(i2_ != I2_NONE) {
		s += '/';
		s += itos__(i2_);
	}
	for(auto i : tags_) {
		s += keyword::TAG_BEGIN + i + keyword::TAG_END;
	}
	if(!is_test_)
	s += kw2__();
	return s;
}

int Item::stoi__(const std::string &s) {
	return std::stoi(s) - 1;
}
std::string Item::itos__(int i) {
	return std::to_string(i + 1);
}

void Item::z2__(int i1, int i2, const KwBy& kw_by, Qv *qv2, List &ls, Ret &ret) {
	::arg::List* args = qv2->args_;
	int len = args->a_.size();
	if(i1 < 0) {
		i1 += len + 1;
		if(i1 < 0)
			i1 = 0;
	}
	if(i2 < 0)
		i2 += len + 1;
	if(i2 >= len)
		i2 = len - 1;
	if(i1 > i2 || i1 >= len) {
		ret.push2__(-1);
		return;
	}
	switch(kw_by.kw_) {
	case keyword::Id::Print: case keyword::Id::Exec:
		if(i1 == 0 && i2 == I2_NONE)
			ret.push__(args->all__());
		else
			ret.push__(::arg::List::mk_all__(args->a_, i1, i2));
		break;
	default:
		for(int i = i1; i <= i2; i++) {
			ret.push__(args->a_[i]);
			if(i < i2)
				ret.one__();
		}
		break;
	}
}

Result2 Item::z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	Qv *qv2 = qv;
	bool badtag = false;
	Result2 r2 = qv4tags__(tags_, qv->args_->use_en_, ls, qv2->mods_, [&](const std::string &s) {
		badtag = true;
		return false;
	}, &qv2, is_test_);
	if(false__(r2))
		return r2;
	if(is_test_) {
		if(!badtag)
			ret.push__("1");
	} else
		z2__(i_, i2_, kw_by, qv2, ls, ret);
	return Ok(true);
}

}}} /* namespace segm */
