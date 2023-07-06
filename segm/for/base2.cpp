/*
 * base2.cpp
 *
 *  Created on: 2016年9月10日
 *      Author: zzzzzzzzzzz
 */

#include "base2.h"
#include "../../debug.h"

namespace segm {
namespace for_ {

Result2 Base2::alt__(segm::Item *&item, bool use_en) {
	std::string name;
	Tag_List tags;
	if(can_cache__(&a_, false, name, tags)) {
		name_ = name;
		has_fix_ = true;
	}
	return Ok(true);
}

void Base2::z_2__(const std::string &name, const KwBy& kw_by, List &ls, bool &is_true) {
	for(const KwBy* i = &kw_by; i; i = i->up_) {
		//o__(0, i->kw_->val_, i->s_);
		if(i->kw_ == for__() && i->s_ == name) {
			is_true = false;
			break;
		}
		if(i->kw2_ && *i->kw2_ == keyword::CALL && name.empty()) {
			is_true = false;
			break;
		}
	}
}

Result2 Base2::z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	std::string name = name_;
	if(!has_fix_) {
		Ret ret2;
		KwBy kw_by2 {kw__(), &a_, &kw_by};
		Result2 r2 = a_.z__(kw_by2, qv, ls, ret2);
		ret2.one__();
		if(false__(r2))
			return r2;
		if(ret2.a_.size() > 0) {
			name = ret2.a_[0].val_;
		}
	}
	bool is_true = true;
	z_2__(name, kw_by, ls, is_true);
	std::string err = kw__();
	if(!name.empty())
		err += keyword::TEXT_BEGIN + name + keyword::TEXT_END;
	return Ok2(is__(), err, name, is_true);
}

}} /* namespace segm */
