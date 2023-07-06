/*
 * callback.cpp
 *
 *  Created on: 2016年9月19日
 *      Author: zzzzzzzzzzz
 */

#include <cstdarg>

#include "callback.h"
#include "../../load.h"
#include "../../alias.h"
#include "../../../util.h"
#include "../../../debug.h"
#include "../../../lib.h"
#include "../../../shell2.h"
#include "../../exit.h"
#include "qv_for.h"

extern std::string null_;

namespace segm {
namespace func {
namespace param {

void callstack__(::segm::List* jsq, Qv* qu, const KwBy* kw_by, const char* code, CallEx*ce, Ret *ret);

static bool name2__(const char* name, ::segm::List* jsq, Qv* &qu, std::string &name2) {
	if(!name || !qu)
		return false;
	bool use_en = qu->args_ ? qu->args_->use_en_ : false;
	All* a;
	Result2 r2 = jsq->parse__(name, use_en, &a);
	if(!jsq->ok__(r2))
		return false;
	Ret ret;
	{
		KwBy kw_by2 {keyword::TEXT_BEGIN, a};
		r2 = a->z__(kw_by2, qu, *jsq, ret);
	}
	if(!jsq->ok__(r2))
		return false;
	ret.one__();
	if(ret.a_.size() > 0) {
		Ret_Item &ri = ret.a_[0];
		r2 = qv4tags__(ri.tags_, use_en, *jsq, qu->mods_, nullptr, &qu);
		if(!jsq->ok__(r2))
			return false;
		name2 = ri.val_;
	}
	return true;
}

static int ok__(Result2 r2, CallEx*ce) {
	if(false__(r2)) {
		if(r2->val2_.empty()) {
			switch(r2->val_.val_) {
			case IS_BREAK:
				return -1;
			case IS_CONTINUE:
				return -2;
			}
		}
		switch(r2->val_.val_) {
		case IS_EXIT:
			return -3;
		case IS_RETURN:
			return -4;
		}
		/*o__(0, jsq->err_);
		o_n__();*/
		if(ce) {
			ce->r2_ = r2;
			if(ce->ret_)
				ce->ret_();
		}
		return 0;
	}
	return 1;
}

void eval__(::segm::List* jsq, Qv* shangji, arg::List &args, CallEx*ce, Ret* ret3) {
	Ret ret, ret2;
	size_t i2 = 0;
	KwBy kw_by {keyword::LOAD, nullptr, nullptr, &keyword::CALL};
	Result2 r2 = load__(ret2, args, nullptr, kw_by, shangji, *jsq, ret, i2);
	if(ret3) {
		ret.one__();
		ret3->push__(ret);
		/*for(auto i : ret3->a_)
			o__(0, i.val_);*/
	}
	int ok = ok__(r2, ce);
	if(ok <= 0) {
		throw ok;
	}
}

static int eval__(segm::List *ls, CallEx*ce, arg::List *args, bool auto1, Qv* qv_up, void* attr_1, void* attr_2, std::vector<std::string>* ret) {
	if(auto1) {
		if(qv_up && qv_up->args_)
			args->use_en_ = qv_up->args_->use_en_;
	}
	Ret ret2;
	Result2 r2 = ls->z2__({keyword::NO, nullptr, nullptr, &keyword::CALL}, args, qv_up ? qv_up : &ls->qv_top_, attr_1, attr_2, ret2);
	if(ret) {
		ret2.one__();
		for(auto i : ret2.a_)
			ret->push_back(i.val_);
	}
	int ok = ok__(r2, ce);
	ls->ok__(r2);
	return ok;
}

static int callback4_3__(::segm::List* jsq, CallEx*ce, const char* src,bool src_is_file,const char* src2,Qv* qv_up,
		void* attr_1, void* attr_2, int argc,const char**argv, std::vector<std::string>* ret) {
	arg::List args;
	for(int i = 0; i < argc; i++) {
		const char* s = argv[i];
		args.push__(s ? s : null_);
	}
	args.src_ = src;
	args.src_is_file_ = src_is_file;
	if(src2)
		args.src2_ = src2;
	return eval__(jsq, ce, &args, true, qv_up, attr_1, attr_2, ret);
}
static int callback4__(::segm::List* jsq, const char* src,bool src_is_file,const char* src2,Qv* qv_up,
		int argc,const char**argv, std::vector<std::string>* ret) {
	return callback4_3__(jsq, nullptr, src, src_is_file, src2, qv_up, nullptr, nullptr, argc,argv, ret);
}
static int callback4_4__(::segm::List* jsq, CallEx*ce, const char* src,bool src_is_file,const char* src2,Qv* qv_up,
		void* attr_1, void* attr_2, std::vector<std::string>* argv, std::vector<std::string>* ret) {
	arg::List args;
	for(size_t i = 0; i < argv->size(); i++)
		args.push__((*argv)[i]);
	args.src_ = src;
	args.src_is_file_ = src_is_file;
	if(src2)
		args.src2_ = src2;
	return eval__(jsq, ce, &args, true, qv_up, attr_1, attr_2, ret);
}
static int callback4_2__(::segm::List* jsq, const char* src,bool src_is_file,const char* src2,Qv* qv_up,
		std::vector<std::string>* argv, std::vector<std::string>* ret) {
	return callback4_4__(jsq, nullptr, src, src_is_file, src2, qv_up, nullptr, nullptr, argv, ret);
}

static int cb_buf_i_ = -1;
#define cb_buf_max_ 128
static std::string cb_buf_[cb_buf_max_];
static std::string& cb_buf__() {
	if(++cb_buf_i_ >= cb_buf_max_)
		cb_buf_i_ = 0;
	cb_buf_[cb_buf_i_].clear();
	return cb_buf_[cb_buf_i_];
}

static const char* callback__(::segm::List* jsq, Qv* shangji, int* err, CallEx*ce,
		const char* src, bool src_is_file, const char* src2, arg::List &args, bool bylib) {
	if(!src || !jsq)
		return "";
	args.src_is_file_ = src_is_file;
	if(src2)
		args.src2_ = src2;
	args.src_ = src;
	Ret ret, ret2;
	size_t i2 = 0;
	KwBy kw_by {keyword::LOAD, nullptr, nullptr, &keyword::CALL};
	Result2 r2 = load__(ret2, args, nullptr, kw_by, shangji, *jsq, ret, i2, nullptr, true, false, SIZE_MAX, nullptr, true);
	ret.one__();
	bool use_ce_ret = true;
	if(false__(r2)) {
		if(err) {
			switch(r2->val_.val_) {
			case IS_BREAK:
			case IS_CONTINUE:
				if(r2->val2_.empty())
					use_ce_ret = false;
			case IS_BREAK2:
			case IS_CONTINUE2:
			case IS_EXIT:
			case IS_RETURN:
				*err = jieshiqi_go_ - r2->val_.val_;
				break;
			default:
				*err = 255;
				break;
			}
			if(bylib)
				*err += jieshiqi_err_;
		}
		jsq->ok__(r2);
	} else {
		if(err)
			*err = 0;
	}
	if(ce && use_ce_ret) {
		ce->r2_ = r2;
		if(ce->ret_)
			ce->ret_();
	}
	std::string& buf = cb_buf__();
	if(ret.a_.size() > 0)
		buf += ret.a_[0].val_;
	return buf.c_str();
}

static const char* callback3_2__(::segm::List* jsq, Qv* shangji, int* err, CallEx*ce,
		const char* src, bool src_is_file, const char* src2, int argc, const char**argv, int from) {
	arg::List args;
	for(int i = from; i < argc; i++) {
		const char* s = argv[i];
		args.push__(s ? s : null_);
	}
	return callback__(jsq, shangji, err, ce, src, src_is_file, src2, args, true);
}

static const char* callback2_2__(::segm::List* jsq, Qv* shangji, int* err, CallEx*ce,
		const char* src, bool src_is_file, const char* src2, int argc, ...) {
	arg::List args;
	va_list argv;
	va_start(argv, argc);
	for(int i = 0; i < argc; ++i) {
		char* s = va_arg(argv, char*);
		args.push__(s ? s : null_);
	}
	va_end(argv);
	return callback__(jsq, shangji, err, ce, src, src_is_file, src2, args, true);
}
static const char* callback2__(::segm::List* jsq,Qv* shangji,int* err,
		const char* src,bool src_is_file,int argc,...) {
	arg::List args;
	va_list argv;
	va_start(argv, argc);
	for(int i = 0; i < argc; ++i) {
		char* s = va_arg(argv, char*);
		args.push__(s ? s : null_);
	}
	va_end(argv);
	return callback__(jsq, shangji, err, nullptr, src, src_is_file, nullptr, args, true);
}

extern "C" {

bool ex_new_def__(::segm::List* jsq, Qv* qu, const char* name, const char* val, size_t argc, size_t back_arg, bool is_priv, bool is_through) {
	std::string name2;
	if(!name2__(name, jsq, qu, name2))
		return false;
	qu->def_get2__(name2, argc, back_arg, is_priv, is_through)->val_ = val;
	return true;
}
bool ex_new_var__(::segm::List* jsq, Qv* qu, const char* name, const char* val) {
	std::string name2;
	if(!name2__(name, jsq, qu, name2))
		return false;
	qu->var_get2__(name2)->val_ = val;
	return true;
}
bool ex_new_alias__(::segm::List* jsq, Qv* qu, const char* name, const char* val) {
	std::string name2;
	if(!name2__(name, jsq, qu, name2))
		return false;
	var::Item *v = qu->var_get2__(name2);
	Ret_Item ri;
	ri.val_ = val;
	alias::Item::z3__(v, ri);
	return true;
}

int ex_var_new__(::segm::List* jsq, Qv* qu, const char* name, const char* val, bool readonly, int type, bool is_noparam) {
	switch(type) {
	case vartype_def_:
		if(!ex_new_def__(jsq, qu, name, val, is_noparam ? 0 : SIZE_MAX, 0, false, false))
			return 255;
		break;
	case vartype_alias_:
		if(!ex_new_alias__(jsq, qu, name, val))
			return 255;
		break;
	default:
		if(!ex_new_var__(jsq, qu, name, val))
			return 255;
		break;
	}
	return 0;
}

Qv* l4_new_qu__(Qv* shangji) {
	Qv* qv = new Qv(shangji);
	qv->mods_ = shangji->mods_;
	return qv;
}
void l4_delete_qu__(Qv* qu) {
	delete qu;
}

void ex_ex__(::segm::List* jsq, CallEx*ce, int val, const char* err, const char* name) {
	for_::Base2* i = nullptr;
	switch(val) {
	case IS_EXIT:
		i = new exit::Item();
		break;
	}
	if(i) {
		i->fix_name__(name);
		Ret ret;
		ce->r2_ = i->z__({keyword::NO}, nullptr, *jsq, ret);
		delete i;
	} else
		ce->r2_ = Ok2(val, err, name);
	if(ce->ret_)
		ce->ret_();
}

}

static const char* ex_var__(::segm::List* jsq, Qv* qu,const char* name) {
	if(!name||!jsq||!qu)
		return nullptr;
	std::string name2;
	if(!name2__(name, jsq, qu, name2))
		return nullptr;
	var::Item *v = qu->var_get__(name2, false, nullptr);
	if(!v)
		return nullptr;
	return v->val_.c_str();
}

static const char* ex_err__(::segm::List* l4) {
	return l4->err_.c_str();
}

static const char* ex_errinfo__(::segm::List* l4, int err) {
	if(err >= jieshiqi_err_)
		err -= jieshiqi_err_;
	if(err && err < 255)
		l4->errinfo_ = " err" + std::to_string(err);
	else
		l4->errinfo_.clear();
	return l4->errinfo_.c_str();
}

static void ex_err_clear__(::segm::List* l4) {
	l4->err_.clear();
	l4->errinfo_.clear();
}

static void ex_err_out__(::segm::List* l4, const char* ret, int err, int by) {
	if(err && !l4->is_exit_) {
		std::string s;
		if(ret)
			s += ret;
		s += ex_err__(l4);
		s += ex_errinfo__(l4, err);
		o__(0, s);
		o_n__();
	}
	ex_err_clear__(l4);
}

Item2 ex__(int i) {
	switch(i) {
	case  9: return (Item2)callback2_2__;
	case 19: return (Item2)callback3_2__;
	case -1: return (Item2)callback2__;
	case  6: return (Item2)callback4__;
	case 30: return (Item2)callback4_2__;
	case 31: return (Item2)callback4_3__;
	case 32: return (Item2)callback4_4__;

	case  2: return (Item2)ex_var_new__;
	case 12: return (Item2)ex_new_var__;
	case  3: return (Item2)ex_var__;

	case  7: return (Item2)l4_new_qu__;
	case  8: return (Item2)l4_delete_qu__;

	case  5: return (Item2)ex_var_for__;
	case 15: return (Item2)ex_var_for_1__;
	case 25: return (Item2)ex_qv_for__;

	case 20: return (Item2)ex_err__;
	case 21: return (Item2)ex_err_clear__;
	case 22: return (Item2)ex_errinfo__;
	case 23: return (Item2)ex_err_out__;

	case 26: return (Item2)mk_suidao__;
	case 27: return (Item2)ex_new_def__;
	case 28: return (Item2)ex_new_alias__;
	case 29: return (Item2)ex_ex__;

	case 18: return (Item2)callstack__;
	}
	return 0;
}

Result2 CallbackItem::z__(Qv *qv, ::segm::List &ls, List2 &ls2, CallEx &ce) {
	switch(i_) {
	case  0: ls2.push_back((Item2)&ls); break;
	case 11: ls2.push_back((Item2)&ce); break;

	case  1: ls2.push_back((Item2)qv); break;
	case 14: ls2.push_back((Item2)qv->up_); break;
	case 17: ls2.push_back((Item2)(ls.qv_main_ ? ls.qv_main_ : &ls.qv_top_)); break;

	case 4: case 13: ls2.push_back(0); break;

	default:
		{
			Item2 i2 = ex__(i_);
			if(i2) {ls2.push_back(i2); break;}
		}
		return err__('X', "回调号", std::to_string(i_));
	}
	return Ok(true);
}

extern "C" {

bool l4_new_def__(Lib* l4, Qv* qu, const char* name, const char* val, size_t argc, size_t back_arg, bool is_priv, bool is_through) {
	return ex_new_def__(l4->ls__(), qu, name, val, argc, back_arg, is_priv, is_through);
}
bool l4_new_var__(Lib* l4, Qv* qu, const char* name, const char* val) {
	return ex_new_var__(l4->ls__(), qu, name, val);
}
bool l4_new_alias__(Lib* l4, Qv* qu, const char* name, const char* val) {
	return ex_new_alias__(l4->ls__(), qu, name, val);
}

const char* l4_errinfo__(Lib* l4,int err) {
	return ex_errinfo__(l4->ls__(), err);
}

void l4_err_clear__(Lib* l4) {
	ex_err_clear__(l4->ls__());
}

void l4_err_out__(Lib* l4, const char* ret, int err, int by) {
	ex_err_out__(l4->ls__(), ret, err, by);
}

bool l4_jieshi3__(Lib* l4, Qv* qv_up, std::vector<std::string>* ret) {
	return eval__(l4->ls__(), nullptr, l4->args__(), false, qv_up, nullptr, nullptr, ret);
}

int l4_jieshi__(Lib* l4, Qv* shangji) {
	if(!l4->has_src__())
		return errinfo_src_file_;
	bool ok = eval__(l4->ls__(), nullptr, l4->args__(), false, shangji, nullptr, nullptr, nullptr);
	return ok || l4->ls__()->is_exit_ ? 0 : 255;
}

bool l4_jieshi4__(Lib* l4, const char* src,bool src_is_file,const char* src2,Qv* qv_up,
		int argc,const char**argv, std::vector<std::string>* ret) {
	return callback4__(l4->ls__(), src, src_is_file, src2, qv_up, argc,argv, ret);
}

int l4_jieshi4_2__(Lib* l4, CallEx*ce, const char* src,bool src_is_file,const char* src2,Qv* qv_up,
		std::vector<std::string>* argv, std::vector<std::string>* ret) {
	return callback4_4__(l4->ls__(), ce, src, src_is_file, src2, qv_up, nullptr, nullptr, argv, ret);
}

const char* l4_callback3_2__(Lib* l4,int* err,CallEx*ce,const char* src,bool src_is_file,const char* src2,Qv* shangji,int argc,const char**argv,int from) {
	arg::List args;
	for(int i = from; i < argc; i++) {
		const char* s = argv[i];
		args.push__(s ? s : null_);
	}
	return callback__(l4->ls__(), shangji, err, ce,
			src ? src : l4->args__()->src_.c_str(),
			src ? src_is_file : l4->args__()->src_is_file_, src2, args, false);
}

const char* l4_callback_2__(Lib* l4,int* err,CallEx*ce,const char* src,bool src_is_file,const char* src2,Qv* shangji,int argc,...) {
	arg::List args;
	va_list argv;
	va_start(argv, argc);
	for(int i = 0; i < argc; ++i) {
		char* s = va_arg(argv, char*);
		args.push__(s ? s : null_);
	}
	va_end(argv);
	return callback__(l4->ls__(), shangji, err, ce, src, src_is_file, src2, args, false);
}
const char* l4_jieshi2__(Lib* l4, int* err, const char* src, bool src_is_file, Qv* shangji) {
	CallEx ce;
	return l4_callback3_2__(l4, err, &ce, src, src_is_file, nullptr, shangji ? shangji : &l4->ls__()->qv_top_, 0, nullptr, 0);
}

}

}}} /* namespace segm */
