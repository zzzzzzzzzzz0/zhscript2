/*
 * name.cpp
 *
 *  Created on: 2016年9月26日
 *      Author: zzzzzzzzzzz
 */

#include "name.h"

namespace segm {
namespace name {

Result2 Item::z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret) {
	std::string name;
	{
		Ret ret2;
		Result2 r2 = a_.z__(kw__(), qv, ls, ret2);
		if(false__(r2))
			return r2;
		ret2.one__();

		for(auto s : ret2.a_) {
			name += s.val_;
		}
	}
	{
		Qv *qv2 = &qv;
		if(qv4tags__(name, ls, qv.mods_, nullptr, qv2) != 0)
			return err__("重名", name);
	}
	qv.name_ = name;

	return Ok(true);
}

}} /* namespace segm */
