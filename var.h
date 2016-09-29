/*
 * var.h
 *
 *  Created on: 2016年8月28日
 *      Author: zzzzzzzzzzz
 */

#ifndef VAR_H_
#define VAR_H_

#include <string>
#include <vector>
#include "sptr.h"

namespace var {

class Item {
public:
	std::string name_, val_;
	bool is_priv_ = false;
	char typ_ = 0;
	Sptr_ val2_;
};

class List {
public:
	std::vector<Item*> a_;
	Item* get__(const std::string& name, bool can_priv);
};

} /* namespace var */

#endif /* VAR_H_ */
