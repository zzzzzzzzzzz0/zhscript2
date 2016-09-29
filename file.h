/*
 * file.h
 *
 *  Created on: 2016年9月1日
 *      Author: zzzzzzzzzzz
 */

#ifndef FILE_H_
#define FILE_H_

#include <string>
#include <vector>

class File {
private:
	std::vector<std::string> known_path_, known_path2_;
public:
	std::string abs__(const std::string& src);
	//relative 相对化
	std::string rel__(const std::string& src, const std::string& base, bool rm_ext);

	std::string dir__(const std::string& src);

	std::string get_contents__(const std::string& src);

	void known_path_add__(const std::string& src) {
		known_path_.push_back(dir__(src));
	}
	void known_path_pop__() {known_path_.pop_back();}
	void known_path2_add__(const std::string& src);
	std::string ok_path__(const std::string& src);
};

extern File file_;

#endif /* FILE_H_ */
