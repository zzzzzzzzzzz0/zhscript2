/*
 * mod_free.cpp
 *
 *  Created on: 2016年12月25日
 *      Author: zzzzzzzzzzz
 */

#include "mod_free.h"

namespace segm {
namespace mod_free {

Result2 Item::z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	Ret ret2;
	{
		KwBy kw_by2 {kw__(), &a_, &kw_by};
		Result2 r2 = a_.z__(kw_by2, qv, ls, ret2);
		ret2.one__();
		if(false__(r2))
			return r2;
	}

	ModList* mods = qv->mods_;
	for(auto i = mods->begin(); i != mods->end();) {
		Qv *qv2 = *i;
		for(auto name : ret2.a_) {
			if(qv2->name_ == name.val_) {
				i = mods->erase(i);
				if(!qv2->free_.empty()) {
					All* a = nullptr;
					Result2 r2 = ls.parse__(qv2->free_, qv->args_->use_en_, &a);
					if(false__(r2))
						return r2;
					Ret ret3;
					KwBy kw_by3 {kw__(), a, &kw_by};
					r2 = a->z__(kw_by3, qv2, ls, ret3);
					if(false__(r2))
						return r2;
				}
				delete qv2->args_;
				delete qv2;
				qv2 = nullptr;
				break;
			}
		}
		if(qv2)
			i++;
	}

	return Ok(true);
}

}} /* namespace segm */
