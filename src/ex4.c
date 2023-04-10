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
    sprintf ( buff , "chmod %o %s " , mode , path ) ;
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

    unsigned length_name = strnlen(wf->name, 256), length_hash= strlen(wf->hash);

    char * ret = malloc((length_hash+length_name+6)* sizeof(char));
    snprintf(ret, length_hash+length_name+5, "%s\t%s\t%o" , wf->name, wf->hash, wf->mode);

    return ret;
}//teste ; ok

//EX4.3: 

WorkFile* stwf(const char* ch){

    if(!ch) return NULL;

    char name[256], hash[256];
    unsigned mode;

    sscanf(ch, "%255s\t%255s\t%o", name, hash , &mode );

    WorkFile* ret= createWorkFile(name);
    ret->hash= strndup(hash, 256); 
    ret->mode = mode;

    return ret;
}//teste ; ok


//EX4.4: 

WorkTree* initWorkTree(){
   WorkTree * ret= (WorkTree* ) malloc(sizeof(WorkTree));

   ret->n=0;
   ret->size= WTREE_SIZE; 
   ret->tab= (WorkFile*) malloc(16*sizeof(WorkFile));
   
   return ret;
}//teste ; semble ok

//EX4.5:

int inWorkTree(WorkTree* wt, char* name){
    /*
    renvoie index de l'element de nom name s'il 
    est dans WT ; -1 sinon
    */

    if(! (wt && name))  return -1;
    if(!wt->tab) return -1;

    for (int i= 0; i<wt->n; i++){
        if(!strncmp( name, wt->tab[i].name, 256)){
            return i;
        }
    }
    return -1;
}//teste ; ok



//EX4.6 : 



int appendWorkTree(WorkTree* wt, char* name, char* hash, int mode){
    
    if(! (wt && name)) return -1;
    if( wt->n >= wt->size) return -1;

    int testTree =inWorkTree(wt, name); 

    if(testTree != -1) return testTree;

    if(hash) wt->tab[wt->n].hash= strndup(hash, 256);
    else  wt->tab[wt->n].hash=NULL;

    wt->tab[wt->n].name = strndup(name, 256);
    wt->tab[wt->n].mode= mode;
    wt->n++;
    return wt->n;
}//teste ; semble ok 


//EX4.7 : 

char* wfts_VAR(WorkFile* wf){
    /*
    comme wfts mais ajoute \n a la fin de 
    la chaine de caractere.
    */
    if(!wf) return NULL;
    if(! (wf->hash && wf->name)) return NULL;

    unsigned length_name = strnlen(wf->name, 256), length_hash= strlen(wf->hash);

    char * ret = malloc((length_hash+length_name+7)* sizeof(char));
    snprintf(ret, length_hash+length_name+6, "%s\t%s\t%o\n" , wf->name, wf->hash, wf->mode);

    return ret;
}//teste ; ok


char* wtts(WorkTree* wt){
    /*
    suppose que wt->hash != NULL ; peut etre pbmatique ; 
    possiblement le laisser print (nil) et ne pas le charger plus tard? 
    sinon laisser le champ vide? ????
    */

    if(!wt) return NULL;
    char **buff= (char**) malloc(wt->n * sizeof(char*));
    unsigned length=0;
  
    for(int i=0 ; i<wt->n; i++){
        buff[i]= wfts_VAR(& wt->tab[i]);
        length+= strnlen(buff[i], 256); //might be a problem i dunno
    }

    char* ret= (char*) calloc( (length+1+wt->n), sizeof(char));

    for (int i=0; i<wt->n; i++){
        strncat(ret, buff[i], 256);
        free(buff[i]);
       
    }

    free(buff);

    return ret;
}//teste ; semble ok 

//EX4.8 : 


WorkTree * wt_from_string( char * str){
    /*
    ne gere pas le cas ou hash =NULL ? 
    */
    if( ! str) return NULL;

    const char * separator ="\n";

    char * curTok= strtok(str, separator);
    WorkTree * ret = initWorkTree();
    char  name[256]; 
    char  hash[256]; 
    unsigned mode;

    while(curTok){
        sscanf(curTok, "%255s\t%255s\t%o", name, hash, &mode);
        appendWorkTree(ret, name, hash, mode);
        curTok= strtok(NULL, separator);
    }

    return ret;
}// teste  ; semble ok 

//EX4.9: 

int wttf(WorkTree * wt , char * file){
    if(! (wt && file)) return -1;

    FILE * f = fopen(file, "w"); 
    if(!f) return -1; 

    char * wt_string  = wtts(wt);
    if(!wt_string) {
        fclose(f);
        return -1; 
    }

    fprintf(f, "%s", wt_string);

    free(wt_string);
    fclose(f);

    return 1;
}//teste ; ok 

//EX4.10: 

WorkTree * ftwt( char * file){
    
    if(! file) return NULL;

    FILE * f= fopen(file, "r");
    if(!f) return NULL; 

    WorkTree* ret= initWorkTree(); 
    if(!ret){
         fclose(f);
         return NULL;
    }

    char line[1024]; 

    char name[256]; 
    char hash[256]; 
    unsigned mode ;

    while(fgets(line, 1024, f)){

        sscanf(line, "%255s\t%255s\t%o", name, hash, &mode);
        appendWorkTree(ret, name, hash, mode);

    }

    fclose(f);
    
    return ret; 
}


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
