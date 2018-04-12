#include "value.h"

using namespace std;

Value::Value(){
	this->v = nullptr;
	this->type = VINT;
}

Value::Value(void* v,CType type){
	this->v = v;
	switch(type){
		case SQL_CHAR:
		case SQL_VARCHAR:
		case SQL_TEXT:
		{
			this->type = VSTRING;
			break;
		}
		case SQL_BLOB:
		{
			this->type = VBLOB;
			break;
		}
		case SQL_ENUM:
		case SQL_SET:
		{
			this->type = VVECTOR;
			break;
		}
		case SQL_YEAR:
		case SQL_INT:
		case SQL_TIMESTAMP:
		case SQL_UINT:
		{
			this->type = VINT;
			break;
		}
	
		case SQL_FLOAT:
		{
			this->type = VFLOAT;
			break;
		}
		case SQL_DOUBLE:
		{
			this->type = VDOUBLE;
			break;
		}
		case SQL_DECIMAL:
		case SQL_NUMERIC:
		case SQL_MONEY:
		case SQL_REAL:
		{
			this->type = VSTRNUM;
			break;
		}
		case SQL_DATE:
		case SQL_DATETIME:
		case SQL_TIME:
		{
			this->type = VDATE;
			break;
		}
		
	}
}

Value::Value(void* v,VType type){
	this->v = v;
	this->type = type;
}
Value::~Value(){

}

string Value::toString(){

}

int64_t Value::compare(Value v){
	if(v.type != this->type){
		throw "Error: the values cannot be compared";
	}
	switch(this->type){
		case VDATE:
			return ((Date*)this->v)->compare((Date*)v.v) == 0;
		case VSTRNUM:
		case VSTRING:
			return ((string*)(this->v))->compare((string*)v.v) == 0;
		case VINT:
			if((int64_t) *(v.v) != (int64_t) *(this->v)){
				return 
			}
		case VFLOAT:
		case VDOUBLE:
			
		case VBLOB:
		case VVECTOR:
			return false;
		default:
			return false;
	}
}


/**
 * Static methods
 */
VType Value::getType(Value v1,Value v1){
	
	if(v1.type == v2.type){
		return v1.type;
	}

	if(v2.type == VSTRNUM || v1.type == VSTRNUM){
		return VSTRNUM;
	}

	return VDOUBLE;
}

string Value::getCppType(CType type){
	switch(type){
		case SQL_CHAR:
		case SQL_VARCHAR:
		case SQL_TEXT:
		case SQL_DECIMAL:
		case SQL_NUMERIC:
		case SQL_MONEY:
		case SQL_REAL:
		{
			return "string";
		}
		case SQL_BLOB:
		{
			return "uint8_t[10000]";
		}
		case SQL_ENUM:
		case SQL_SET:
		{
			return "vector<string>";
		}
		case SQL_YEAR:
		case SQL_INT:
		case SQL_TIMESTAMP:
		case SQL_UINT:
		{
			return "int64_t";
		}
	
		case SQL_FLOAT:
		{
			return "float";
		}
		case SQL_DOUBLE:
		{
			return "double";
		}
		case SQL_DATE:
		case SQL_DATETIME:
		case SQL_TIME:
		{
			return "Date";
		}
		
	}
}

Value Value::add(Value v1, Value v2){
	return Value::op(v1,v2,ADD);
}

Value Value::add(vector<Value> v){
	vector<Value>::iterator it = v.begin();
	Vector out = *it;

	for(it++;it != v.end();it++){
		out = Value::add(out,*it);
	}
	return out;
}

Value Value::sub(Value v1, Value v2){
	return Value::op(v1,v2,SUB);
}


Value Value::mul(Value v1, Value v2){
	return Value::op(v1,v2,MUL);
}


Value Value::div(Value v1, Value v2){
	return Value::op(v1,v2,DIV);	
}



