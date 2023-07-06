/*
 * item1.cpp
 *
 *  Created on: 2016年9月11日
 *      Author: zzzzzzzzzzz
 */

#include "item1.h"

namespace segm {

Result2 Item1::z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	switch(*kw_) {
	case keyword::Id::Juhao:
	case keyword::Id::Douhao:
		for_kwby__(kw_by, [&](const keyword::Item& kw) {
			if(kw == keyword::Id::With) {
				ret.one__();
				return true;
			}
			return false;
		});
		break;
	case keyword::Id::Dunhao:
		ret.dunhao__();
		break;
	default:
		break;
	case keyword::Id::DebugPoint: {
		bool o_X_o = true;
		break; }
	}
	return Ok(true);
}

} /* namespace segm */
