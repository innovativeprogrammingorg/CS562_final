#ifndef _AGGREGATE_H_
#define _AGGREGATE_H_

#include <string>
#include <vector>
#include <cstdlib>
#include "../str.h";
using namespace std;

class Aggregate{
	public:
		int group;
		string func;
		string column;
		Aggregate(string aggr);
		virtual ~Aggregate();
		string toESQL();
		string toSQL();
		string toString();
		bool equals(string aggr);
		static bool isAggregate(string aggr);
};



#endif