#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#include "ex1.h"


//q1.3:
int hashFile(char * source, char * dest){

		if(! (source && dest)) return -1;
		
		unsigned l1= strnlen(source, 256) , l2=strnlen(dest, 256); //strnlen est plus "sur"
		unsigned length= l1+l2 + 14;

		char*  tmp = (char* ) calloc(length , sizeof(char));  

		snprintf(tmp, length,"sha256sum %s > %s", source, dest); // meme chose pour snprintf
		
		int ret= system(tmp);
		
		free(tmp);

		return ret; 

}//teste

//q1.4: 

char*  sha256file( char * file){

	if(!file ) return NULL;
	static char template[]= "tmp_filenameXXXXXX";

	

	char fname[1000] ; 
	strcpy(fname  , template); 

	int fd = mkstemp(fname);
	if(fd==-1) return NULL;


	hashFile(file, fname);

	FILE * f = fopen( fname , "r"); 
	if(!f) return NULL;

	char * line= calloc(256, sizeof(char)); 

	fgets(line, 256, f); 
	
	fclose(f);

	unsigned short len= strnlen(line, 256);
	unsigned short cpt=0; 

	while(line[cpt]!=' ' && line[cpt] !='\0') ++cpt;

	if(line[cpt]){
		char * ret = strndup(line, cpt);
		free(line); 
		
		system("rm -f tmp_filename*");

		return ret;
	
	}

	system("rm -f tmp_filename*");

	return line;		 
}//teste
