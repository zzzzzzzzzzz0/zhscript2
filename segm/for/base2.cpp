/*
 * base2.cpp
 *
 *  Created on: 2016年9月10日
 *      Author: zzzzzzzzzzz
 */

#include "base2.h"

namespace segm {
namespace for_ {

void Base2::alt__(segm::Item *&item) {
	std::string name;
	Tag_List tags;
	if(can_cache__(&a_, false, name, tags)) {
		name_ = name;
		has_fix_ = true;
	}
}

Result2 Base2::z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret) {
	if(!has_fix_) {
		Ret ret2;
		for(auto i : a_.a__()) {
			Result2 r2 = i->z__(kw__(), qv, ls, ret2);
			if(false__(r2))
				return r2;
		}
		ret2.one__();
		if(ret2.a_.size() > 0) {
			name_ = ret2.a_[0].val_;
		}
	}
	return Ok2(is__(), name_);
}

}} /* namespace segm */
