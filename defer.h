/*
 * defer.h
 *
 *  Created on: 2016年9月17日
 *      Author: zzzzzzzzzzz
 */

#ifndef DEFER_H_
#define DEFER_H_

#include <functional>
#include <vector>

using DeferItem = std::function<void()>;

class defer {
private:
	std::vector<DeferItem> a_;
public:
	defer(DeferItem i) {
		a_.push_back(i);
	}
	defer() {}
	~defer() {
		for(auto i : a_)
			i();
	}
	void i__(DeferItem i) {
		a_.insert(a_.begin(), i);
	}
};

#endif /* DEFER_H_ */
