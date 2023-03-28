#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ex1.h"
#include "ex3.h"
#include "ex6.h"



/*EX 6*/

//q1:

kvp* createKeyVal(char* key, char* val){
    /*
    alloue de la memeoire pour un nouveau kvp; 
    duplique clef et val.
    */
        kvp * ret=  (kvp*) malloc(sizeof(kvp));

        ret->key= strdup(key);
        ret->value= strdup(val);
        return  ret;
}//teste ; ok

void freeKeyVal( kvp* k){
    if(!k) return;

    if(k->key) free(k->key); 
    if(k->value) free(k->value);

    free(k);
}//teste ; ok

//q6.2: 

char * kvts( kvp * k){
    /*
    cree une string representant k.
    */
    if(!k) return NULL;

    if(! (k->key && k->value)) return NULL;

    unsigned retlen= (2+ strnlen(k->value, 256)+ strnlen(k->key, 256));
    char * ret= (char*) calloc(retlen,  sizeof(char)); 

    snprintf( ret,  retlen, "%s:%s", k->key, k->value);
  
    return ret; 
}//teste ; ok


kvp * stkv( char * str){
    /*
    */
    if(!str) return NULL;

    char key[256], val[256];
    memset(key, 0, 256);
    memset(val, 0, 256);

    char * separator= ":"; 

    char * curTok= strtok(str, ":");
    if(!curTok){
        fprintf(stderr, "in stkv, invalid format of string %s", str);
        return NULL;
    }
    memcpy(key, curTok, strlen(curTok));

    curTok= strtok(NULL, separator);
    if(!curTok){
        fprintf(stderr, "in stkv, invalid format of string %s", str);
        return NULL;
    }
    memcpy(val, curTok, strlen(curTok));

    return createKeyVal(key, val);
}//teste ; pas ok 

//q6.3: 

Commit * initCommit(){
    /*
    */
    Commit * ret= (Commit*) malloc(sizeof(Commit));

    ret->n=0;
    ret->size= _COMMIT_SIZE;

    ret->T= (kvp**) calloc( _COMMIT_SIZE , sizeof( kvp*));

    return ret;
}//teste ; ok

//q6.4: 

unsigned long sdbm(unsigned char* str){
    /*
    place declaration type parametre dans la liste de parametres pour 
    rendre la fonction plus lisible. 

    question sur utilisation dans le cadre de la table : nombres renvoyes 
    grands par rapport taille table ; modulo ou qqch ??????
    */
    unsigned long hash = 0;
    int c;

    while ((c = *str++))
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}//donne sur le site auquel le td renvoie.
//question sur mettre modulo du hash sur taille de la table???????????

//q6.5 : 

void commitSet(Commit* c, char* key, char* value){
    /*
    ajoute la paire clef value a la table C 
    en resolvant les collisions par probing lineaire. 

    ATTENTION : n'ajoute rien si la table est remplie 
    et ne verifie pas que la valeur est deja dans la table ( probleme? )
    */
    if(! (c && key && value)) return ;

    if(c->size == c->n){ //gestion de table pleine.
        printf("placeholder: table remplie\n");
        return;
    }

    kvp* newEntry= createKeyVal(key, value);
    if(!newEntry){
        fprintf(stderr, "probleme a la creation d'entree pour clefs : %s val : %s\n", key, value );
        return ;
    }
    unsigned long hashedKey =sdbm((unsigned char*)key)%c->size;

    if(c->T[hashedKey]){
       
        while(  c->T[( (hashedKey)%c->size)] ){ //finira par etre nul car certain que la table n'est pas pleine.
            hashedKey++;
        }
    
        c->T[ (hashedKey)%c->size]=newEntry;
        c->n++;
       
    }else{
        c->T[hashedKey]=newEntry;
        c->n++;
    }

}//teste ; semble ok
//gestion de clef deja presente dans la table ?????????????

//q6.6: 

Commit* createCommit(char* hash){
    /*
    
    */

    Commit* ret= initCommit(); 
    commitSet(ret, "tree", hash);

    return ret;
}//teste; ok ; 
//q6.7: 

char* commitGet(Commit* c, char* key){

    if(!(c && key)) return NULL;
   
    unsigned long hashedKey= sdbm( (unsigned char*)key)%c->size;
    if(c->T[hashedKey]){
       
        if(!strcmp(c->T[hashedKey]->key,key)){
            return c->T[hashedKey]->value;
        }else {
            unsigned i=hashedKey+1;

            while((i%c->size)!=hashedKey){ //parcours la table "maximum" une fois 
            //a partir de la clef; seul cas ou toute la table est parcourue est si 
            //la valeur cherche est a l'index hashedKey-1 mais peu probable.
            
                if (c->T[i]){ //necessaire car si on essaie d'acceder a clef ou val alors que 
                //c->T[i] est NULL a cet index cela provoque une segfault.
                    if( !strcmp(c->T[i]->key,key)){
                       
                        return c->T[i]->value;
                    }
                }
                i++;
            }
        }
    }
 
    return NULL;
}//teste ; semble ok

//q6.8: 

