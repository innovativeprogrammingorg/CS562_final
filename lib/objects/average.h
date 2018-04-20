#ifndef _AVERAGE_H_
#define _AVERAGE_H_

using namespace std;

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