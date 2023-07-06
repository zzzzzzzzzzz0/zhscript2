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
	if(s == "-zhscript-o-cache") {
		o_cache_ = true;
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

void Debug::o_args__(const arg::List* args) {
	if(/*args->src_is_file_ ||*/ args->src_.size() < 260)
		o__('n', args->src_);
	else
		o__('n', "...");
	o_n__();
	if(!args->src2_.empty()) {
		o__('n', "0) ", args->src2_);
		o_n__();
	}
	for(size_t i = 0; i < args->a_.size(); i++) {
		o__('n', i + 1, ") ", args->a_[i].val_);
		o_n__();
	}
}

void Debug::o_args__(int argc, const char** argv, int from) {
	for(int i = from; i < argc; i++) {
		o__('n', i + 1, ") ", argv[i]);
		o_n__();
	}
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

void o_2__() {}
void o_2__(const char* s) {
	std::cout << s;
}
void o_2__(const std::string &s) {
	std::cout << s;
}
void o_2__(unsigned long s) {
	std::cout << s;
}
void o_2__(char s) {
	std::cout << s;
}
void o_2__(long double s) {
	std::cout << s;
}
void o_2__(bool s) {
	std::cout << s;
}
void o_2__(int s) {
	std::cout << s;
}
void o_2__(unsigned int s) {
	std::cout << s;
}

void o_n__() {
	std::cout << std::endl;
}

Debug debug_;
