/*
 * callback.h
 *
 *  Created on: 2016年9月19日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_FUNC_PARAM_CALLBACK_H_
#define SEGM_FUNC_PARAM_CALLBACK_H_

#include "../param.h"

namespace segm {
namespace func {
namespace param {

class CallbackItem : Item {
public:
	int i_;
	CallbackItem(int i) : Item(Typ::Callback), i_(i) {}
	Result2 z__(Qv &qv, ::segm::List &ls, List2 &ls2, CallEx &ce);
};

}}} /* namespace segm */

#endif /* SEGM_FUNC_PARAM_CALLBACK_H_ */
