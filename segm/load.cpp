/*
 * load.cpp
 *
 *  Created on: 2016年8月28日
 *      Author: zzzzzzzzzzz
 */

#include "load.h"
#include "../is.h"

namespace segm {

Result2 load__(Ret &ret2, arg::List &args, arg::NameList *nl, All *a, const keyword::Item& kw_by, bool use_part, size_t &i2, Qv &qv, List &ls, Ret &ret) {
	if(a) {
		Result2 r2 = a->z2__(kw_by, use_part, i2, qv, ls, ret2);
		if(false__(r2))
			return r2;
		ret2.one__();

		const Ret_List& rl = ret2.a_;
		size_t len = rl.size();
		if(len == 0)
			return Err("无代码");
		args.src_ = rl[0].val_;
		for(size_t i = 1; i < len; i++)
			args.push__(rl[i].val_);
	}
	if(nl) {
		for(size_t i = 0; i < nl->size() && i < args.a_.size(); i++) {
			args.a_[i]->name_ = (*nl)[i];
		}
	}
	Result2 r2 = ls.z2__(kw_by, &args, &qv, ret);
	if(r2->val_->val_ == IS_RETURN && r2->val_->err_.empty()) {
		return Ok(true);
	}
	return r2;
}

namespace load {

Result2 Item::z_2__(bool src_is_file, Qv &qv, List &ls, Ret &ret) {
	size_t i2 = 0;
	Ret ret2;
	arg::List args;
	args.src_is_file_ = src_is_file;
	return load__(ret2, args, nullptr, &a_, kw__(), false, i2, qv, ls, ret);
}

}} /* namespace segm */
