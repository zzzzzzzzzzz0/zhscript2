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

	if(qv.args_->src_is_file_) {
		qv.args_->src_ = qv.args_->src2_;
		if(name.empty()) {
			name = ls.mk_modname__(qv.args_->src2_);
		}
	} else {
		if(name.empty()) {
			return err__('n');
		}
	}
	{
		Qv *qv2 = &qv;
		if(qv4tags__(name, ls, qv.mods_, nullptr, qv2) != 0)
			return Ok2(IS_RETURN, "");
	}
	qv.name_ = name;
	qv.is_mod_ = true;

	return Ok(true);
}

}} /* namespace segm */
