/*
 * eval.cpp
 *
 *  Created on: 2016年8月25日
 *      Author: zzzzzzzzzzz
 */

#include "eval.h"
#include "../eval.h"
#include "../util.h"
#include "../debug.h"

namespace segm {
namespace eval {

Result2 Item::z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	std::string s;
	size_t max = 10;
	{
		Ret ret2;
		KwBy kw_by2 {kw__(), &a_, &kw_by};
		Result2 r2 = a_.z__(kw_by2, qv, ls, ret2);
		ret2.one__();
		if(false__(r2))
			return r2;
		if(ret2.a_.size() > 0) {
			s = ret2.a_[0].val_;
		}
		if(ret2.a_.size() > 1) {
			const std::string &s2 = ret2.a_[1].val_;
			if(!s2.empty()) {
				if(!can_stoi__(s2))
					return err__('x', s2);
				max = std::stoi(s2);
			}
		}
	}

	auto err = [&](const char* s) {
		if(for_kwby__(kw_by, [&](const keyword::Item& kw) {
			switch(kw) {
			case keyword::Id::Equ:
			case keyword::Id::Guandaojie:
				ret.one__(false);
				ret.push__(s);
				return true;
			default:
				return false;
			}
		}))
			return Ok(true);
		return Err(s);
	};

	::eval::List a;
	::eval::Result2 ret3 = a.parse__(s);
	if(!ret3.val_)
		return err(bad__(ret3.err_).c_str());
	//a.pn__();

	try {
		//sprintf %*L
		s = std::to_string(a.z__());
	} catch(const char* e) {
		return err(e);
	}
	size_t pos = s.rfind('.');
	if(pos != std::string::npos) {
		if(s.size() - pos > max)
			s = s.substr(0, pos + 1 + max);
		for(size_t i = s.size(); i > pos;) {
			char c = s[--i];
			if(c != '0') {
				s = s.substr(0, i + (c == '.' ? 0 : 1));
				break;
			}
		}
	}
	ret.push__(s);
	for_kwby__(kw_by, [&](const keyword::Item& kw) {
		switch(kw) {
		case keyword::Id::Equ:
		case keyword::Id::Guandaojie:
			ret.one__();
			ret.push__("");
			return true;
		default:
			return false;
		}
	});
	return Ok(true);
}

}} /* namespace segm */
