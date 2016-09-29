/*
 * tag.cpp
 *
 *  Created on: 2016年8月31日
 *      Author: zzzzzzzzzzz
 */

#include "tag.h"

namespace segm {
namespace tag {

Result2 Item::z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret) {
	Ret ret2;
	{
		Result2 r2 = a_.z__(kw__(), qv, ls, ret2);
		if(false__(r2))
			return r2;
	}
	ret2.one__();
	std::string s;
	for(auto s2 : ret2.a_) {
		s += s2.val_;
	}
	ret.push_tag__(s);
	return Ok(true);
}

}} /* namespace segm */
