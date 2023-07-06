/*
 * tag.cpp
 *
 *  Created on: 2016年8月31日
 *      Author: zzzzzzzzzzz
 */

#include "tag.h"

namespace segm {
namespace tag {

Result2 Item::z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	Ret ret2;
	{
		KwBy kw_by2 {kw__(), &a_, &kw_by};
		Result2 r2 = a_.z__(kw_by2, qv, ls, ret2);
		ret2.one__();
		if(false__(r2))
			return r2;
	}
	std::string s;
	for(auto s2 : ret2.a_) {
		s += s2.val_;
	}
	ret.push_tag__(s);
	return Ok(true);
}

std::string Item::str__() {
	std::string s;
	s += kw__();
	for(auto i : a_.a__()) {
		if(i->kw__() == keyword::TEXT_BEGIN) {
			i->s__(s);
		} else
			s += i->str__();
	}
	s += kw2__();
	return s;
}

}} /* namespace segm */
