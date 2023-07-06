/*
 * alias.cpp
 *
 *  Created on: 2016年9月24日
 *      Author: zzzzzzzzzzz
 */

#include "alias.h"

namespace segm {
namespace alias {

void Item::z3__(var::Item* v, const Ret_Item& ri) {
	v->val_ = ri.val_;
	v->tags_ = std::move(ri.tags_);
	v->typ2_ = Typ2::Alias;
}

}} /* namespace segm */
