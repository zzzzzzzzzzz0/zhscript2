/*
 * guandaojie.cpp
 *
 *  Created on: 2018年2月25日
 *      Author: zzzzzzzzzzz
 */

#include "guandaojie.h"
#include "../util.h"

namespace segm {
namespace guandaojie {

Result2 Item::alt__(segm::Item *&item, bool use_en) {
	return mem4tags__(a_, [&](size_t i, const std::string& s) {
		if(is_jie__()) {
			switch(i) {
			case 0: {
				Result2 r2 = stoi__(s, range_.from_);
				if(false__(r2))
					return r2;
				return Ok(true); }
			case 1: {
				Result2 r2 = stoi__(s, range_.to_);
				if(false__(r2))
					return r2;
				return Ok(true); }
			}
		}
		return err__('X', 't', s);
	}, [&](size_t i) {
		if(is_jie__()) {
			switch(i) {
			case 0:
				range_.from_fix_ = false;
				range_.from_i_ = i;
				return Ok(true);
			case 1:
				range_.to_fix_ = false;
				range_.to_i_ = i;
				return Ok(true);
			}
		}
		return err__('X', 't');
	}, i2_);
}

Result2 Item::stoi__(const std::string& s, size_t & i) {
	if(!can_stoi__(s))
		return err__('x', s);
	int i1 = std::stoi(s) - 1;
	if(i1 < 0)
		return err__('x', s);
	i = i1;
	return Ok(true);
}

Result2 Item::z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	KwBy kw_by2 {kw__(), &a_, &kw_by};
	Ret ret2;
	size_t i2 = i2_;
	Result2 r2 = a_.z7__(kw_by2, qv, ls, ret2, i2);
	ret2.one__();
	if(false__(r2))
		return r2;
	if(is_jie__()) {
		size_t from = range_.from_, to = range_.to_;
		if(!range_.from_fix_) {
			Result2 r2 = atoi__(a_, range_.from_i_, kw_by2, qv, ls, [&](const std::string& s) {
				return stoi__(s, from);
			});
			if(false__(r2))
				return r2;
		}
		if(!range_.to_fix_) {
			Result2 r2 = atoi__(a_, range_.to_i_, kw_by2, qv, ls, [&](const std::string& s) {
				return stoi__(s, to);
			});
			if(false__(r2))
				return r2;
		}
		if(from <= to && from < ret2.a_.size()) {
			//std::move
			ret.push__(ret2, from, to);
			return Ok(true);
		}
	}
	ret.push2__(-1);
	return Ok(true);
}

}} /* namespace segm */
