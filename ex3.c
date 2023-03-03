#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ex1.h"
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

char* hashToPath(char* hash){

    /*
    le snprintf est un peu bizarre mais j'ai teste le code et il semble ok.
    */
 
    if(!hash) return NULL; //hash est null
    
    unsigned hash_length = strnlen(hash, 256);

    if(hash_length<=2) return NULL; //hash n'est pas valide car trop court

    char * ret= malloc( (hash_length+2)* sizeof(char));
    ret[0]= hash[0];
    ret[1]= hash[1];
    ret[2]='/';
    char * snde_part= strndup(hash+2, hash_length-2);

    snprintf(ret+3, hash_length-1, "%s", snde_part);

    free(snde_part);

    return ret;
}//teste ; semble ok 

//q3.5:

void blobFile(char* file){

    /*
    
    */
    char * hash= sha256file(file);
    char * path = hashToPath(hash);


    unsigned short path_length= strlen( path);

    char * directory_name = strndup(path, 2);

    //pour construire l'appel systeme
    char * syscall = (char*) malloc(  ((4)+1+32)  * sizeof(char)); 
    //alloue 2 fois la taille du chemin + le nombre fixe de caracteres necessaire a la commande +1 pour 
    //le \0

    snprintf(syscall, 4 + 33, "if [ ! -d \"%s\" ];then mkdir \"%s\";fi", directory_name, directory_name);

    system(syscall);

    cp(file, path);
    
    free(syscall); 
    free(directory_name);
    free(path); 
    free(hash);
}//teste ; semble ok