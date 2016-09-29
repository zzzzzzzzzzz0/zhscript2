/*
 * arg.cpp
 *
 *  Created on: 2016年9月1日
 *      Author: zzzzzzzzzzz
 */

#include "arg.h"
#include "../../arg.h"
#include "../../util.h"

namespace segm {
namespace var {
namespace arg {

#define IS_ARG        -3
#define IS_ARG_LENGTH -2
#define IS_ARG0       -1

segm::Item* Item::mk__(const std::string &name, Tag_List& tags) {
	Item *item = nullptr;
	int i;
	if(mk_i__(name, i))
		item = new Item(i, tags);
	return (segm::Item*)item;
}

bool Item::mk_i__(const std::string &name, int &i) {
	const std::string& kw = keyword::ARG;
	if(name == kw) {
		i = IS_ARG;
		return true;
	}
	if(name == kw + keyword::LENGTH) {
		i = IS_ARG_LENGTH;
		return true;
	}
	if(startswith__(name, kw)) {
		std::string s = name.substr(kw.size());
		if(can_stoi__(s)) {
			i = std::stoi(s) - 1;
			return true;
		}
	}
	return false;
}

std::string Item::s__() {
	std::string s;
	s += kw__();
	s += keyword::ARG;
	switch(i_) {
	case IS_ARG:
		break;
	case IS_ARG_LENGTH:
		s += keyword::LENGTH;
		break;
	default:
		s += std::to_string(i_ + 1);
		break;
	}
	for(auto i : tags_) {
		s += keyword::TAG_BEGIN + i + keyword::TAG_END;
	}
	s += kw2__();
	return s;
}

void Item::z2__(int i, Qv *qv2, List &ls, Ret &ret) {
	::arg::List* args = qv2->args_;
	switch(i) {
	case IS_ARG:
		if(args)
			ret.push__(args->all__());
		break;
	case IS_ARG_LENGTH:
		if(args)
			ret.push__(std::to_string(args->a_.size()));
		break;
	case IS_ARG0:
		if(args)
			ret.push__(args->src_is_file_ ? args->src_ : args->src2_);
		break;
	default:
		if(args) {
			if(i >= 0 && i < (int)args->a_.size()) {
				ret.push__(args->a_[i]->val_);
			}
		}
		break;
	}
}

Result2 Item::z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret) {
	Qv *qv2 = &qv;
	Result2 r2 = qv4tags__(tags_, ls, qv2->mods_, nullptr, qv2);
	if(false__(r2))
		return r2;
	z2__(i_, qv2, ls, ret);
	return Ok(true);
}

}}} /* namespace segm */
