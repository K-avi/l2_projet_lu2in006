#include "ex7.h"
#include "ex5.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

//q1:
void initRefs(){

    if(!isDirectory(".refs")){
        mkdir(".refs", 0777);
    }
    FILE * fmaster= fopen(".refs/master", "w");
    FILE * fhead= fopen(".refs/HEAD", "w");

    fclose(fmaster);
    fclose(fhead);
}//pas teste 


//q2: 

void createUpdateRef(char* ref_name, char* hash){
    
    if(! (ref_name && hash)) return;

    unsigned ref_path_length= 7+strlen(ref_name);

    char* ref_path = (char*) malloc( (ref_path_length)* sizeof(char));
    
    sprintf(ref_path, ".refs/%s", ref_name);

    FILE * f= fopen(ref_path, "w");
    fprintf(f, "%s",hash);

    fclose(f);
    free(ref_path);
}//pas teste

//q3: 

void deleteRef(char* ref_name){

    if(! (ref_name )) return;

    unsigned ref_path_length= 7+strlen(ref_name);

    char* ref_path = (char*) malloc( (ref_path_length)* sizeof(char));
    
    sprintf(ref_path, ".refs/%s", ref_name);

    remove(ref_path);

    free(ref_path);
}//pas teste 

//q4: 

char* getRef(char* ref_name){
    /*
    renvoie NULL si ref name null ou fichier n'existe pas; 

    renvoie "" si le fichier est vide 

    renvoie premiere ligne du fichier sinon en supposant que c'est la que le hash est contenu; 

    cela posera probleme s'il fallait faire autrement. 
    */
    
    if(! ref_name ) return NULL;

    unsigned ref_path_length= 7+strlen(ref_name);

    char* ref_path = (char*) malloc( (ref_path_length)* sizeof(char));
    
    sprintf(ref_path, ".refs/%s", ref_name);

    FILE* f = fopen(ref_path, "r");

    if(!f) return NULL;
    char * ret= (char*) calloc(256, sizeof(char));

    if(!fgets(ret, 256, f)){
        free(ret);
        ret= strdup("");
        fclose(f);
        return ret;
    }else{

        fclose(f);
        return ret;
    }
}//pas teste
