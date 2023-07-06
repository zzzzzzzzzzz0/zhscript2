/*
 * qv_for.h
 *
 *  Created on: 2018年10月13日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_FUNC_PARAM_QV_FOR_H_
#define SEGM_FUNC_PARAM_QV_FOR_H_

#include "../old.h"

namespace segm {
namespace func {
namespace param {

typedef int (*callback___)(int argc,...);

void ex_qv_for__(::segm::List* jsq, Qv* qu, Qv* qu_e, const char* code, const char* flag, int max, int min, CallEx*ce, Ret *ret);
void ex_var_for__(Qv* qu,callback___ cb);
void ex_var_for_1__(Qv* qu,callback___ cb,int max);

}}}

#endif /* SEGM_FUNC_PARAM_QV_FOR_H_ */
