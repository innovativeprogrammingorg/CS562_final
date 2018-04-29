#include "main.h"

int main(int argc,char** argv){
	if(argc <2){
		parse_user_input(false);
	}else if(argc == 2 && string(argv[1]).compare("-emf") == 0){
		parse_user_input(true);
	}else if(argc == 2){
		parse_file_input(string(argv[1]),false);
	}else if(string(argv[1]).compare("-emf") == 0){
		parse_file_input(string(argv[2]),true);
	}else if(string(argv[2]).compare("-emf") == 0){
		parse_file_input(string(argv[1]),true);
	}else{
		cout<<"Invalid input"<<endl;
	}	
	
	return EXIT_SUCCESS;
}