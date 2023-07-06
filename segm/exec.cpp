/*
 * exec.cpp
 *
 *  Created on: 2016年9月8日
 *      Author: zzzzzzzzzzz
 */

#include <cstdlib>
#include "exec.h"
#include "../util.h"

namespace segm {
namespace exec {

Result2 Item::z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	Ret ret2;
	{
		KwBy kw_by2 {kw__(), &a_, &kw_by};
		Result2 r2 = a_.z__(kw_by2, qv, ls, ret2);
		ret2.one__();
		if(false__(r2))
			return r2;
	}
	if(ret2.a_.size() == 0)
		return err__('<');
	int i = std::system(ret2.a_[0].val_.c_str());
	switch(kw_by.kw_) {
	case keyword::Id::No:
	case keyword::Id::Guandaodu:
		break;
	default:
		ret.one__();
		ret.push__(std::to_string(i / 256));
		{
			int i2 = i % 256;
			if(i2) {
				ret.dunhao__();
				ret.push__(std::to_string(i2));
			}
		}
		break;
	}
	return Ok(true);
}

}} /* namespace segm */
