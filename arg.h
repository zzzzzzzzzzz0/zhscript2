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
#include <functional>
#include "tag.h"
#include "equname.h"

namespace arg {

class Name : public Equ_name {
public:
	std::string val_;
};
using NameList = std::shared_ptr<std::vector<Name>>;

bool for_arg_name__(const NameList &names, std::function<bool(const Name&)> fn);

class Item {
public:
	std::string val_;
	Tag_List tags_;
};

class List {
private:
	std::string all_;
	bool has_mk_all_ = false;
public:
	std::vector<Item> a_;
	NameList names_ = nullptr;
	std::string src_, src2_, src3_;
	bool src_is_file_ = true, use_en_ = false;

	void parse__(const std::string& s);
	void push__(const std::string& s) {a_.push_back(Item {s});}
	void push__(const std::string& s, const Tag_List &tl) {a_.push_back(Item {s, std::move(tl)});}
	void reset1__();
	const std::string& all__();
	static std::string mk_all__(const std::vector<Item>& a, size_t from, size_t to);
};

} /* namespace arg */

#endif /* ARG_H_ */
