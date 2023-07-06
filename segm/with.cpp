/*
 * with.cpp
 *
 *  Created on: 2017年12月22日
 *      Author: zzzzzzzzzzz
 */

#include "with.h"

namespace segm {
namespace with {

Result2 Item::alt__(segm::Item *&item, bool use_en) {
	const All_List& al = a_.a__();
	size_t end = al.size();
	if(end < 2)
		return err__(kw__().val_, '.');
	segm::Item *end2 = al[--end], *begin = al[0];
	if(end2->kw__() != keyword::Id::Begin || begin->kw__() != keyword::Id::Begin)
		return err__(kw__().val_, '@', keyword::BEGIN.val_);
	return Ok(true);
}

Result2 Item::z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	const All_List& al = a_.a__();
	size_t end = al.size() - 1;
	All *a2 = al[end]->a__(), *a0 = al[0]->a__();
	KwBy kw_by2 {kw__(), a0, &kw_by};
	KwBy kw_by22 {kw__(), a2, &kw_by};
	for(size_t i = 0; i < a2->a__().size(); i++) {
		arg::List args;
		{
			Ret ret2;
			Result2 r2 = a2->z7__(kw_by22, qv, ls, ret2, i, nullptr, nullptr, true);
			ret2.one__();
			if(false__(r2))
				return r2;
			for(auto ri : ret2.a_)
				args.push__(ri.val_, ri.tags_);
		}
		Qv qv2(&args, qv);
		qv2.mods_ = qv->mods_;
		Result2 r2 = a0->z__(kw_by2, &qv2, ls, ret);
		if(false__(r2))
			return r2;
	}
	return Ok(true);
}

}} /* namespace segm */
