#ifndef _SQL_H_
#define _SQL_H_


#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdarg.h>
#include <cstdint>
#include "mysql_driver.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include "../config.h"

/**
 * double 'd'
 * int32_t 'i'
 * string 's'
 * int64_t 'l'
 * uint64_t 'u'
 */

using namespace std;

class SQLConn{
	private:
		static sql::Driver* driver;
	  	static string user;
	public:
		string database;
		sql::Connection* conn;
		SQLConn();
		SQLConn(string database);
		virtual ~SQLConn();
		/**
		 * Switch to a new database
		 * @param database The new database
		 */
		void update_database(string database = "");
		/**
		 * Execute a nornal query or a parameterized query
		 */
		void execute(string types,string query,...);
		void execute(string query);
		/**
		 * Fetch the results from a normal query or a parameterized query
		 */
		sql::ResultSet* fetch(string types,string query,...);
		sql::ResultSet* fetch(string query);


};


#endif