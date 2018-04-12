#ifndef _AGGREGATE_H_
#define _AGGREGATE_H_

#include <string>
#include <vector>

enum Function = {
	SQL_AVG,
	SQL_COUNT,
	SQL_MIN,
	SQL_MAX,
	SQL_SUM
};

class Aggregate{
	private:
		Function func;
		Expression* exp;
	public:
		Aggregate(Function f,Expression* e);
		virtual ~Aggregate();
		Value* calculate(vector<Value*> arg);
	private:
		Value* sum(vector<Value*> arg);
		Value* count(vector<Value*> arg);
		Value* min(vector<Value*> arg);
		Value* max(vector<Value*> arg);
		Value* avg(vector<Value*> arg);
};



#endif