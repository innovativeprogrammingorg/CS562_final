#ifndef _SCAN_GENERATOR_H_
#define _SCAN_GENERATOR_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "column.h"
#include "aggregate.h"
#include "conditions.h"

using namespace std;

class Scan_Generator{
	private:
		int no_grouping_vars;
		vector<Column*>* columns;
		vector<string>* select_columns;
		vector<Aggregate*>* select_aggregates;
		vector<Aggregate*>* all_aggregates;
		vector<Conditions*>* select_conditions;
		string having;
		vector<string>* grouping_attr;
		bool emf;
	public:
		/**
		 * Generates all 3 scans
		 * @param  no_grouping_vars  The number of grouping variables
		 * @param  columns           The columns in the table
		 * @param  select_columns    The columns in the select statement
		 * @param  select_aggregates The aggregates in the select statement
		 * @param  all_aggregates    All of the aggregates
		 * @param  select_conditions The such that logic for each grouping variable
		 * @param  having            The having string
		 * @return                   All 3 scans used for processing
		 */
		Scan_Generator(int no_grouping_vars,vector<Column*>* columns,vector<string>* select_columns,vector<Aggregate*>* select_aggregates,
				    vector<Aggregate*>* all_aggregates,vector<Conditions*>* select_conditions,string having,vector<string>* grouping_attr,bool emf);
		string generate();
	private:
		/**
		 * Parses the having string into a C++ expression, which evaluates into 
		 * a bool
		 * @param  having  The given having string
		 * @param  columns The columns in the Table
		 * @return         The C++ expression
		 */
		string parse_having();
		vector<vector<Aggregate*>> group_aggregates();
		string get_selection_cond(int group);

		/**
		 * The first scan: handles inserting the data for all of the 
		 * columns that do not require any addition processing
		 * @return                  The first scan
		 */
		string prelim_scan();


		/**
		 * processes all the aggregates
		 * @return     The second scan
		 */
		string aggregate_scan();

		string emf_aggregate_scan();

		string fill_mfstruct();

};



#endif