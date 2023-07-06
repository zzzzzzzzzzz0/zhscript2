/*
 * mod_.cpp
 *
 *  Created on: 2016年8月31日
 *      Author: zzzzzzzzzzz
 */

#include "mod_.h"
#include "../is.h"

namespace segm {
namespace mod {

void Item::other__(Qv *qv, List &ls) {
	qv->up_ = &ls.qv_top_;

	arg::List* args = qv->args_;
	qv->args_ = new arg::List();
	qv->args_->use_en_ = args->use_en_;
}

Result2 Item::z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	Ret ret2;
	{
		KwBy kw_by2 {kw__(), &a_, &kw_by};
		Result2 r2 = a_.z__(kw_by2, qv, ls, ret2);
		ret2.one__();
		if(false__(r2))
			return r2;
	}

	std::string name;
	if(ret2.a_.size() > 0)
		name = ret2.a_[0].val_;
	if(name.empty()) {
		if(qv->args_->src_is_file_)
			name = ls.mk_modname__(qv->args_->src2_);
		else
			return err__('n');
	}
	bool use_en = qv->args_->use_en_;
	{
		Qv *qv2 = qv;
		switch(qv4tags__(name, use_en, ls, qv->mods_, nullptr, &qv2)) {
		case 'm':
			return Ok2(IS_RETURN);
		case 'n':
			return err__('m', name);
		case 0:
			break;
		default:
			return err__('?', 't', name);
		}
	}
	qv->name_ = name;
	qv->src2_ = qv->args_->src2_;
	//qv->args_->src2_ = name;
	qv->is_mod_ = true;
	if(ret2.a_.size() > 1) {
		qv->free_ = ret2.a_[1].val_;
		/*qv.defer_ = new defer([&]() {
			All* a = nullptr;
			Result2 r2 = ls.parse__(qv.free_, use_en, &a);
			if(false__(r2))
				return;
			Ret ret3;
			r2 = a->z__(kw__(), qv, ls, ret3);
			if(false__(r2))
				return;
		});*/
	}

	return Ok(true);
}

}} /* namespace segm */
