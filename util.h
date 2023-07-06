/*
 * util.h
 *
 *  Created on: 2016年9月4日
 *      Author: zzzzzzzzzzz
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <functional>
#include <string>

size_t step__(const std::string &s, size_t i, std::function<void(unsigned char c)> fn = nullptr);
int startswith__(const std::string& s, const std::string& s2);
int startswith__(const std::string& s, size_t i, const std::string& s2, size_t &i2);
bool can_stoi__(const std::string &s, bool use_minus = false);
bool can_stod__(const std::string &s);

std::string bad__(unsigned char c);

#ifdef ver_no_std_to_string_
namespace std {

std::string to_string(unsigned char t);
std::string to_string(long t);
std::string to_string(unsigned long t);
std::string to_string(int t);
std::string to_string(unsigned int t);
std::string to_string(long double t);
int stoi(std::string s);
long double stold(std::string s);
long stol(std::string s);
unsigned long stoul(std::string s);

}
#endif

#endif /* UTIL_H_ */
