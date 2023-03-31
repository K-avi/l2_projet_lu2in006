#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


#include "ex5.h"
#include "ex8.h"
#include "ex9.h"
#include "listeChaine.h"
#include "ex1.h"
#include "ex7.h"


int main(int argc, char ** argv){
	
	if(argc<2){
		printf("passez au moins un argument au main!\n");
		return 1;
	}
	//traiter les cas speciaux (nombre d'arguments variables )
	//avant de traiter les cas a arguments fixes.
	
	if(!strcmp(argv[1], "commit")){

		if(argc == 3){
			
			myGitCommit(argv[2], NULL);
		}else if(argc==5){//peut etre utiliser getopt???
			if(strcmp(argv[3], "-m")) {
				printf("commit : option invalide\n");
				return 13;
			}
			myGitCommit(argv[2], argv[4] );
		}else{
			printf("erreur : argument invalide\n");
			return 12;
		}
	}else if (!strcmp(argv[1],"add")){
		

		for(int i=2; i<argc; i++){
			myGitAdd(argv[i]);
		}
	}else if(argc==2){
		/*
		cas possibles: 
		init
		list-refs
		list-add 
		clear-add
		*/

		if(!strcmp(argv[1], "init")){
			//initialise .refs
			initRefs();
			initBranch(); //ex10.1
			return 0;
		}else if(!strcmp(argv[1], "list-refs")){
			//liste fichiers de .refs
			DIR * d= opendir(".refs");
			if(!d){
				printf(".refs n'est pas initialise!!\n");
				closedir(d);
				return 2;
			}else{
				struct dirent* entry; 
				while( (entry=readdir(d))){
					char * path=  (char*)calloc(strlen(entry->d_name)+7, sizeof(char));
					sprintf(path, ".refs/%s", entry->d_name);

					if(isFile(path)){
						printf("%s\n", entry->d_name);
					}
					free(path);
				}
				closedir(d);
				return 0;
			}
		}else if(!strcmp(argv[1], "list-add")){
			//liste contenu de .add
			FILE * f= fopen(".refs/.add", "r");
			if(!f){
				printf(".add n'existe pas!\n");
				return 5;
			}
			char line[256];

			while( fgets(line, 256, f)){
				printf("%s\n", line);
			}
			fclose(f);
			return 0;
		}else if(!strcmp(argv[1], "clear-add")){
			//efface contenu de .add
			FILE * f = fopen(".refs/.add", "w");
			fclose(f);
			return 0;
		}else if (!strcmp(argv[1], "get-current-branch")){//ex10.2

			char * curbranch = getCurrentBranch();
			if(curbranch){//getCurrentBranch() se passe bien 
				printf("la branche courante est : %s\n", curbranch);
				free(curbranch);

				return 0;
			}else{
				fprintf(stderr, "erreur recuperation du nom de la branche courante\n");
				exit(-11);
			}
		}else{
			printf("erreur : argument invalide\n");
			return 0;
		}

	}else if(argc==3){
		/*cas possible :
		delete-ref
		*/

		if(!strcmp( argv[1], "delete-ref")){
			if (!isDirectory(".refs")) {
				printf(".refs n'est pas initialise :/\n");
				return 8;
			}
			char * refpath= calloc(7+strlen(argv[2]), sizeof(char));
			sprintf(refpath, ".refs/%s", argv[2]);
			if(!isFile(refpath)){
				printf("la reference passee en argument n'existe pas\n");
				free(refpath);
				return 7;

			}else{
				printf("refpath %s\n", refpath);
				remove(refpath); 
				free(refpath);
				return 0;
			}
		}else if(!strcmp(argv[1], "branch")){ //ex10.2:
				createBranch(argv[2]);
				return 0;
		}else if(!strcmp(argv[1], "branch-print")){

				printBranch(argv[2]);
				return 0;
		}else if(!strcmp(argv[1], "checkout-branch")){

				myGitCheckoutBranch(argv[2]);
				return 0;
		}else if(!strcmp(argv[1], "checkout-commit")){

				myGitCheckoutCommit(argv[2]);
				return 0;
		}else{
			printf("erreur argument invalide\n");
			return 6;
		}
	}else if (argc==4){
		/*
		cas possible : 
		create ref :
		*/
		if(!strcmp(argv[1], "create-refs")){
			char * refpath= calloc(7+strlen(argv[2]), sizeof(char));
			sprintf(refpath, ".refs/%s", argv[2]);
			FILE * f = fopen(refpath, "w");

			fprintf(f, "%s\n", argv[3]);

			fclose(f);
			free(refpath);
			return 0;

		}else{
			printf("erreur argument invalide\n"); 
			return 14;
		}
	}else{ 
		printf("erreur argument invalide\n");
			return 15;
	}
	return 0;

}//pas teste ; 
//cas avec nb d'arg variables (commit et add ) non implementes 