#include "date.h"
using namespace std;



Date::Date(string date){
	if(date.find(' ') != string::npos){
		vector<string>* dt = c_explode(' ',date);
		this->extractDate(dt->at(0));
		this->extractTime(dt->at(1));
		delete dt;
	}else if(date.find('-') != string::npos){
		this->extractTime(date);
	}else{
		this->extractDate(date);
	}
}

void Date::extractDate(string date){
	vector<string>* dat = c_explode('-',date);
	this->year = (int16_t)atoi(dat->at(0).c_str());
	this->month = (int8_t)atoi(dat->at(1).c_str());
	this->day = (int8_t)atoi(dat->at(2).c_str());
	delete dat;
}

void Date::extractTime(string time){
	vector<string>* dat = c_explode(':',time);
	this->hour = (int8_t)atoi(dat->at(0).c_str());
	this->min = (int8_t)atoi(dat->at(1).c_str());
	this->sec = (int8_t)atoi(dat->at(2).c_str());
	delete dat;
}

int Date::compare(Date d){
	if(this->year != d.year){
		return this->year - d.year;
	}else if(this->month != d.month){
		return this->month - d.month;
	}else if(this->day != d.day){
		return this->day - d.day;
	}else if(this->hour != d.hour){
		return this->hour - d.hour;
	}else if(this->min != d.min){
		return this->min - d.min;
	}
	return this->sec - d.sec;
}