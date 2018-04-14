#ifndef _MF_STRUCTURE_H_
#define _MF_STRUCTURE_H_

#include <map>
#include <vector>
#include <string>
#include <cstdint>
#include <cstdlib>

/**
 * For each rpoduct show each month's total sales as percentage of this product's year-long total sales
 * Select product, month, year, sum(X.quantity)/sum(Y.quantity)
 * from Sales
 * group by product, month, year ; X,Y
 * such that
 * X.product = product and X.month = month and X.year = year, 
 * Y.product = product and Y.year = year
 */

using namespace std;

class MFStructure{
	private:
		map<string,vector<Value>*>* data;
		vector<string>* keys;
	public:
		MFStructure();
		MFStructure(vector<string>* keys,map<string,vector<Value>*>* data);
		virtual ~MFStructure();
		void insert(map<string,Value> entry);
		void update(map<string,Value> query,map<string,Value> entry);
		void del(map<string,Value>query);
		string toString();


};

#endif