/*
 * old.h
 *
 *  Created on: 2016年9月20日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_FUNC_OLD_H_
#define SEGM_FUNC_OLD_H_

#include "../../is.h"

namespace segm {
namespace func {

#define jieshiqi_err_ 10000
#define jieshiqi_go_   1000
#define jieshiqi_err_go_ jieshiqi_err_+jieshiqi_go_

#define keyword_break_     -IS_BREAK
#define keyword_continue_  -IS_CONTINUE
#define keyword_break2_    -IS_BREAK2
#define keyword_continue2_ -IS_CONTINUE2
#define keyword_end_       -IS_EXIT
#define keyword_exit_      -IS_RETURN

}} /* namespace segm */

#endif /* SEGM_FUNC_OLD_H_ */
