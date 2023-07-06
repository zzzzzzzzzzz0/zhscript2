/*
 * result2.h
 *
 *  Created on: 2016年8月26日
 *      Author: zzzzzzzzzzz
 */

#ifndef RESULT2_H_
#define RESULT2_H_

#include <string>
#include <memory>
#include "result.h"

using Result2__ = Result<int, std::string>;
class Result2_ {
public:
	Result2__ val_;
	std::string val2_;
	bool is_true_ = true;
	std::string err_;
};
using Result2 = std::shared_ptr<Result2_>;

bool false__(Result2 r2);
bool falsetrue__(Result2 r2);

Result2 Ok(int val);
Result2 Err(const std::string& err = "");

Result2 Ok2(int val, const std::string& err = "", const std::string& val2 = "", bool is_true = true);

void err2__(Result2 r2);
void err2__(Result2 r2, const char* s);
void err2__(Result2 r2, const std::string& s);
void err2__(Result2 r2, char c);
void err2__(Result2 r2, char* s);
template<typename T, typename... S>
void err2__(Result2 r2, T t, S... s) {
	err2__(r2, t);
	err2__(r2, s...);
}
template<typename... S>
Result2 err__(S... s) {
	Result2 r2 = Err();
	err2__(r2, s...);
	return r2;
}

#endif /* RESULT2_H_ */
