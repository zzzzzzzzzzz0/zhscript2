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

Result2 Item::z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret) {
	std::string s;
	{
		Ret ret2;
		Result2 r2 = a_.z__(kw__(), qv, ls, ret2);
		if(false__(r2))
			return r2;
		ret2.one__();
		if(ret2.a_.size() > 0) {
			s = ret2.a_[0].val_;
		}
	}

	::eval::List a;
	::eval::Result2* ret3 = a.parse__(s);
	if(!ret3->val_) {
		ret.one__(false);
		ret.push__(bad__(ret3->err_));
	} else {
		//if(debug_.o_liucheng_) a.pn__();

		//sprintf %*L
		s = std::to_string(a.z__());
		for(size_t i = s.size(); i > 0;) {
			char c = s[--i];
			if(c != '0') {
				s = s.substr(0, i + (c == '.' ? 0 : 1));
				break;
			}
		}
		ret.push__(s);
		ret.one__();
		ret.push__("");
	}
	return Ok(true);
}

}} /* namespace segm */
