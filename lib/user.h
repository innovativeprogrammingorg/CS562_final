#ifndef _USER_H_
#define _USER_H_


#include <istream>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "debug.h"
#include "str.h"
#include "io.h"
#include "output.h"

using namespace std;
/**
 * Handle input from the command 
 */
void parse_user_input();

/**
 * Parses input from a file
 * @param file The file to parse
 */
void parse_file_input(string file);

#endif