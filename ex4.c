#include "ex4.h"

#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

//fonctions donnees dans la consigne : 

int getChmod(const char * path){
    struct stat ret; 

    if( stat(path, &ret)== -1){
        return -1;
    }

    return ( ret . st_mode & S_IRUSR ) |( ret . st_mode & S_IWUSR ) |( ret . st_mode & S_IXUSR ) |/*owner*/
           ( ret . st_mode & S_IRGRP ) |( ret . st_mode & S_IWGRP ) |( ret . st_mode & S_IXGRP ) |/*group*/
           ( ret . st_mode & S_IROTH ) |( ret . st_mode & S_IWOTH ) |( ret . st_mode & S_IXOTH ) ;/*other*/
}


void setMode ( int mode , char * path ) {
    char buff [100];
    sprintf ( buff , "chmod %d %s " , mode , path ) ;
    system ( buff ) ;
}


//EX4.1:

WorkFile* createWorkFile(const char* name){
    
    if(!(name)) return NULL;

    WorkFile * ret=  (WorkFile* ) malloc(sizeof(WorkFile));

    ret->name= strndup(name, 256);
    ret->hash=NULL;
    ret->mode= 0;

    return ret;
}//teste ; ok

//EX4.2: 

char* wfts(WorkFile* wf){

    if(!wf) return NULL;
    if(! (wf->hash && wf->name)) return NULL;


    char mode[4];

    snprintf(mode, 3, "%d", wf->mode);
    mode[3]= '\0';

    unsigned length_name = strnlen(wf->name, 256), length_hash= strlen(wf->hash);

    char * ret = malloc((length_hash+length_name+6)* sizeof(char));
    snprintf(ret, length_hash+length_name+5, "%s\t%s\t%s" , wf->name, wf->hash, mode);

    return ret;
}//teste ; ok

//EX4.3: 

WorkFile* stwf(const char* ch){

    if(!ch) return NULL;

    char name[256], hash[256], mode[4];  
    sscanf(ch, "%255s\t%255s\t%3s", name, hash , mode );

    WorkFile* ret= createWorkFile(name);
    ret->hash= strndup(hash, 256); 
    ret->mode = atoi(mode);

    return ret;
}//teste ; ok


//EX4.4: 

WorkTree* initWorkTree(){
   WorkTree * ret= (WorkTree* ) malloc(sizeof(WorkTree));

   ret->n=0;
   ret->size= WTREE_SIZE; 
   ret->tab= calloc(16, sizeof(WorkTree));


   return ret;
}//teste ; semble ok

//EX4.5:

int inWorkTree(WorkTree* wt, char* name){


    if(! (wt && name))  return -1;
    if(!wt->tab) return -1;

    for (int i= 0; i<wt->n; i++){
        if(!strncmp( name, wt->tab[i].name, 256)){
            return i;
        }
    }
    return -1;
}//teste ; ok


//Pas demande mais necessaire/utile

void freeWorkFile(WorkFile * wfile){

    if(!wfile) return;

    if(wfile->hash) free(wfile->hash);
    if(wfile->name) free(wfile->name);

    free(wfile);
}//teste ok 

void freeWorkTree (WorkTree* wtree){
    if(!wtree) return;
    for(unsigned i=0; i<wtree->n; i++){
        
        if(wtree->tab[i].name) free(wtree->tab[i].name); 
        if(wtree->tab[i].hash)free(wtree->tab[i].hash);
    }
    free(wtree->tab);
    free(wtree);
}//teste ; pas sur