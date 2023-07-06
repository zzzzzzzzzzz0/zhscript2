/*
 * sptr.h
 *
 *  Created on: 2016年9月13日
 *      Author: zzzzzzzzzzz
 */

#ifndef SPTR_H_
#define SPTR_H_

#include <memory>

enum class Typ2 {
	No,
	Alias,
	Dl,
	Func,
	Int,
	UInt,
	Addr,
};

class Sptr {};

using Sptr_ = std::shared_ptr<Sptr>;

#endif /* SPTR_H_ */
