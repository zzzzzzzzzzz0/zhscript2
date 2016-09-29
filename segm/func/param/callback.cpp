/*
 * callback.cpp
 *
 *  Created on: 2016年9月19日
 *      Author: zzzzzzzzzzz
 */

#include "callback.h"
#include "../../load.h"
#include "../old.h"

namespace segm {
namespace func {
namespace param {

int cb_buf_i_ = -1;
#define cb_buf_max_ 128
std::string cb_buf_[cb_buf_max_];
std::string& cb_buf__() {
	if(++cb_buf_i_ >= cb_buf_max_)
		cb_buf_i_ = 0;
	cb_buf_[cb_buf_i_].clear();
	return cb_buf_[cb_buf_i_];
}

const char* callback3_2__(::segm::List* jsq, Qv* shangji, int* err, CallEx*ce,
		const char* src, bool src_is_file, const char* src2, int argc, const char**argv, int from) {
	size_t i2 = 0;
	Ret ret, ret2;
	arg::List args;
	args.src_is_file_ = src_is_file;
	args.src2_ = src2;
	args.src_ = src;
	for(int i = from; i < argc; i++) {
		args.push__(argv[i]);
	}
	Result2 r2 = load__(ret2, args, nullptr, nullptr, keyword::LOAD, false, i2, *shangji, *jsq, ret);
	if(false__(r2)) {
		if(err) {
			*err = jieshiqi_err_;
			if(r2->val_->err_.empty()) {
				switch(r2->val_->val_) {
				case IS_BREAK:
				case IS_CONTINUE:
					*err = jieshiqi_err_go_ - r2->val_->val_;
					return "";
				}
			}
		}
	}
	if(ce) {
		ce->r2_ = r2;
		ce->z_(ret);
	}
	std::string& buf = cb_buf__();
	if(ret.a_.size() > 0)
		buf += ret.a_[0].val_;
	return buf.c_str();
}

Result2 CallbackItem::z__(Qv &qv, ::segm::List &ls, List2 &ls2, CallEx &ce) {
	switch(i_) {
	case 0:
		ls2.push_back((Item2)&ls);
		break;
	case 1:
		ls2.push_back((Item2)&qv);
		break;
	case 11:
		ls2.push_back((Item2)&ce);
		break;
	case 19:
		ls2.push_back((Item2)callback3_2__);
		break;
	default:
		return err__("无效回调号", std::to_string(i_));
	}
	return Ok(true);
}

}}} /* namespace segm */
