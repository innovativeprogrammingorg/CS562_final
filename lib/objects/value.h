#ifndef _VALUE_H_
#define _VALUE_H_

#include <string>
#include <vector>
#include <cstdint>
#include <iostream>
#include "date.h"

using namespace std;


enum VType{
	VINT,
	VFLOAT,
	VDOUBLE,
	VSTRING,
	VBLOB,
	VVECTOR,
	VSTRNUM,
	VDATE
};

enum Func{
	ADD,
	SUB,
	MUL,
	DIV
};

typedef union ValData Val;

class Value{
	public:
		void* v;
		VType type;
		Value();
		Value(void* v,CType type);
		Value(void* v,VType type);
		virtual ~Value();
		string toString();

		int64_t compare(Value v);

		static string getCppType(CType type);
		static Value add(Value v1, Value v2);
		static Value add(vector<Value> v);
		static Value sub(Value v1, Value v2);
		static Value mul(Value v1, Value v2);
		static Value div(Value v1, Value v2);

	private:
		static VType getType(Value v1,Value v2);
		static VType op(Value v1,Value v2,Func op);
};


#endif