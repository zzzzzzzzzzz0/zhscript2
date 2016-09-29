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

enum class VarTyp {
	Var,
	Def,
};

class Qv;
using ModList = std::vector<Qv*>;

class Qv {
private:
	var::List vars_;
	def::List defs_;
public:
	arg::List* args_ = nullptr;
	Qv *up_ = nullptr;
	std::string name_;
	bool is_mod_ = false;
	ModList* mods_ = nullptr;

	Qv() {}
	Qv(arg::List* args, Qv* up) : args_(args), up_(up) {}
	Qv(const char* name) : name_(name) {}
	Qv(Qv &&qv) :
		vars_(std::move(qv.vars_)),
		defs_(std::move(qv.defs_)),
		args_(qv.args_),
		up_(qv.up_),
		name_(qv.name_),
		is_mod_(qv.is_mod_),
		mods_(qv.mods_) {}

	var::Item* var_get__(const std::string& name, bool can_priv2, VarTyp vt = VarTyp::Var,
			bool auto_new = false, bool use_up = true);
	bool for_def__(std::function<bool(def::Item*)> fn);
};

#endif /* QV_H_ */
