/*
 * call.cpp
 *
 *  Created on: 2016年9月20日
 *      Author: zzzzzzzzzzz
 */

#include "call.h"

namespace segm {
namespace func {

bool call__(const Info* fi, const param::List2 &params, param::Item2 &ret3) {
#if defined( ver_no_asm_ )
	if(fi->params_.size() == 0) {
		if(fi->ret_ == func::param::Typ::Void) {
			((func::VV)fi->addr_)();
		} else {
			ret3 = ((func::UV)fi->addr_)();
		}
	} else {
		if(fi->ret_ == func::param::Typ::Void) {
			func::VA fn = (func::VA)fi->addr_;
			switch(params.size()) {
			case 1:
				fn(params[0]);
				break;
			case 2:
				fn(params[0], params[1]);
				break;
			case 3:
				fn(params[0], params[1], params[2]);
				break;
			case 4:
				fn(params[0], params[1], params[2], params[3]);
				break;
			case 5:
				fn(params[0], params[1], params[2], params[3], params[4]);
				break;
			case 6:
				fn(params[0], params[1], params[2], params[3], params[4], params[5]);
				break;
			case 7:
				fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6]);
				break;
			case 8:
				fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7]);
				break;
			case 9:
				fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8]);
				break;
			case 10:
				fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9]);
				break;
			case 11:
				fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10]);
				break;
			case 12:
				fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11]);
				break;
			case 13:
				fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12]);
				break;
			case 14:
				fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13]);
				break;
			case 15:
				fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14]);
				break;
			case 16:
				fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15]);
				break;
			case 17:
				fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16]);
				break;
			case 18:
				fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17]);
				break;
			case 19:
				fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18]);
				break;
			case 20:
				fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19]);
				break;
			case 21:
				fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19], params[20]);
				break;
			case 22:
				fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19], params[20], params[21]);
				break;
			case 23:
				fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19], params[20], params[21], params[22]);
				break;
			case 24:
				fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19], params[20], params[21], params[22], params[23]);
				break;
			case 25:
				fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19], params[20], params[21], params[22], params[23], params[24]);
				break;
			case 26:
				fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19], params[20], params[21], params[22], params[23], params[24], params[25]);
				break;
			case 27:
				fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19], params[20], params[21], params[22], params[23], params[24], params[25], params[26]);
				break;
			case 28:
				fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19], params[20], params[21], params[22], params[23], params[24], params[25], params[26], params[27]);
				break;
			case 29:
				fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19], params[20], params[21], params[22], params[23], params[24], params[25], params[26], params[27], params[28]);
				break;
			case 30:
				fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19], params[20], params[21], params[22], params[23], params[24], params[25], params[26], params[27], params[28], params[29]);
				break;
			case 31:
				fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19], params[20], params[21], params[22], params[23], params[24], params[25], params[26], params[27], params[28], params[29], params[30]);
				break;
			case 32:
				fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19], params[20], params[21], params[22], params[23], params[24], params[25], params[26], params[27], params[28], params[29], params[30], params[31]);
				break;
			default:
				return false;
			}
		} else {
			func::UA fn = (func::UA)fi->addr_;
			switch(params.size()) {
			case 1:
				ret3 = fn(params[0]);
				break;
			case 2:
				ret3 = fn(params[0], params[1]);
				break;
			case 3:
				ret3 = fn(params[0], params[1], params[2]);
				break;
			case 4:
				ret3 = fn(params[0], params[1], params[2], params[3]);
				break;
			case 5:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4]);
				break;
			case 6:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5]);
				break;
			case 7:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6]);
				break;
			case 8:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7]);
				break;
			case 9:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8]);
				break;
			case 10:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9]);
				break;
			case 11:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10]);
				break;
			case 12:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11]);
				break;
			case 13:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12]);
				break;
			case 14:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13]);
				break;
			case 15:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14]);
				break;
			case 16:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15]);
				break;
			case 17:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16]);
				break;
			case 18:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17]);
				break;
			case 19:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18]);
				break;
			case 20:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19]);
				break;
			case 21:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19], params[20]);
				break;
			case 22:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19], params[20], params[21]);
				break;
			case 23:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19], params[20], params[21], params[22]);
				break;
			case 24:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19], params[20], params[21], params[22], params[23]);
				break;
			case 25:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19], params[20], params[21], params[22], params[23], params[24]);
				break;
			case 26:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19], params[20], params[21], params[22], params[23], params[24], params[25]);
				break;
			case 27:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19], params[20], params[21], params[22], params[23], params[24], params[25], params[26]);
				break;
			case 28:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19], params[20], params[21], params[22], params[23], params[24], params[25], params[26], params[27]);
				break;
			case 29:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19], params[20], params[21], params[22], params[23], params[24], params[25], params[26], params[27], params[28]);
				break;
			case 30:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19], params[20], params[21], params[22], params[23], params[24], params[25], params[26], params[27], params[28], params[29]);
				break;
			case 31:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19], params[20], params[21], params[22], params[23], params[24], params[25], params[26], params[27], params[28], params[29], params[30]);
				break;
			case 32:
				ret3 = fn(params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19], params[20], params[21], params[22], params[23], params[24], params[25], params[26], params[27], params[28], params[29], params[30], params[31]);
				break;
			default:
				return false;
			}
		}
	}
#else
	param::Item2* params2 = new param::Item2[params.size()];
	for(size_t i = 0; i < params.size(); i++)
		params2[i] = params[i];
	[&]() {
		int add = (params.size() - 6);
		if(add <= 0)
			add = 0;
		else {
			if(add % 2 == 1)
				__asm__ volatile ("sub $0x8,%rsp");
			add = (add + 1) / 2 * 16;
		}
		for(int i = params.size(); i >= 7; i--)
			__asm__ volatile ("pushq %0"::"m"(params2[i - 1]));
		switch(params.size()) {
		default:
		case 6: __asm__ volatile ("mov %0,%%r9" ::"m"( params2[5] ));
		case 5: __asm__ volatile ("mov %0,%%r8" ::"m"( params2[4] ));
		case 4: __asm__ volatile ("mov %0,%%rcx"::"m"( params2[3] ));
		case 3: __asm__ volatile ("mov %0,%%rdx"::"m"( params2[2] ));
		case 2: __asm__ volatile ("mov %0,%%rsi"::"m"( params2[1] ));
		case 1: __asm__ volatile ("mov %0,%%rdi"::"m"( params2[0] ));
		case 0: break;
		}
		if(fi->ret_ != func::param::Typ::Void) {
			param::Item2 ret;
			__asm__ volatile (
					"callq *%1" "\n"
					"mov %%rax,%0" "\n"
					"add %2,%%rsp"
					:"=m"( ret ):"m"( fi->addr_ ),"m"( add ));
			ret3 = ret;
		} else {
			__asm__ volatile (
					"callq *%0" "\n"
					"add %1,%%rsp"
					::"m"( fi->addr_ ),"m"( add ));
		}
	}();
	delete params2;
#endif
	return true;
}

}} /* namespace segm */
