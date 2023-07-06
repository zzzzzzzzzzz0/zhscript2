/*
 * textpars.h
 *
 *  Created on: 2018年2月28日
 *      Author: zzzzzzzzzzz
 */

#ifndef TEXTPARS_H_
#define TEXTPARS_H_

#include "keyword.h"
#include "buf.h"

class Textpars {
private:
	int in_text_ = 0, in_code_ = 0, in_yuanyang_ = 0, in_text2_ = 0, in_rem_ = 0;
	bool is_text_ = false;
	int in_var_ = 0;
public:
	bool in_text__() {return in_text_ > 0 || in_code_ > 0 || in_yuanyang_ > 0 || in_text2_ > 0;};
	bool is_text__() {return is_text_;};
	void submit__() {is_text_ = false;}
	bool can_add__(char c);
	const keyword::Item* kw_get__(const std::string &s, bool use_en, size_t i, size_t &kw_len, bool &no);
	bool kw_use__(const keyword::Item* kw, Buf &buf);
};

#endif /* TEXTPARS_H_ */
