/*
 * textpars.cpp
 *
 *  Created on: 2018年2月28日
 *      Author: zzzzzzzzzzz
 */

#include "textpars.h"

bool Textpars::can_add__(char c) {
	if(in_rem_ > 0)
		return false;
	if(c >= 0 && c < ' ')
		return in_yuanyang_ > 0 || in_text2_ > 0;
	if(c == ' ')
		return in_text_ > 0 || in_yuanyang_ > 0 || in_text2_ > 0 || in_var_ > 0;
	return true;
}

static const keyword::List
	power_kw_rem_ = {&keyword::REM_BEGIN, &keyword::REM_END,},
	power_kw_yuanyang_ = {&keyword::YUANYANG_BEGIN, &keyword::YUANYANG_END,},
	power_kw_code_ = {
			&keyword::CODE_BEGIN, &keyword::CODE_END,
			&keyword::YUANYANG_BEGIN, &keyword::YUANYANG_END,
			&keyword::TEXT_BEGIN2, &keyword::TEXT_END2,
			&keyword::TEXT_BEGIN, &keyword::TEXT_END,
			&keyword::REM_BEGIN, &keyword::REM_END,
			&keyword::VAR_BEGIN, &keyword::VAR_END,
	},
	power_kw_text_ = {
			&keyword::TEXT_BEGIN, &keyword::TEXT_END,
			&keyword::VAR_BEGIN, &keyword::VAR_END,
	},
	power_kw_text2_ = {
			&keyword::TEXT_BEGIN2, &keyword::TEXT_END2,
			&keyword::VAR_BEGIN, &keyword::VAR_END,
			//需要保持var不解
			&keyword::CODE_BEGIN, &keyword::CODE_END,
			&keyword::YUANYANG_BEGIN, &keyword::YUANYANG_END,
			//让可单
			&keyword::TEXT_BEGIN, &keyword::TEXT_END,
	};

const keyword::Item* Textpars::kw_get__(const std::string &s, bool use_en, size_t i, size_t &kw_len, bool &no) {
	if(in_rem_      > 0) {
		return keyword::get__(s, use_en, i, kw_len, keyword::Id::RemBegin, &power_kw_rem_);
	}
	if(in_yuanyang_ > 0) {
		return keyword::get__(s, use_en, i, kw_len, keyword::Id::YuanyangBegin, &power_kw_yuanyang_);
	}
	if(in_code_     > 0) {
		const keyword::Item* kw = keyword::get__(s, use_en, i, kw_len, keyword::Id::CodeBegin, &power_kw_code_);
		if(kw)
			switch(*kw) {
			case keyword::Id::VarBegin: in_var_++; return nullptr;
			case keyword::Id::VarEnd:   in_var_--; return nullptr;
			default: break;
			}
		return kw;
	}
	if(in_text_     > 0) {
		return keyword::get__(s, use_en, i, kw_len, keyword::Id::TextBegin, &power_kw_text_);
	}
	if(in_text2_    > 0) {
		return keyword::get__(s, use_en, i, kw_len, keyword::Id::TextBegin2, &power_kw_text2_);
	}
	no = true;
	return nullptr;
}

bool Textpars::kw_use__(const keyword::Item* kw, Buf &buf) {
	switch(*kw) {
	case keyword::Id::TextBegin:
	case keyword::Id::TextEnd:
	case keyword::Id::CodeBegin:
	case keyword::Id::CodeEnd:
	case keyword::Id::YuanyangBegin:
	case keyword::Id::YuanyangEnd:
	case keyword::Id::TextBegin2:
	case keyword::Id::TextEnd2:
		if(!is_text_) {
			buf.clear__();
			is_text_ = true;
		}
		break;
	case keyword::Id::RemBegin:
	case keyword::Id::RemEnd:
		break;
	default: return false;
	}
	switch(*kw) {
	case keyword::Id::TextBegin:
		if(in_text_++ || in_code_ > 0 || in_yuanyang_ > 0 || in_text2_ > 0)
			buf.add__(kw->val_);
		break;
	case keyword::Id::TextEnd:
		if(--in_text_ || in_code_ > 0 || in_yuanyang_ > 0 || in_text2_ > 0)
			buf.add__(kw->val_);
		break;
	case keyword::Id::CodeBegin:
		if(in_text_ > 0 || in_code_++ || in_yuanyang_ > 0 || in_text2_ > 0)
			buf.add__(kw->val_);
		break;
	case keyword::Id::CodeEnd:
		if(in_text_ > 0 || --in_code_ || in_yuanyang_ > 0 || in_text2_ > 0)
			buf.add__(kw->val_);
		break;
	case keyword::Id::YuanyangBegin:
		if(in_text_ > 0 || in_yuanyang_++ || in_code_ > 0 || in_text2_ > 0)
			buf.add__(kw->val_);
		break;
	case keyword::Id::YuanyangEnd:
		if(in_text_ > 0 || --in_yuanyang_ || in_code_ > 0 || in_text2_ > 0)
			buf.add__(kw->val_);
		break;
	case keyword::Id::TextBegin2:
		if(in_text_ > 0 || in_text2_++ || in_code_ > 0 || in_yuanyang_ > 0)
			buf.add__(kw->val_);
		break;
	case keyword::Id::TextEnd2:
		if(in_text_ > 0 || --in_text2_ || in_code_ > 0 || in_yuanyang_ > 0)
			buf.add__(kw->val_);
		break;
	case keyword::Id::RemBegin:
		if(in_text_ > 0 || in_yuanyang_ > 0)
			buf.add__(kw->val_);
		else
			in_rem_++;
		break;
	case keyword::Id::RemEnd:
		if(in_text_ > 0 || in_yuanyang_ > 0)
			buf.add__(kw->val_);
		else
			in_rem_--;
		break;
	default: break;
	}
	return true;
}
