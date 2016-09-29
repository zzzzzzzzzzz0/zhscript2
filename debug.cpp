/*
 * debug.cpp
 *
 *  Created on: 2016年8月24日
 *      Author: zzzzzzzzzzz
 */

#include <iostream>
#include "debug.h"

bool Debug::parse__(const std::string& s) {
	if(s == "-zhscript-o-ansi") {
		o_ansi_ = true;
		return true;
	}
	if(s == "-zhscript-o-tree") {
		o_tree_ = true;
		return true;
	}
	if(s == "-zhscript-o-args") {
		o_args_ = true;
		return true;
	}
	if(s == "-zhscript-o-path") {
		o_path_ = true;
		return true;
	}
	if(s == "-zhscript-o-lc") {
		o_liucheng_ = true;
		return true;
	}
	if(s == "-zhscript-o-if") {
		o_if_ = true;
		return true;
	}
	if(s == "-zhscript-o-ret") {
		o_ret_ = true;
		return true;
	}
	return false;
}

void o_begin__(const char r) {
	if(!r)
		return;
	if(debug_.o_ansi_) {
		std::string head = "\x1b[0;3";
		/*
		白色（7）是关键字色，背景不同区分用途
		蓝色（4）是输入的参数色
		红色（1）是结果，背景区分阶段
		黑色（0）就是输出的一般色
		绿色（2）黄色（3）粉色（5）青色（6）
		*/
		switch(r) {
		case 'k': //key
			head += "7;44"; break;
		case 'x': //exec
			head += "7;40"; break;
		case 'T': //tag
			head += "7;45"; break;
		case 'r': //ret
			head += "7;42"; break;
		case 'R': //ret 值
			head += "0;42"; break;
		case 't': //text
			head += "0;47"; break;
		case 'E': //err
			head += "7;41"; break;
		case 'e': //end 结果
			head += "1;47"; break;
		case 'N': //name
			head += "1;43"; break;
		case 'C': //cache
			head += "1;46"; break;
		case 'g': //gonggong
			head += "1"; break;
		case 'n': //(n) 参数
			head += "4"; break;
		case 'K':
			head += "3;42"; break;
		case 'd': //def
			head += "3;40"; break;
		case 'c': //code
			head += "2"; break;
		default:
			head += "2"; break;
		}
		std::cout << head + "m";
	} else {
		if(r != ' ') {
			std::cout << "{";
			if(r > ' ') {
				std::cout << r << " ";
			}
		}
	}
}
void o_end__(const char r) {
	if(!r)
		return;
	if(debug_.o_ansi_) {
		std::cout << "\x1b[0m";
	} else {
		if(r != ' ') {
			std::cout << "}";
		}
	}
}

void Debug::ptree__(const segm::All* a2, int lvl, size_t lvl2, const char c) {
	if(!a2)
		return;

	const segm::All_List& a = a2->a__();
	size_t end = a.size() - 1;
	size_t i2 = 0;
	size_t lvl3;
	auto fn = [&](const std::string &s, int i3) {
		o_begin__(c);
		head__(lvl, lvl3, i3);
		o__({s});
		o_end__(c);
		o_n__();
	};
	for(auto i : a) {
		lvl3 = lvl2 + (i2 == end ? 1 << lvl : 0);
		fn(i->s__(), 1);
		int lvl1 = lvl + 1;
		ptree__(i->a__(), lvl1, lvl3, c);
		if(i->a2__()) {
			fn(i->kw2__(), 2);
			ptree__(i->a2__(), lvl1, lvl3, c);
		}
		if(i->a3__()) {
			fn(i->kw3__(), 3);
			ptree__(i->a3__(), lvl1, lvl3, c);
		}
		i2++;
	}
}

void Debug::head__(int lvl, size_t lvl2, int i3) {
	for(int i = 1; i <= lvl; i++) {
		bool eot = (lvl2 >> i) % 2, is = i == lvl;
		o__({eot ? (is ? (i3 == 1 ? '\\' : '/') : ' ') : '|'});
		for(int i2 = 0; i2 < 3; i2++) {
			o__({is ? '-' : ' '});
		}
	}
}

void Debug::o_args__(const arg::List* args) {
	if(args->src_is_file_)
		o__({args->src_}, 'n');
	else
		o__({"..."}, 'n');
	o_n__();
	for(size_t i = 0; i < args->a_.size(); i++) {
		auto item = args->a_[i];
		o__({std::to_string(i).c_str(), "/", item->name_.c_str(), ") ", item->val_.c_str()}, 'n');
		o_n__();
	}
}

void Debug::o_args__(int argc, const char** argv, int from) {
	for(int i = from; i < argc; i++) {
		o__({i}, 'n');
		o__({") ", argv[i]}, 'n');
		o_n__();
	}
}

template<typename T>
void o__(std::initializer_list<T> s, const char c) {
	if(s.size() == 0)
		return;
	o_begin__(c);
	for(auto o : s)
		std::cout << o;
	o_end__(c);
}

void o_n__() {
	std::cout << std::endl;
}

Debug debug_;
