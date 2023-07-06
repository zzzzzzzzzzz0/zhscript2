/*
 * qv.cpp
 *
 *  Created on: 2017年3月21日
 *      Author: zzzzzzzzzzz
 */

#include "qv.h"
#include "../../util.h"

namespace segm {
namespace var {
namespace qv {

segm::Item* Item::mk__(const std::string &name, bool use_en, Tag_List& tags) {
	Item *item = nullptr;
	if(keyword::QV.is__(name, use_en))
		item = new Item(tags);
	return (segm::Item*)item;
}

std::string Item::s__() {
	std::string s;
	s += kw__() + keyword::QV;
	for(auto i : tags_) {
		s += keyword::TAG_BEGIN + i + keyword::TAG_END;
	}
	s += kw2__();
	return s;
}

Result2 Item::z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	Qv *qv2 = qv;
	Result2 r2 = qv4tags__(tags_, qv->args_->use_en_, ls, qv2->mods_, nullptr, &qv2);
	if(false__(r2))
		return r2;
	unsigned long l = (unsigned long)qv2;
	ret.push__(std::to_string(l));
	ret.push__(Typ2::UInt, std::make_shared<UIntRet>(l));
	return Ok(true);
}

}}} /* namespace segm */
