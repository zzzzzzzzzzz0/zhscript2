/*
 * result.h
 *
 *  Created on: 2016年8月25日
 *      Author: zzzzzzzzzzz
 */

#ifndef RESULT_H_
#define RESULT_H_

template<typename V, typename E>
class Result {
public:
	V val_;
	E err_;

	static Result* Ok(V val) {
		return new Result {val_:val};
	}
	static Result* Err(E err) {
		return new Result {val_:0, err_:err};
	}
};

#endif /* RESULT_H_ */
