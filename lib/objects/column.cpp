#include "column.h"


Column::Column(string name,CType type){
	this->name = name;
	this->type = type;
}

Column::Column(string name,string type){
	this->name = name;
	this->type = Column::getType(type);
}

CType Column::getType(string type){
	if(type.find('varchar')!=string::npos){
		return SQL_VARCHAR;	
	}else if(type.find('char')!=string::npos){
		return SQL_CHAR;
	}else if(type.find('text')!=string::npos){
		return SQL_TEXT;
	}else if(type.find('enum')!=string::npos){
		return SQL_ENUM;
	}else if(type.find('set')!=string::npos){
		return SQL_SET;
	}else if(type.find('unsigned')!=string::npos){
		return SQL_UINT;
	}else if(type.find('int')!=string::npos){
		return SQL_INT;
	}else if(type.find('float')!=string::npos){
		return SQL_FLOAT;
	}else if(type.find('double')!=string::npos){
		return SQL_DOUBLE;
	}else if(type.find('decimal')!=string::npos){
		return SQL_DECIMAL;
	}else if(type.find('datetime')!=string::npos){
		return SQL_DATETIME;
	}else if(type.find('timestamp')!=string::npos){
		return SQL_TIMESTAMP;
	}else if(type.find('time')!=string::npos){
		return SQL_TIME;
	}else if(type.find('date')!=string::npos){
		return SQL_DATE;
	}else if(type.find('year')!=string::npos){
		return SQL_YEAR;
	}else if(type.find('blob')!=string::npos){
		return SQL_BLOB;
	}else if(type.find('numeric')!=string::npos){
		return SQL_NUMERIC;
	}else if(type.find('money')!=string::npos){
		return SQL_MONEY;
	}else if(type.find('real')!=string::npos){
		return SQL_REAL;
	}
	return SQL_BOOL;
}