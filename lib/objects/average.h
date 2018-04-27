#ifndef _AVERAGE_H_
#define _AVERAGE_H_

using namespace std;
/**
 * A class wrapper for calculating average of items
 * may use any primitive integer or float type
 */
template <typename T>
class Average{
	private:
		int count;
		T sum;
	public:
		Average();
		void add(T val);
		T value();
};

#include "average.tcc"

#endif