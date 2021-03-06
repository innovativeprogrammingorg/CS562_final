#ifndef STR_H
#define STR_H

#include <cstdint>
#include <iostream>
#include <cstdlib>
#include <string>
#include <string.h>
#include <stdarg.h>
#include <vector>
using namespace std;

/**
 * An old string manipulation library I created for something else, 
 * and can be used for this project.
 */
/*************C++ Only Functions*************/
/**
 * See PHP explode
 */
vector<string>* c_explode(char quan,string subject);
vector<string>* explode(string quan,string subject);
/**
 * Similiar to explode, but only splits it once
 */
vector<string>* split(char quan,string subject);
vector<string>* ssplit(string quan,string subject);


string itoa(int i);
string trim(string str);
string str_replace(string search,string replace,string subject);
char* to_cstr(string s);
string ltos(int64_t i);
int strpos_m(string haystack,int args,...);
int64_t count(string haystack, string needle);
char getLast(string str);
int indexOfChar(string haystack, char needle);
/***********C Functions*************/
/**
 * Reverse a string
 * @param  str A C String
 * @return     Reversed Version of the C String
 */
char* str_reverse(char* str);
char* substring(char * subject,size_t index,int length);
char* substr(char * subject,int index);
uint_least8_t strcompare(char * str1, char * str2);
uint_least8_t strcompsub(char * str1,char * str2, size_t index, size_t length);
uint_least8_t strcompsub(string str1,string str2, size_t index, size_t length);
size_t strlength(char * str);
char* concat(char * s1, char * s2, uint8_t mem);
char* concat_all(int args,...);

int64_t strpos(char * haystack, char * needle);

char* substring_f(char * subject,size_t index,size_t length);
char* substr_f(char * subject,size_t index);
char lastChar(char * str);
char* strappend(char s,char * str);
char* stradd(char * str,char s);
char* str_replace(char* search,char* replace,char* subject);




#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef FIRST
#define FIRST 1
#endif

#ifndef SECOND
#define SECOND 2
#endif

#endif