#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include <string>
#include "column.h"




class Expression{
	public:
		string* variable;
		Column* column;
		Expression(Column* column,string* variable = nullptr);
		virtual ~Expression();
};






#endif