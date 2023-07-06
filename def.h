/*
 * def.h
 *
 *  Created on: 2016年9月3日
 *      Author: zzzzzzzzzzz
 */

#ifndef DEF_H_
#define DEF_H_

#include "var.h"

namespace def {

class Item : public var::Item {
public:
	std::string name2_;
	size_t argc_ = SIZE_MAX, back_arg_ = 0;
	bool is_through_ = false;
	arg::NameList arg_names_ = nullptr;
	std::vector<std::string> dunhao3_;
};

class List : public var::List {
};

} /* namespace def */

#endif /* DEF_H_ */
