#include "io.h"
using namespace std;


void append_to_file(string dir, string filename,string data){
	string loc = dir + filename;
	ofstream file;
	file.open(loc,ios::out|ios::app);
	file<<data;
	file.close();
}

void write_to_file(string dir, string filename,string data){
	string loc = dir + filename;
	char* tmp = to_cstr(loc);
	unlink(tmp);
	free(tmp);
	ofstream file;
	file.open(loc,ios::out);
	file<<data;
	file.close();
}


string read_from_file(string dir,string filename){
	string loc = dir + filename;
	ifstream file;
	file.open(loc);
	if(!file){
		throw exception();
	}
	string out = "";
	string tmp;
	while(!file.eof()){
		getline(file,tmp);
		out = out + tmp + "\n";
	}
	
	file.close();
	return out;
}
