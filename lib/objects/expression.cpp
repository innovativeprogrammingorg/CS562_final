#include "expression.h"


Expression::Expression(Column* column,string* variable = nullptr){
	this->column = column;
	this->variable = variable;
}



Expression::~Expression(){
	delete this->column;
	if(this->variable != nullptr){
		delete this->variable;
	}
}