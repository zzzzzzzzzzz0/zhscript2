/*
 * alias.cpp
 *
 *  Created on: 2016年9月24日
 *      Author: zzzzzzzzzzz
 */

#include "alias.h"

namespace segm {
namespace alias {

void Item::z_3__(var::Item* v, const Ret_Item& ri) {
	v->typ_ = 'a';

	auto info = std::make_shared<Info>();
	info->ret_.a_.push_back(std::move(ri));
	v->val2_ = info;
}

}} /* namespace segm */
