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

#define keyword_kaiyinhao_ 0
#define keyword_biyinhao_ 1
#define keyword_bianliangshi_ 2
#define keyword_bianliangzhong_ 3
#define keyword_zhujieshi_ 7
#define keyword_zhujiezhong_ 8
#define keyword_juhao_ 9
#define keyword_dunhao_ 14
#define keyword_jieheshi_ 16
#define keyword_jiehezhong_ 17
#define keyword_shangji_ 39
#define keyword_equ_ 43
#define keyword_call_ 57
#define keyword_params_ 64
#define keyword_null_ 68
#define keyword_callback_ 69

#define errinfo_src_file_ 7

#define vartype_var_ 0
#define vartype_def_ 1
#define vartype_alias_ 2

}} /* namespace segm */

#endif /* SEGM_FUNC_OLD_H_ */
