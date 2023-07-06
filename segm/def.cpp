/*
 * def.cpp
 *
 *  Created on: 2016年9月2日
 *      Author: zzzzzzzzzzz
 */

#include "def.h"
#include "../util.h"
#include "../debug.h"

namespace segm {
namespace def {

using namespace keyword;
static const keyword::List ALL_RESERVED1 = {
		&REM_BEGIN, &REM_END,
		&TEXT_BEGIN, &TEXT_END,
		&VAR_BEGIN, &VAR_END,
		&TAG_BEGIN, &TAG_END,
		&CODE_BEGIN, &CODE_END,
		&YUANYANG_BEGIN, &YUANYANG_END,
		&TEXT_BEGIN2, &TEXT_END2,
		&BEGIN, &END,
		&JUHAO,
		&DOUHAO,
		&MAOHAO,
		&DUNHAO, &DUNHAO2,
		&FOR, &BREAK, &CONTINUE,
		&RANGE, &BREAK2, &CONTINUE2,
		&RETURN,
		&EXIT,
		&IF,
		&DENGYU, &XIAOYUDENGYU, &XIAOYU, &DAYUDENGYU, &DAYU,
		&NOT, &AND, &OR,
		&THEN, &ELSE,
		&SWITCH,
		&WITH,
		&GUANDAOJIE, &GUANDAODU,
		&MOD, &MOD_FREE,
		&NAME,
		&SET, &ALIAS, &DEF, &EQU,
		&HAS,
		&EVAL2,
		&LOAD,
		&EVAL,
		&PRINT, &EXEC,
		&DL, &FUNC,
		&CALL,
		&DBGPOT, &DBGPARPOT,
};

Result2 Item::z_2__(Ret &ret2, Ret &ret3, const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	bool use_en = qv->args_->use_en_;
	Qv *qv2 = qv;
	::def::Item* v;
	bool no_argc = false;
	{
		std::string name;
		Tag_List *tags = nullptr;
		Result2 r2 = name1__(ret2, name, tags);
		if(false__(r2))
			return r2;

		bool is_priv = false, is_through = false;
		size_t argc = SIZE_MAX, back_arg = 0;
		auto get_ba = [&](const std::string &s, const keyword::Item &kw) -> bool {
			size_t kw_len;
			if(kw.starts__(s, use_en, kw_len)) {
				std::string s2 = s.substr(kw_len);
				if(s2.empty()) {
					back_arg = 1;
					return true;
				}
				if(can_stoi__(s2)) {
					back_arg = std::stoi(s2);
					return true;
				}
			}
			return false;
		};
		r2 = qv4tags__(*tags, use_en, ls, qv2->mods_, [&](const std::string &s) {
			if(is__(s, use_en, is_priv))
				return true;
			if(keyword::NO_ARG.is__(s, use_en)) {
				argc = 0;
				return true;
			}
			if(keyword::NO_ARGC.is__(s, use_en)) {
				no_argc = true;
				return true;
			}
			if(keyword::THROUGH.is__(s, use_en)) {
				is_through = true;
				return true;
			}
			if(get_ba(s, keyword::BACK_ARG))
				return true;
			return false;
		}, &qv2);
		if(false__(r2))
			return r2;

		for(auto i : ALL_RESERVED1) {
			if(i->val_ == keyword::PRINT)
				continue;
			if(name.find(i->val_) != std::string::npos) {
				return err__("名", name, keyword::HAS.val_.c_str(), keyword::RESERVED.val_.c_str());
			}
		}

		if(qv->for_def__([&](::def::Item* item) {return startswith__(name, item->name_) == 2;}))
			return err__("名", name, "被覆盖");

		v = qv2->def_get2__(name, argc, back_arg, is_priv, is_through);
	}
	if(ret3.a_.size() > 0) {
		auto i = ret3.a_[0];
		//if(debug_.o_liucheng_) o__('e', i.val_);
		v->val_ = i.val_;
	} else {
		v->val_.clear();
	}
	{
		auto a = ret2.a_;
		int dunhao3 = 0;
		if(a.size() > 1) {
			v->arg_names_ = std::make_shared<std::vector<arg::Name>>();
			v->name_ = v->name2_;
			for(size_t i = 1; i < a.size(); i++) {
				Ret_Item &ri = a[i];
				bool is_dunhao = false, equ_name = false;
				Result2 r2 = qv4tags__(ri.tags_, use_en, ls, nullptr, [&](const std::string &s) {
					if(keyword::DUNHAO3.is__(s, use_en)) {
						is_dunhao = true;
						dunhao3++;
						v->name_ += ri.val_;
						return true;
					}
					if(s == "值") {
						equ_name = true;
						return true;
					}
					return false;
				}, nullptr);
				if(false__(r2))
					return r2;
				if(is_dunhao)
					v->dunhao3_.push_back(ri.val_);
				else {
					arg::Name name{};
					name.val_ = ri.val_;
					name.equ_ = equ_name;
					v->arg_names_->push_back(/*{ri.val_, }*/name);
					v->dunhao3_.push_back("");
				}
			}
			if(v->argc_ == SIZE_MAX && !no_argc) {
				//v->argc_ = v->arg_names_->size();
				v->argc_ = v->dunhao3_.size();
			}
		} else {
			v->arg_names_ = nullptr;
			/*if(!no_argc)
				v->argc_ = SIZE_MAX;*/
		}
		if(!dunhao3)
			v->dunhao3_.clear();
	}

	return Ok(true);
}

}} /* namespace segm */
