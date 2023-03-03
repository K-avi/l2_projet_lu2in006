#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "listeChaine.h"
#include "ex1.h"

int main(){
	//hashFile( "/home/ivan/Documents/L2/doc_s2/struct_donnees/projet/tmp1.tmp", "/home/ivan/Documents/L2/doc_s2/struct_donnees/projet/tmp2.tmp");

	char * test = sha256file( "/home/ivan/Documents/L2/doc_s2/struct_donnees/projet/tmp1.tmp");
	if(test) printf("%s\n",test); 
	free(test);
	return 0;

}
