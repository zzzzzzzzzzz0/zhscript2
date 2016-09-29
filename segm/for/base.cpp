/*
 * base.cpp
 *
 *  Created on: 2016年9月10日
 *      Author: zzzzzzzzzzz
 */

#include "base.h"
#include "../../is.h"
#include "../../debug.h"

namespace segm {
namespace for_ {

void Base::alt__(segm::Item *&item) {
	size_t len = a_.a__().size();
	if(len > 0) {
		std::string s;
		Tag_List tags;
		if(can_cache__(&a_, false, s, tags, len - 1)) {
			Ret ret2;
			ret2.push__(s);
			ret2.one__();
			mk_name_count__(ret2);
			has_fix_ = true;
			if(debug_.o_liucheng_) o__({s}, 'C');
		}
	}
}

void Base::mk_name_count__(Ret &ret2) {
	if(use_count__()) {
		std::string count, name;
		bool to_count = true;
		for(auto s : ret2.a_) {
			for(auto c : s.val_) {
				if(to_count && c >= '0' && c <= '9') {
					count += c;
				} else {
					to_count = false;
					name += c;
				}
			}
		}
		if(!count.empty()) {
			count_ = std::stoi(count);
		}
		name_ = name;
	} else {
		name_.clear();
		for(auto s : ret2.a_) {
			name_ += s.val_;
		}
	}
}

Result2 Base::z_2__(segm::Item* item, Qv &qv, List &ls, Ret &ret) {
	for(size_t i = 0; count_ == std::string::npos || i < count_; i++) {
		if(!name_.empty()) {
			qv.var_get__(name_, false, VarTyp::Var, true, false)->val_ = std::to_string(i + 1);
		}
		Result2 r2 = item->z__(kw__(), qv, ls, ret);
		if(is__(IS_BREAK, r2))
			break;
		if(is__(IS_CONTINUE, r2))
			continue;
		if(false__(r2))
			return r2;
	}
	return Ok(true);
}

Result2 Base::z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret) {
	const All_List& a = a_.a__();
	int end = a.size() - 1;
	if(end < 0) {
		return Err("死循环");
	}
	if(end > 0) {
		if(!has_fix_) {
			Ret ret2;
			for(int i = 0; i < end; i++) {
				Result2 r2 = a[i]->z__(kw__(), qv, ls, ret2);
				if(false__(r2))
					return r2;
			}
			ret2.one__();
			mk_name_count__(ret2);
		}
	}
	return z_2__(a[end], qv, ls, ret);
}

}} /* namespace segm */