Value Value::op(Value v1, Value v2, Func op){
	Value out;
	out.type = Value::getType(v1,v2);
	switch(v1.type){
		case VINT:
			switch(v2.type){
				case VINT:
				{
					int64_t i = *((int64_t*)v1.v);
					int64_t j = *((int64_t*)v2.v);
					int64_t* res = (int64_t*)malloc(sizeof(int));
					switch(op){
						case ADD:
							*res = i + j; 
							break;
						case SUB:
							*res = i - j; 
							break;
						case MUL:
							*res = i * j; 
							break;
						case DIV:
							*res = i / j; 
							break;
					}
					
				}
				case VFLOAT:
				{
					int64_t i = *((int64_t*)v1.v);
					float j = *((float*)v2.v);
					double* res = (double*)malloc(sizeof(double));
					switch(op){
						case ADD:
							*res = i + j; 
							break;
						case SUB:
							*res = i - j; 
							break;
						case MUL:
							*res = i * j; 
							break;
						case DIV:
							*res = i / j; 
							break;
					} 
				}
				case VDOUBLE:
				{
					int64_t i = *((int64_t*)v1.v);
					double j = *((double*)v2.v);
					double* res = (double*)malloc(sizeof(double));
					switch(op){
						case ADD:
							*res = i + j; 
							break;
						case SUB:
							*res = i - j; 
							break;
						case MUL:
							*res = i * j; 
							break;
						case DIV:
							*res = i / j; 
							break;
					} 
				}
				case VSTRNUM:
				{

				}
			}
		
		case VFLOAT:
			switch(v2.type){
				case VINT:
				{
					float i = *((float*)v1.v);
					int64_t j = *((int64_t*)v2.v);
					double* res = (double*)malloc(sizeof(double));
					switch(op){
						case ADD:
							*res = i + j; 
							break;
						case SUB:
							*res = i - j; 
							break;
						case MUL:
							*res = i * j; 
							break;
						case DIV:
							*res = i / j; 
							break;
					}
				}
				case VFLOAT:
				{
					float i = *((float*)v1.v);
					float j = *((float*)v2.v);
					double* res = (double*)malloc(sizeof(double));
					switch(op){
						case ADD:
							*res = i + j; 
							break;
						case SUB:
							*res = i - j; 
							break;
						case MUL:
							*res = i * j; 
							break;
						case DIV:
							*res = i / j; 
							break;
					}
				}
				case VDOUBLE:
				{
					float i = *((float*)v1.v);
					double j = *((double*)v2.v);
					double* res = (double*)malloc(sizeof(double));
					switch(op){
						case ADD:
							*res = i + j; 
							break;
						case SUB:
							*res = i - j; 
							break;
						case MUL:
							*res = i * j; 
							break;
						case DIV:
							*res = i / j; 
							break;
					}
				}
				case VSTRNUM:
				{

				}
			}
		case VDOUBLE:
			switch(v2.type){
				case VINT:
				{
					double i = *((double*)v1.v);
					int64_t j = *((int64_t*)v2.v);
					double* res = (double*)malloc(sizeof(double));
					switch(op){
						case ADD:
							*res = i + j; 
							break;
						case SUB:
							*res = i - j; 
							break;
						case MUL:
							*res = i * j; 
							break;
						case DIV:
							*res = i / j; 
							break;
					}
				}
				case VFLOAT:
				{
					double i = *((double*)v1.v);
					float j = *((float*)v2.v);
					double* res = (double*)malloc(sizeof(double));
					switch(op){
						case ADD:
							*res = i + j; 
							break;
						case SUB:
							*res = i - j; 
							break;
						case MUL:
							*res = i * j; 
							break;
						case DIV:
							*res = i / j; 
							break;
					} 
				}
				case VDOUBLE:
				{
					double i = *((double*)v1.v);
					double j = *((double*)v2.v);
					double* res = (double*)malloc(sizeof(double));
					switch(op){
						case ADD:
							*res = i + j; 
							break;
						case SUB:
							*res = i - j; 
							break;
						case MUL:
							*res = i * j; 
							break;
						case DIV:
							*res = i / j; 
							break;
					} 
				}
				case VSTRNUM:
				{

				}
			}
		case VSTRNUM:
		{
			cout<<"Numbers represented as strings is not currently supported!"<<endl;
		}
	}
	return out;	

}