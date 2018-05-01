#ifndef _SCAN_GENERATOR_H_
#define _SCAN_GENERATOR_H_

#include <iostream>
#include <string>
#include <vector>
#include "column.h"
#include "aggregate.h"
#include "conditions.h"

using namespace std;

/**
 * This is a wrapper class for the generation of scans for the output program
 * It currently handles the scans in a 3 stage process. 
 * The first stage simply initializes the variables, and fills all of the
 * data structures with the data which will NOT be manipulated
 * 
 * The second stage calculates all ofthe aggregate values in the query
 *
 * The third stage fills the mf_struct with the relevant data, and filters it based on the having
 * clause if it is given.
 */
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
		 * Creates an object capable of generating the scans for the query.
		 * @param  no_grouping_vars  The number of grouping variables
		 * @param  columns           The columns in the table
		 * @param  select_columns    The columns in the select statement
		 * @param  select_aggregates The aggregates in the select statement
		 * @param  all_aggregates    All of the aggregates
		 * @param  select_conditions The such that logic for each grouping variable
		 * @param  having            The having string
		 * @param  grouping_attr	 The grouping attributes
		 * @param  emf               Whether the query is an emf query
		 * @return                   All 3 scans used for processing
		 */
		Scan_Generator(int no_grouping_vars,vector<Column*>* columns,vector<string>* select_columns,vector<Aggregate*>* select_aggregates,
				    vector<Aggregate*>* all_aggregates,vector<Conditions*>* select_conditions,string having,vector<string>* grouping_attr,bool emf);
		/**
		 * Creates the code for all of the scans for the query and returns it
		 */
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
		/**
		 * Groups the aggregates by their grouping variable. Used for optimization
		 */
		vector<vector<Aggregate*>> group_aggregates();

		/**
		 * Gets a boolean expression which represents the such that statement
		 * for the given grouping variable
		 * @param  group The grouping variable
		 */
		string get_selection_cond(int group);

		/**
		 * The first scan: handles inserting the data for all of the 
		 * columns that do not require any addition processing
		 */
		string prelim_scan();


		/**
		 * processes all the aggregates
		 */
		string aggregate_scan();

		/**
		 * Processes all the aggregates for an EMF query
		 */
		string emf_aggregate_scan();

		/**
		 * Fills the mf structure with the required results
		 */
		string fill_mfstruct();

};

#endif