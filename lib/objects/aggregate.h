#ifndef _AGGREGATE_H_
#define _AGGREGATE_H_

#include <string>
#include <vector>
#include <cstdlib>
#include "../str.h"

using namespace std;
/**
 * Represents an aggegate function
 */
class Aggregate{
	public:
		/**
		 * The grouping variable
		 */
		int group;
		/**
		 * The function to be executed
		 */
		string func;
		/**
		 * The column on which the function is evaluated
		 */
		string column;
		Aggregate(string aggr);
		virtual ~Aggregate();
		string toESQL();
		string toSQL();
		string toString();
		string toVar();
		string toABSVar();
		bool equals(string aggr);
		static bool isAggregate(string aggr);
};



#endif