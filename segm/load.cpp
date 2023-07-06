/*
 * load.cpp
 *
 *  Created on: 2016年8月28日
 *      Author: zzzzzzzzzzz
 */

#include "load.h"
#include "../is.h"
#include "../util.h"

namespace segm {
namespace load {

Result2 Item::alt__(segm::Item *&item, bool use_en) {
	return mem4tags__(a_, [&](size_t i, const std::string& s) {
		if(s == "en") {
			use_en_ = true;
			return Ok(true);
		}
		return err__('X', 't', s);
	}, nullptr, i2_);
}

Result2 Item::z_2__(bool src_is_file, const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	Ret ret2;
	arg::List args;
	args.src_is_file_ = src_is_file;
	size_t i2 = i2_;
	bool auto1 = true;
	if(use_en_) {
		args.use_en_ = true;
		auto1 = false;
	}
	KwBy kw_by2 {kw__(), &a_, &kw_by};
	return load__(ret2, args, &a_, kw_by2, qv, ls, ret, i2, nullptr, auto1);
}

int Item::is_return__(Result2 r2) {
	if(r2->val_.val_ == IS_RETURN) {
		if(r2->val2_.empty())
			return 1;
		if(can_stoi__(r2->val2_))
			return 2;
		return 3;
	}
	return 0;
}

}

Result2 load__(Ret &ret2, arg::List &args, All *a, KwBy& kw_by, Qv *qv, List &ls, Ret &ret,
		size_t &i2, const size_t *end, bool auto1, bool use_part, size_t argc_max, std::vector<std::string> *dunhao3, bool is_through) {
	if(a) {
		Result2 r2 = a->z7__(kw_by, qv, ls, ret2, i2, end, nullptr, use_part, use_part, argc_max, dunhao3);
		if(i2 > 0) {
			size_t i21 = i2 - 1;
			const All_List& a1 = a->a__();
			if(i21 < a1.size())
				if(a1[i21]->kw__() == keyword::EVAL2)
					ret2.clear_push2__();
		}
		ret2.one__();
		if(false__(r2))
			return r2;

		const Ret_List& rl = ret2.a_;
		size_t len = rl.size();
		if(len == 0)
			return Ok(true);
		args.src_ = rl[0].val_;
		for(size_t i = 1; i < len; i++) {
			const Ret_Item &ri = rl[i];
			args.push__(ri.val_, ri.tags_);
		}
	}
	if(auto1) {
		if(qv->args_)
			args.use_en_ = qv->args_->use_en_;
	}
	Result2 r2 = ls.z2__(kw_by, &args, qv, nullptr, nullptr, ret);
	switch(load::Item::is_return__(r2)) {
	case 1:
		if(!is_through)
			return Ok(true);
		break;
	case 2: case 3:
		if(r2->val2_ == qv->name2_)
			return Ok(true);
		break;
	}
	return r2;
}

void full_args__(def::Item* di, const KwBy& kw_by, arg::List& args) {
	args.src_is_file_ = false;
	args.src2_ = di->name_;
	args.src3_ = kw_by.kw_;
	args.names_ = di->arg_names_;
}
void full_ret2__(def::Item* di, Ret &ret2) {
	ret2.push__(di->val_);
	ret2.one__();
}

} /* namespace segm */
