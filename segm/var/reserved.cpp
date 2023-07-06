/*
 * reserved.cpp
 *
 *  Created on: 2016年11月12日
 *      Author: zzzzzzzzzzz
 */

#include "reserved.h"
#include "../../util.h"

namespace segm {
namespace var {
namespace reserved {

segm::Item* Item::mk__(const std::string &name, Tag_List& tags) {
	Item *item = nullptr;
	if(tags.empty()) {
		int i;
		bool is_en;
		if(mk_i__(name, i, is_en)) {
			item = new Item(i, is_en);
		}
	}
	return (segm::Item*)item;
}

size_t Item::len__() {
	return keyword::ALL_RESERVED.size();
}

#define IS_LENGTH -1

bool Item::mk_i__(const std::string &name, int &i, bool &is_en) {
	auto fn = [&](const std::string& kw, const std::string& len) -> bool {
		if(name == kw + len) {
			i = IS_LENGTH;
			return true;
		}
		if(startswith__(name, kw)) {
			std::string s = name.substr(kw.size());
			if(can_stoi__(s)) {
				i = std::stoi(s) - 1;
				if(i >= 0 && i < (int)len__()) {
					return true;
				}
			}
		}
		return false;
	};
	if(fn(keyword::RESERVED, keyword::LENGTH)) {
		is_en = false;
		return true;
	}
	if(fn(keyword::RESERVED.val_en_, keyword::LENGTH.val_en_)) {
		is_en = true;
		return true;
	}
	return false;
}

std::string Item::s__() {
	std::string s;
	s += kw__();
	s += keyword::RESERVED;
	switch(i_) {
	case IS_LENGTH:
		s += keyword::LENGTH;
		break;
	default:
		s += std::to_string(i_ + 1);
		break;
	}
	s += kw2__();
	return s;
}

void Item::z2__(int i, bool is_en, Qv *qv2, List &ls, Ret &ret) {
	switch(i) {
	case IS_LENGTH:
		ret.push__(std::to_string(len__()));
		break;
	default: {
		const keyword::Item *kw = keyword::ALL_RESERVED[i];
		ret.push__(is_en ? kw->val_en_ : kw->val_);
		break; }
	}
}

Result2 Item::z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	z2__(i_, is_en_, qv, ls, ret);
	return Ok(true);
}

}}} /* namespace segm */
