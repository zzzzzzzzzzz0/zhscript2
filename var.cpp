/*
 * var.cpp
 *
 *  Created on: 2016年8月28日
 *      Author: zzzzzzzzzzz
 */

#include <algorithm>
#include "var.h"

namespace var {

Item* List::get__(const std::string& name, bool can_priv) {
	auto i = std::find_if(a_.begin(), a_.end(), [&](Item* i2) {
		return i2->name_ == name && (!i2->is_priv_ || (can_priv && i2->is_priv_));
	});
	if(i == a_.end()) {
		return nullptr;
	}
	return *i;
}

} /* namespace var */
