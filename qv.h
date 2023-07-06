/*
 * qv.h
 *
 *  Created on: 2016年8月29日
 *      Author: zzzzzzzzzzz
 */

#ifndef QV_H_
#define QV_H_

#include <functional>
#include "arg.h"
#include "var.h"
#include "def.h"
#include "defer.h"

enum class VarTyp {
	Var,
	Def,
	Func,
};

class Qv;
using ModList = std::vector<Qv*>;

class Qv {
public:
	var::List vars_, funcs_;
	def::List defs_;

	arg::List* args_ = nullptr;
	std::string name_, src2_, name2_;
	bool is_mod_ = false;
	std::string free_;
	defer* defer_ = nullptr;
	ModList* mods_ = nullptr;

	Qv *up_;

	Qv(Qv* up = nullptr) : up_(up) {
		i__();
	}
	Qv(arg::List* args, Qv* up) : args_(args), up_(up) {
		i__();
	}
	Qv(const char* name, Qv* up = nullptr) : name_(name), up_(up) {
		i__();
	}
	Qv(Qv &&qv) :
		vars_(std::move(qv.vars_)),
		funcs_(std::move(qv.funcs_)),
		defs_(std::move(qv.defs_)),
		args_(qv.args_),
		name_(qv.name_),
		src2_(qv.src2_),
		is_mod_(qv.is_mod_),
		free_(qv.free_),
		defer_(qv.defer_),
		//mods
		up_(qv.up_) {
		i__();
	}
	~Qv();

	bool this__() {return this == this_;}

	bool var_get__(const std::string& name, bool can_priv2,
			std::function<void(var::Item*, Qv*, bool)> fn2, std::function<bool(Qv*)> fn3,
			VarTyp vt = VarTyp::Var, bool auto_new = false, bool use_up = true);
	var::Item* var_get__(const std::string& name, bool is_test, Qv **qv_var, VarTyp vt = VarTyp::Var,
			bool auto_new = false, bool *is_new = nullptr, bool use_up = true);
	var::Item* var_get2__(const std::string& name, bool *is_new = nullptr) {
		return var_get__(name, false, nullptr, VarTyp::Var, true, is_new, false);
	}
	def::Item* def_get2__(const std::string& name, size_t argc = 0, size_t back_arg = 0,
			bool is_priv = false, bool is_through = false);
	bool for_def__(std::function<bool(def::Item*)> fn);
private:
	void *this_;

	void i__() {
		this_ = this;
	}
};

#endif /* QV_H_ */
