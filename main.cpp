#include "main.h"

int main(int argc,char** argv){
	if(argc <2){
		parse_user_input();
	}else{
		parse_file_input(string(argv[1]));
	}	


	return EXIT_SUCCESS;
}