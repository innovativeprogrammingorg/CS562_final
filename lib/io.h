#ifndef _IO_H_
#define _IO_H_

#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <cstdint>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "str.h"

using namespace std;


void append_to_file(string dir, string filename,string data);
void write_to_file(string dir, string filename, string data);
string read_from_file(string dir,string filename = "");

#endif