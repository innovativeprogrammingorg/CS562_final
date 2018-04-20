#include "average.h"

using namespace std;

template <typename T>
Average<T>::Average(){
	this->count = 0;
	this->sum = 0;
}

template <typename T>
void Average<T>::add(T val){
	this->sum += val;
}

template <typename T>
T Average<T>::value(){
	if(this->count == 0){
		return 0;
	}
	return sum/count;
}
