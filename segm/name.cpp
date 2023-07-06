/*
 * name.cpp
 *
 *  Created on: 2016年9月26日
 *      Author: zzzzzzzzzzz
 */

#include "name.h"

namespace segm {
namespace name {

Result2 Item::z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	std::string name, name2;
	{
		Ret ret2;
		{
			KwBy kw_by2 {kw__(), &a_, &kw_by};
			Result2 r2 = a_.z__(kw_by2, qv, ls, ret2);
			ret2.one__();
			if(false__(r2))
				return r2;
		}

		switch(ret2.a_.size()) {
		case 2:
			name2 = ret2.a_[1].val_;
		case 1:
			name = ret2.a_[0].val_;
			break;
		}
	}
	if(!name.empty()) {
		Qv *qv2 = qv;
		switch(qv4tags__(name, qv->args_->use_en_, ls, qv->mods_, nullptr, &qv2)) {
		case 'm': case 'n':
			return err__('m', name);
		case 0:
			break;
		default:
			return err__('?', 't', name);
		}
		qv->name_ = name;
	}
	qv->name2_ = name2;

	return Ok(true);
}

}} /* namespace segm */
