#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <vector>
#include <string>
#include <iostream>
#include "objects/column.h"
using namespace std;


void print_vector(vector<string>* vec);
void print_vector(vector<Column*>* vec);

#endif