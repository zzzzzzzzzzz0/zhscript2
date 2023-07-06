/*
 * buf.h
 *
 *  Created on: 2016年8月31日
 *      Author: zzzzzzzzzzz
 */

#ifndef BUF_H_
#define BUF_H_

#include <string>
#include <functional>

using Buf_clear = std::function<void(const std::string&)>;
using Buf_can_add = std::function<bool(char c)>;

class Buf {
private:
	std::string val_;
	bool add_ = false;
	Buf_clear clear_;
	Buf_can_add can_add_;
public:
	Buf(Buf_clear clear, Buf_can_add can_add) : clear_(clear), can_add_(can_add) {}
	void clear__() {
		if(add_) {
			clear_(val_);
			val_.clear();
			add_ = false;
		}
	}
	void add__(char c) {
		if(!can_add_(c))
			return;
		val_ += c;
		add_ = true;
	}
	void add__(const std::string& s) {
		val_ += s;
		add_ = true;
	}
	bool empty__() {
		return val_.empty();
	}
};

#endif /* BUF_H_ */