char* cts(Commit* c){
    /*
    l'implementation va etre en O(n*n) afin 
    de connaitre la taille de la string a allouer
    puis de la remplir .
    */

    if(!c) return NULL;
    unsigned long total_length=0;

    for( unsigned i=0; i<c->size ; i++){
        if(c->T[i]){
            total_length+= strlen(c->T[i]->key) + strlen(c->T[i]->value) + 2 ; 
            //+2 pour ':' et '\n'
        }
    }

    char * ret= calloc( total_length+1, sizeof(char));
    unsigned long curlength=0;

    for(unsigned i=0; i<c->size; i++){

        if(c->T[i]){        
            snprintf(ret+curlength, total_length,"%s:%s\n", c->T[i]->key, c->T[i]->value );
            curlength+=strlen(c->T[i]->key) + strlen(c->T[i]->value)+2;
        }
    }
    return ret;
}//teste , semble ok

Commit* stc(char* ch){

    if(!ch ) return NULL;

    Commit * ret= initCommit();

    const char * separator = ":\n";

    char * curTok = strtok(ch, separator);

    char key[256] ; 
    char value[256];


    while(curTok){
        memset(key, 0, 256);
        memset(value, 0, 256);

        memcpy( key, curTok, strlen(curTok));

        curTok= strtok(NULL, separator);
        if(!curTok){
            fprintf(stderr , "in stc, char passed has invalid format %s\n", ch); 

            freeCommit(ret);

            return NULL;
        }
        memcpy( value, curTok, strlen(curTok));

        commitSet(ret, key, value);
        
        curTok= strtok(NULL, separator);
    }

    return ret;     

}//teste semble ok


//q9: 

void ctf(Commit* c, char* file){
    if(!(c && file)) return;

    char * commitString = cts(c);

    FILE * f = fopen(file, "w");

    fprintf(f, "%s", commitString);

    free(commitString);
    fclose(f);
}//pas teste

Commit* ftc(char* file){
    /*
    */
    if(!file)return NULL;

    FILE * f= fopen(file, "r"); 
    if(!f) return NULL;

    Commit * ret= initCommit();

    char line[516];
    char key[256] , value[256];

    char * separator= ":\n";
    char * curTok=NULL;
    
    while(fgets(line , 516, f)){

        memset(key, 0, 256);
        memset(value, 0, 256);

        curTok= strtok(line, separator);

        if(!curTok){
            fprintf(stderr , "in stc, char passed has invalid format %s\n", line); 

            freeCommit(ret);
            fclose(f);
            return NULL;
        }
        memcpy( key, curTok, strlen(curTok));

        curTok= strtok(NULL, separator);

        if(!curTok){
            fprintf(stderr , "in stc, char passed has invalid format %s\n", line); 

            freeCommit(ret);
            fclose(f);
            return NULL;
        }
        memcpy( value, curTok, strlen(curTok));
        commitSet(ret, key, value);
    }

    fclose(f);
    return ret;
}//pas teste

//q10: 

char*  sha256file_c( char * c_string){
    /*
    returns the hash of a string representing a commit with .c at the end of it.
    */

	if(!c_string ) return NULL;
	static char template[]= "tmp_filenameXXXXXX";


	char fname[1000] ; 
	strcpy(fname  , template); 

	int fd = mkstemp(fname);
	if(fd==-1) return NULL;


	hashFile(c_string, fname);

	FILE * f = fopen( fname , "r"); 
	if(!f) return NULL;

	char * line= calloc(260, sizeof(char)); 

	fgets(line, 256, f); 
	
	fclose(f);

	unsigned short len= strnlen(line, 260);
	unsigned short cpt=0; 

	while(line[cpt]!=' ' && line[cpt] !='\0') ++cpt;

	if(line[cpt]){
		char * ret = strndup(line, cpt+3);
		free(line); 
		ret[cpt]='.'; 
        ret[++cpt]='c';
        ret[++cpt]='\0';
		system("rm -f tmp_filename*");

		return ret;
	
	}
    line[cpt]='.'; 
    line[++cpt]='c';
    line[++cpt]='\0';
	system("rm -f tmp_filename*");

	return line;		 
}//teste 

char* blobCommit(Commit* c){

    if(!c) return NULL;

    ctf(c, "c.tmp");

    char * hash= sha256file_c("c.tmp");
    char * path = hashToPath(hash);


    unsigned short path_length= strlen( path);

    char * directory_name = strndup(path, 2);

    //pour construire l'appel systeme
    char * syscall = (char*) malloc(  ((4)+1+32)  * sizeof(char)); 
    //alloue 2 fois la taille du chemin + le nombre fixe de caracteres necessaire a la commande +1 pour 
    //le \0

    snprintf(syscall, 4 + 33, "if [ ! -d \"%s\" ];then mkdir \"%s\";fi", directory_name, directory_name);

    system(syscall);

    cp("c.tmp", path);
    
    free(syscall); 
    free(directory_name);
    free(path); 


    remove("c.tmp");
    return hash;
}//teste ; semble ok 



//pas demande mais necessaire 

void freeCommit( Commit* c){
    /*
    */
    if(!c) return;

    for(unsigned i=0; i<c->size ;i++){
        freeKeyVal(c->T[i]);
    }
    free(c->T);
    free(c);
}