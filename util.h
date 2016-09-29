/*
 * util.h
 *
 *  Created on: 2016年9月4日
 *      Author: zzzzzzzzzzz
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <functional>

size_t step__(const std::string &s, size_t i, std::function<void(unsigned char c)> fn = nullptr);
int startswith__(const std::string& s, const std::string& s2);
int startswith__(const std::string& s, size_t i, const std::string& s2, size_t &i2);
bool can_stoi__(const std::string &s, bool use_minus = false);

std::string bad__(unsigned char c);

#endif /* UTIL_H_ */
