#ifndef _DATE_H_
#define _DATE_H_

#include <cstdlib>
#include <cstdint>
#include <string>
#include "../str.h"

using namespace std;

class Date{
	private:
		int8_t day;
		int8_t month;
		int16_t year;
		int8_t hour;
		int8_t min;
		int8_t sec;
	public:
		Date():day(0),month(0),year(0),hour(0),min(0),sec(0){}
		Date(string date);
		int compare(Date d);
	private:
		void extractDate(string date);
		void extractTime(string time);
}

#endif