/*
 * callex.h
 *
 *  Created on: 2018年11月19日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_FUNC_CALLEX_H_
#define SEGM_FUNC_CALLEX_H_

#include "../../result2.h"
#include <functional>

namespace segm {
namespace func {
namespace param {

class CallEx {
public:
	Result2 r2_;
	std::function<void()> ret_ = nullptr;
};

}}}

#endif /* SEGM_FUNC_CALLEX_H_ */
