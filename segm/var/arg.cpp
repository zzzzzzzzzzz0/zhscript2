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
#define IS_ARG00      -4

segm::Item* Item::mk__(const std::string &name, bool use_en, Tag_List& tags, bool is_test) {
	Item *item = nullptr;
	int i;
	if(mk_i__(name, use_en, i))
		item = new Item(i, tags, is_test);
	return (segm::Item*)item;
}

bool Item::mk_i__(const std::string &name, bool use_en, int &i) {
	auto fn = [&](const std::string& kw, const std::string& len) -> bool {
		if(name == kw) {
			i = IS_ARG;
			return true;
		}
		if(name == kw + len) {
			i = IS_ARG_LENGTH;
			return true;
		}
		if(startswith__(name, kw)) {
			std::string s = name.substr(kw.size());
			if(s == "00") {
				i = IS_ARG00;
				return true;
			}
			if(can_stoi__(s)) {
				i = std::stoi(s) - 1;
				return true;
			}
		}
		return false;
	};
	if(fn(keyword::ARG, keyword::LENGTH) || (use_en && fn(keyword::ARG.val_en_, keyword::LENGTH.val_en_)))
		return true;
	return false;
}

std::string Item::s__() {
	std::string s;
	if(!is_test_)
	s += kw__();
	s += keyword::ARG;
	switch(i_) {
	case IS_ARG:
		break;
	case IS_ARG_LENGTH:
		s += keyword::LENGTH;
		break;
	case IS_ARG00:
		s += "00";
		break;
	default:
		s += std::to_string(i_ + 1);
		break;
	}
	for(auto i : tags_) {
		s += keyword::TAG_BEGIN + i + keyword::TAG_END;
	}
	if(!is_test_)
	s += kw2__();
	return s;
}

void Item::z2__(int i, std::function<const char*(const std::string&)> fn_val, Qv *qv2, List &ls, Ret &ret) {
	::arg::List* args = qv2->args_;
	if(!args)
		return;
	switch(i) {
	case IS_ARG:
		ret.push__(args->all__());
		break;
	case IS_ARG_LENGTH:
		ret.push__(std::to_string(args->a_.size()));
		break;
	case IS_ARG0:
		ret.push__(args->src2_);
		break;
	case IS_ARG00:
		ret.push__(args->src_);
		break;
	default:
		if(i >= 0 && i < (int)args->a_.size()) {
			const ::arg::Item& item = args->a_[i];
			//ret.push__(item);
			ret.push__(fn_val(item.val_));
			ret.push__(item.tags_);
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
		if(!badtag && (i_ < 0 || (qv2->args_ && i_ < (int)qv2->args_->a_.size())))
			ret.push__("1");
	} else
		z2__(i_, [](const std::string& val) {return val.c_str();}, qv2, ls, ret);
	return Ok(true);
}

}}} /* namespace segm */
