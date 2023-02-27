#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "listeChaine.h"


//q1.3:
int hashFile(char * source, char * dest){

		if(! (source && dest)) return -1;
		
		unsigned l1= strlen(source) , l2=strlen(dest);
		unsigned length= l1+l2 + 14;

		char*  tmp = (char* ) calloc(length , sizeof(char));  

		sprintf(tmp, "sha256sum %s > %s", source, dest);
		
		int ret= system(tmp);
		
		free(tmp);

		return ret; 

}

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

	char * ret= calloc(256, sizeof(char)); 

	fgets(ret, 256, f); 
	
	fclose(f);
	
	system("rm tmp_filename*");
	return ret; 
}

int main(){
	//hashFile( "/home/ivan/Documents/L2/doc_s2/struct_donnees/projet/tmp1.tmp", "/home/ivan/Documents/L2/doc_s2/struct_donnees/projet/tmp2.tmp");

	char * test = sha256file( "/home/ivan/Documents/L2/doc_s2/struct_donnees/projet/tmp1.tmp");
	if(test) printf("%s\n",test); 
	free(test);
	return 0;
}
