/*
 * arg.h
 *
 *  Created on: 2016年8月23日
 *      Author: zzzzzzzzzzz
 */

#ifndef ARG_H_
#define ARG_H_

#include <string>
#include <vector>
#include <memory>

namespace arg {

using NameList = std::vector<std::string>;

class Item {
public:
	std::string val_, name_;
};

using List_List = std::vector<std::shared_ptr<Item>>;

class List {
private:
	std::string all_;
	bool has_mk_all_ = false;
public:
	List_List a_;
	std::string src_, src2_;
	bool src_is_file_ = true;

	void parse__(const std::string& s);
	void push__(const std::string& s);
	const std::string& all__();
	static std::string mk_all__(List_List a, size_t from, size_t to);
};

} /* namespace arg */

#endif /* ARG_H_ */
