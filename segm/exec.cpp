/*
 * exec.cpp
 *
 *  Created on: 2016年9月8日
 *      Author: zzzzzzzzzzz
 */

#include <cstdlib>
#include "exec.h"

namespace segm {
namespace exec {

Result2 Item::z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret) {
	Ret ret2;
	{
		Result2 r2 = a_.z__(kw__(), qv, ls, ret2);
		if(false__(r2))
			return r2;
	}
	ret2.one__();
	for(auto s : ret2.a_) {
		int i = std::system(s.val_.c_str());
		switch(kw_by) {
		case keyword::Id::No:
		case keyword::Id::Begin:
			break;
		default:
			ret.one__();
			ret.push__(std::to_string(i));
			break;
		}
	}
	return Ok(true);
}

}} /* namespace segm */
