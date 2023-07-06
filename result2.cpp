/*
 * result2.cpp
 *
 *  Created on: 2016年8月26日
 *      Author: zzzzzzzzzzz
 */

#include "result2.h"

bool false__(Result2 r2) {
	return r2 && r2->val_.val_ <= 0;
}
bool falsetrue__(Result2 r2) {
	return r2->is_true_;
}

Result2 Ok(int val) {
	return std::make_shared<Result2_>(Result2_ {Result2__::Ok(val)});
}
Result2 Err(const std::string& err) {
	return std::make_shared<Result2_>(Result2_ {Result2__::Err(err)});
}

Result2 Ok2(int val, const std::string& err, const std::string& val2, bool is_true) {
	return std::make_shared<Result2_>(Result2_ {Result2__{val, err}, val2, is_true});
}

void err2__(Result2 r2) {}
void err2__(Result2 r2, const char* s) {
	r2->err_ += s;
}
void err2__(Result2 r2, char* s) {
	r2->err_ += s;
}
void err2__(Result2 r2, char c) {
	switch(c) {
	case '<':
		r2->err_ += "参数不足";
		break;
	case '>':
		r2->err_ += "参数过量";
		break;
	case 'x':
		r2->err_ += "非法格式数据";
		break;
	case 'n':
		r2->err_ += "无名";
		break;
	case 'm':
		r2->err_ += "重名";
		break;
	case 'X':
		r2->err_ += "无效的";
		break;
	case '?':
		r2->err_ += "无法的";
		break;
	case 't':
		r2->err_ += "标注";
		break;
	case '@':
		r2->err_ += "期待";
		break;
	case 'o':
		r2->err_ += "死循环";
		break;
	case '.':
		r2->err_ += "需要更多语句";
		break;
	}
}
#include "keyword.h"
void err2__(Result2 r2, const std::string& s) {
	r2->err_ += keyword::TEXT_BEGIN;
	r2->err_ += s;
	r2->err_ += keyword::TEXT_END;
}
