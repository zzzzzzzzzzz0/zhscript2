/*
 * qv_for.cpp
 *
 *  Created on: 2018年10月13日
 *      Author: zzzzzzzzzzz
 */

#include "../../all.h"
#include "../callex.h"
#include "qv_for.h"

namespace segm {
namespace func {
namespace param {

void eval__(::segm::List* jsq, Qv* shangji, arg::List &args, CallEx*ce, Ret* ret3);

void ex_qv_for__(::segm::List* jsq, Qv* qu, Qv* qu_e, const char* code, const char* flag, int max, int min, CallEx*ce, Ret *ret) {
	bool has_qv = false, has_arg = false, has_mod = false, has_src_is = false, use_src_siz = false,
			has_var = false, has_val = false, has_def = false, has_def_val = false, has_func = false,
			has_i = true, has_priv = false;
	if(flag) {
		for(; *flag; flag++) {
			switch(*flag) {
			case 'q': has_qv = true; break;
			case 'a': has_arg = true; break;
			case 'v': has_var = true; break;
			case 'V': has_val = true; break;
			case 'f': has_func = true; break;
			case 'd': has_def = true; break;
			case 'D': has_def_val = true; break;
			case 'm': has_mod = true; break;
			case 's': has_src_is = true; break;
			case 'S': use_src_siz = true; break;
			case 'p': has_priv = true; break;
			case '0': has_i = false; break;
			default:
				ce->r2_ = err__('X', flag);
				if(ce->ret_)
					ce->ret_();
				return;
			}
		}
	}
	arg::List args;
	args.src_ = code;
	args.src_is_file_ = false;
	int i=0;
	auto fn = [&](Qv *qv) {
		args.reset1__();
		if(has_i) {
			args.push__("i");
			args.push__(std::to_string(i));
			eval__(jsq, qu_e, args, ce, ret);
		}
		if(has_qv) {
			args.reset1__();
			if(has_i)
				args.push__("q");
			args.push__(qv->name_);
			args.push__(qv->name2_);
			eval__(jsq, qu_e, args, ce, ret);
		}
		if(has_arg && !qv->is_mod_) {
			arg::List* args2 = qv->args_;
			if(args2) {
				args.reset1__();
				if(has_i)
					args.push__("a");
				//args.push__(args2->src2_);
				if(has_src_is)
					args.push__(args2->src_is_file_ ? "1" : "");
				args.push__(args2->src_is_file_ || !use_src_siz || args2->src_.size() < 150 ? args2->src_ : "...");
				for(auto i2 : args2->a_)
					args.push__(i2.val_);
				eval__(jsq, qu_e, args, ce, ret);
			}
		}
		if(has_var)
		for(var::Item *v : qv->vars_.a_) {
			if(v->is_priv_ && !has_priv)
				continue;
			args.reset1__();
			if(has_i)
				args.push__("v");
			args.push__(v->name_);
			if(has_val)
				args.push__(v->val_);
			eval__(jsq, qu_e, args, ce, ret);
		}
		if(has_func)
		for(var::Item *v : qv->funcs_.a_) {
			if(v->is_priv_ && !has_priv)
				continue;
			args.reset1__();
			if(has_i)
				args.push__("f");
			args.push__(v->name_);
			eval__(jsq, qu_e, args, ce, ret);
		}
		if(has_def)
		for(var::Item *v : qv->defs_.a_) {
			if(v->is_priv_ && !has_priv)
				continue;
			def::Item *d = (def::Item *)v;
			args.reset1__();
			if(has_i)
				args.push__("d");
			args.push__(d->name_);
			args.push__(d->argc_ == std::string::npos ? keyword::NO_ARGC : std::to_string(d->argc_));
			if(has_def_val)
				args.push__(v->val_);
			eval__(jsq, qu_e, args, ce, ret);
		}
	};
	ModList* mods = qu_e->mods_;
	Qv* qv = qu;
	for(;;i++){
		if(!qv || (max>=0&&i>=max)) {
			if(has_mod && mods) {
				for(auto i2 : *mods) {
					try {
						fn(i2);
					} catch(int ret) {
						if(ret == -2) {}
						else if(ret == -1)
							break;
						else
							return;
					}
				}
			}
			break;
		}
		if(i >= min) try {
			fn(qv);
		} catch(int ret) {
			if(ret == -2) {}
			else if(ret == -1)
				break;
			else
				return;
		}
		qv = qv->up_;
	}
}

void ex_var_for_1__(Qv* qu,callback___ cb,int max){
	if(!qu||!cb)
		return;
	auto fn2 = [&](int ret) {
		if(ret)
			throw ret;
	};
	auto fn = [&](Qv *qv) {
		{
			auto args = qv->args_;
			if(args){
				fn2(cb(3,"0", args->src_.c_str(),args->src_is_file_?"1":"0"));
				for(size_t i = 0; i < args->a_.size(); i++)
					fn2(cb(4,"1", "a", std::to_string(i + 1).c_str(), args->a_[i].val_.c_str()));
			}else
				fn2(cb(2,"0",qv->name_.c_str()));
		}
		for(var::Item *v : qv->vars_.a_) {
			try {
				fn2(cb(3, "1", "v", v->name_.c_str()));
				fn2(cb(2, "2", v->val_.c_str()));
			} catch(int ret) {
				if(ret == jieshiqi_err_go_+keyword_continue_) {
				}
				else if(ret == jieshiqi_err_go_+keyword_break_)
					break;
				else
					throw ret;
			}
		}
		for(var::Item *v : qv->funcs_.a_)
			fn2(cb(3, "1", "f", v->name_.c_str()));
		for(var::Item *v : qv->defs_.a_) {
			def::Item *di = (def::Item *)v;
			fn2(cb(3, "1", "d", di->name_.c_str()));
			fn2(cb(2, "2", v->val_.c_str()));
		}
	};
	ModList* mods = qu->mods_;
	for(int i=0;;i++){
		try {
			if(!qu || (max>=0&&i>=max)) {
				if(mods) {
					for(auto i2 : *mods) {
						fn(i2);
					}
				}
				break;
			}
			fn(qu);
		} catch(int ret) {
			if(ret == jieshiqi_err_go_+keyword_continue_) {
			}
			else if(ret == jieshiqi_err_go_+keyword_break_)
				break;
			else
				throw ret;
		}
		qu = qu->up_;
	}
}
void ex_var_for__(Qv* qu,callback___ cb) {ex_var_for_1__(qu,cb,-1);}

}}}
