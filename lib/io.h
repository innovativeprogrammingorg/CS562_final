#ifndef _IO_H_
#define _IO_H_

#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "str.h"

using namespace std;

/**
 * Append data to a file
 * @param dir      The directory of the file
 * @param filename The name of the file
 * @param data     The data to write to the file
 */
void append_to_file(string dir, string filename,string data);

/**
 * Create/Overwrite a file and write to it
 * @param dir      The directory of the file
 * @param filename The name of the file
 * @param data     The data to write to the file
 */
void write_to_file(string dir, string filename, string data);

/**
 * Read data from file
 * @param dir      The directory of the file
 * @param filename The name of the file
 * @return 		   The contents of the file
 */
string read_from_file(string dir,string filename = "");

#endif