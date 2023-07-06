/*
 * base.cpp
 *
 *  Created on: 2016年9月10日
 *      Author: zzzzzzzzzzz
 */

#include "base.h"
#include "../../is.h"
#include "../../util.h"
#include "../../debug.h"

namespace segm {
namespace for_ {

Result2 Base::alt__(segm::Item *&item, bool use_en) {
	{
		size_t i2 = 0;
		Result2 r2 = mem4tags__(a_, [&](size_t i, const std::string& s) {
			if(use_count__() && i == 0 && can_stoi__(s)) {
				count_ = std::stoi(s);
				count_i_ = i;
				return Ok(true);
			}
			if((use_count__() && i == 1) || i == 0) {
				if(name_i_ == std::string::npos) {
					name_ = s;
					name_i_ = i;
					return Ok(true);
				}
			}
			return err__('X', 't', s);
		}, [&](size_t i) {
			if(use_count__() && i == 0) {
				count_fix_ = false;
				count_i_ = i;
				return Ok(true);
			}
			if((use_count__() && i == 1) || i == 0) {
				name_fix_ = false;
				name_i_ = i;
				return Ok(true);
			}
			return err__('X', 't');
		}, i2);
		if(false__(r2))
			return r2;
		if(use2__()) {
			from_ = i2;
			return r2;
		}
	}

	size_t len = a_.a__().size();
	if(len == 0) {
		return err__('o');
	}
	std::string s;
	Tag_List tags;
	for(from_ = len - 1; from_ > 2; from_--) {
		if(a_.a__()[from_ - 1]->kw__() == keyword::Id::Douhao)
			from_--;
		else
			break;
	}
	if(can_cache__(&a_, false, s, tags, from_)) {
		Ret ret2;
		ret2.push__(s);
		ret2.one__();
		mk_name_count__(ret2, name_, count_);
		has_fix_ = true;
		//if(debug_.o_liucheng_) o__('C', s);
	}
	return Ok(true);
}

void Base::mk_name_count__(Ret &ret2, std::string &name1, size_t &count1) {
	if(use_count__()) {
		std::string count, name;
		bool to_count = true;
		for(auto s : ret2.a_) {
			for(auto c : s.val_) {
				if(to_count && ((c >= '0' && c <= '9') || c == '-')) {
					if(c == '-' && !count.empty()) {
					} else {
						count += c;
						continue;
					}
				}
				to_count = false;
				name += c;
			}
			//break;
		}
		if(count == "-") {
			name = count + name;
		}
		else if(!count.empty()) {
			count1 = count[0] == '-' ? 0 : std::stoi(count);
		}
		name1 = name;
	} else {
		name1.clear();
		for(auto s : ret2.a_) {
			name1 += s.val_;
			break;
		}
	}
}

Result2 Base::z_2__(const std::string &name1, size_t count1, KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	var::Item* name = nullptr;
	if(!name1.empty()) {
		name = qv->var_get2__(name1);
	}
	for(size_t i = 1; count1 == std::string::npos || i <= count1; i++) {
		if(name) {
			name->val_ = std::to_string(i);
		}
		size_t i2 = from_;
		Result2 r2 = a_.z7__(kw_by, qv, ls, ret, i2);
		if(is__(IS_BREAK, name1, r2))
			break;
		if(is__(IS_CONTINUE, name1, r2))
			;
		else if(false__(r2))
			return r2;
		if(name) {
			const std::string &s = name->val_;
			if(can_stoi__(s))
				i = std::stoi(s);
		}
	}
	return Ok(true);
}

Result2 Base::z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	std::string name1 = name_;
	size_t count1 = count_;
	KwBy kw_by2 {kw__(), &a_, &kw_by};
	if(use2__()) {
		if(!count_fix_) {
			Result2 r2 = atoi__(a_, count_i_, kw_by2, qv, ls, [&](const std::string& s) {
				if(!can_stoi__(s))
					return err__('x', s);
				count_ = std::stoi(s);
				return Ok(true);
			});
			if(false__(r2))
				return r2;
		}
		if(!name_fix_) {
			Result2 r2 = atoi__(a_, name_i_, kw_by2, qv, ls, [&](const std::string& s) {
				name_ = s;
				return Ok(true);
			});
			if(false__(r2))
				return r2;
		}
	} else {
		if(from_ != std::string::npos) {
			if(!has_fix_) {
				Ret ret2;
				size_t i2 = 0;
				Result2 r2 = a_.z7__(kw_by2, qv, ls, ret2, i2, &from_);
				ret2.one__();
				if(false__(r2))
					return r2;
				mk_name_count__(ret2, name1, count1);
			}
		}
	}
	kw_by2.s_ = name1;
	return z_2__(name1, count1, kw_by2, qv, ls, ret);
}

}} /* namespace segm */
