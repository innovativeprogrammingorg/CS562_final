#ifndef _QUERY_PARSER_H_
#define _QUERY_PARSER_H_

#include <istream>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "../debug.h"
#include "../str.h"
#include "../io.h"
#include "../output.h"

using namespace std;

enum query_type {EMF = 0, MF = 1, NORMAL = 2};

class Query_Parser{
	public:
		string table;
		vector<string>* select_attribute;
		int no_grouping_vars;
		
		vector<string>* grouping_attr;
		vector<string>* f_vect;
		vector<string>* select_cond_vect;
		string having;
		string where;
		int query;

		Query_Parser();
		Query_Parser(string file);

	private:
		void parse_select(string select);
		void parse_group_by(string group_by);
		void parse_such_that(string such_that);
		void parse_f_vect(string query);

	public:
		static string PARTS[];

		static string KEYWORDS[];
};




#endif