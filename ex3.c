#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

#include "ex3.h"
#include "listeChaine.h"

//q3.1:

List* listdir(char* root_dir){

    if(!root_dir) return NULL;

    DIR * dir= opendir(root_dir);

    if(!dir) return NULL;

    struct dirent * entry;
    
    List * ret= initList();
    while ( (entry = readdir(dir)) ){
        
        insererFirst( ret, buildCell(entry->d_name));
    }

    closedir(dir);
    return ret;
}//teste ; ok

//q3.2: 

int file_exists( char * str){

    
    if(!str) return 0;

    List * list_curdir= listdir("./");

    Cell * check = searchList(list_curdir, str);
    int ret = check ? 1 : 0;
    freeList(list_curdir);

    return ret;
}//teste ; ok

//q3.3 

void cp (const char *from , const char * to){
    /*
    dans l'ennonce l'ordre de from est to est inverse 
    j'ai remplace par l'ordre de cp dans la commande shell 
    du meme nom
    */

    if(!from) return;

    FILE *source = fopen(from, "r");
    if(!source) return;

    FILE * dest = fopen(to, "w");

    char line[256];


    while ( fgets(line, 256, source) ) {
        fprintf(dest, "%s", line);
    }

    fclose(source);
    fclose(dest);   
}//teste ; ok

//q3.4: 


//q3.5: