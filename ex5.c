#include "ex5.h"
#include "ex3.h"
#include "ex4.h"
#include "ex1.h"
#include "listeChaine.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>


char*  sha256file_wt( char * wt_string){
    /*
    returns the hash of a string representing a worktree with .t at the end of it.
    */

	if(!wt_string ) return NULL;
	static char template[]= "tmp_filenameXXXXXX";

	

	char fname[1000] ; 
	strcpy(fname  , template); 

	int fd = mkstemp(fname);
	if(fd==-1) return NULL;


	hashFile(wt_string, fname);

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
        ret[++cpt]='t';
        ret[++cpt]='\0';
		system("rm -f tmp_filename*");

		return ret;
	
	}
    line[cpt]='.'; 
    line[++cpt]='t';
    line[++cpt]='\0';
	system("rm -f tmp_filename*");

	return line;		 
}//teste

//q5.1  : 

char * blobWorkTree ( WorkTree * wt){

    if( ! wt ) return NULL;
    
    wttf(wt, "wt.tmp");
  
    char * hash= sha256file_wt("wt.tmp");
    char * path = hashToPath(hash);


    unsigned short path_length= strlen( path);

    char * directory_name = strndup(path, 2);

    //pour construire l'appel systeme
    char * syscall = (char*) malloc(  ((4)+1+32)  * sizeof(char)); 
    //alloue 2 fois la taille du chemin + le nombre fixe de caracteres necessaire a la commande +1 pour 
    //le \0

    snprintf(syscall, 4 + 33, "if [ ! -d \"%s\" ];then mkdir \"%s\";fi", directory_name, directory_name);

    system(syscall);

    cp("wt.tmp", path);
    
    free(syscall); 
    free(directory_name);
    free(path); 

    remove("wt.tmp");

    return hash;
}

//q5.2: 

int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

int isFile(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISREG(statbuf.st_mode);
}

char * saveWorkTree( WorkTree * wt , char * path){
    /*
    */
    if(! (wt && path)) return NULL;

    int path_length= strlen(path);
    size_t path_size= path_length* sizeof(char);

    
    char * path_with_slash = calloc(path_length+2, sizeof(char));
    sprintf(path_with_slash, "%s/", path);

    char * curname; 
    char * curname_with_path= calloc(path_length+258, sizeof(char));
    int curname_with_path_length= path_length+258;

    char * blob;

    for(int i=0 ; i<wt->n; i++){

        curname = wt->tab[i].name;
        /* vide et remplis le buffer du nom courant.*/
        memset(curname_with_path, 0, curname_with_path_length);
        sprintf(curname_with_path, "%s%s", path_with_slash,curname);

        if(isFile(curname_with_path)){

             blobFile(curname_with_path);
//printf("in saving getCh %s %d\n", wt->tab[i].name,getChmod(curname_with_path));
             wt->tab[i].mode= getChmod(curname_with_path);

             if(wt->tab[i].hash) free(wt->tab[i].hash);
             wt->tab[i].hash= sha256file(curname_with_path);

        }else if(isDirectory(curname_with_path)){

            WorkTree * newWT= initWorkTree();
            List * list_curdir = listdir(curname_with_path);
            List tmp=*list_curdir;
          //  printf("cur is %s\n", curname_with_path);
            while(tmp){ //construis newWT
                
                if(tmp->data){
                    
                    //solution pas propre mais trop fatigue de debugger pour faire mieux
                    char path_tmpdata [512]; 
                    memset(path_tmpdata, 0, 512);
                    sprintf(path_tmpdata, "%s/%s", curname_with_path, tmp->data);
//printf("tmpdata is %s %d\n", path_tmpdata, getChmod(path_tmpdata));
                    appendWorkTree(newWT, tmp->data, NULL, getChmod(path_tmpdata) );
                }
                
                tmp=tmp->next;
            }
            freeList(list_curdir);

           char * saved_name = saveWorkTree(newWT, curname_with_path); //appl recursif

           if(wt->tab[i].hash) free(wt->tab[i].hash);
           wt->tab[i].hash=strdup(saved_name);
//printf("in end of save la %s %d \n ", saved_name, getChmod(curname_with_path));
           wt->tab[i].mode=getChmod(curname_with_path);

           free(saved_name);
           freeWorkTree(newWT);
        
        }

    }
    
    char * ret= blobWorkTree(wt);
    free(path_with_slash);
    free(curname_with_path);
    return ret;
}//teste ; semble ok ? 

void restoreWorkTree(WorkTree *wt, char *path){
    
    if (!(wt && path)) return;
    if(wt->n > wt->size) return;

//doit recuperer path correspondant au hash ; puis hash pour verifier 

    char * path_hash;

    char path_target [512];

    for(int i=0; i<wt->n; i++){
        
    //    printf("in restore loop %s %d\n" , wt->tab[i].name, i);
        //if(!wt->tab[i].hash) { i++ ;continue;}
        
        path_hash =hashToPath(wt->tab[i].hash);
        if(!path_hash){
            i++;
            continue;
        }
     

        //vide et remplis path target ; on suppose que 512 char suffisent
        memset(path_target,0, 512);
        snprintf(path_target, 512, "%s/%s", path, wt->tab[i].name);
    
        if(!strstr(path_hash, ".t") ){ 
        //strstr permet de chercher '.t' dans la chaine ; on suppose que le hash ne permet pas de creer ce nom
        //et qu'un fichier contenant .t est FORCEMENT un worktree 

          // printf("in loop, cp file, %s %s\n\n", path_hash, path_target);
           cp(path_hash, path_target);
       //   printf("path target in restore mode %d %s %s\n", wt->tab[i].mode , wt->tab[i].name,path_target);
           setMode(wt->tab[i].mode, path_target);

        }else { 
//printf("path hash: %s\n", path_hash);
            WorkTree * newWT= ftwt(path_hash);

            char newPath[512];

            snprintf(newPath, 512, "%s/%s", path, wt->tab[i].name);
            
            if(!isDirectory(newPath)){

                char * syscall= malloc((7+strlen(newPath))* sizeof(char));

                sprintf(syscall, "mkdir %s",newPath);
                system(syscall); 
                free(syscall);
            }

            restoreWorkTree(newWT, newPath);
            freeWorkTree(newWT);

        }
        free(path_hash);
    }   

    return;
}//fini? teste; semble ok