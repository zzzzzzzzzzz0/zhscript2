/*
 * callstack.cpp
 *
 *  Created on: 2018年10月14日
 *      Author: zzzzzzzzzzz
 */

#include "../../all.h"
#include "../callex.h"

namespace segm {
namespace func {
namespace param {

void eval__(::segm::List* jsq, Qv* shangji, arg::List &args, CallEx*ce, Ret* ret3);

void callstack__(::segm::List* jsq, Qv* qu, const KwBy* kw_by, const char* code, CallEx*ce, Ret *ret) {
	arg::List args;
	args.src_ = code;
	args.src_is_file_ = false;
	const KwBy* kw_by2 = kw_by;
	for(; kw_by2;) {
		::segm::All* a = kw_by2->a_;
		if(a) {
			for(size_t i = kw_by2->i_; i >= kw_by2->begin_; i--) {
				args.reset1__();
				args.push__(a->a__()[i]->str__());
				try {
					eval__(jsq, qu, args, ce, ret);
				} catch(int e) {
					if(e == -2) {}
					else if(e == -1)
						break;
					else
						return;
				}
				if(i == 0)
					break;
			}
		}
		kw_by2 = kw_by2->up_;
	}
}

}}}
