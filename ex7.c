#include "ex7.h"

#include "ex1.h"
#include "ex4.h"
#include "ex5.h"
#include "ex6.h"

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
}//teste ; ok


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
}//teste; ok

//q3: 

void deleteRef(char* ref_name){

    if(! (ref_name )) return;

    unsigned ref_path_length= 7+strlen(ref_name);

    char* ref_path = (char*) malloc( (ref_path_length)* sizeof(char));
    
    sprintf(ref_path, ".refs/%s", ref_name);

    remove(ref_path);

    free(ref_path);
}// teste ; ok

//q4: 

char* getRef(char* ref_name){
    /*
    renvoie NULL si ref name null ou fichier n'existe pas; 
    renvoie "" si le fichier est vide 

    renvoie premiere ligne du fichier sinon.
    */
    
    if(! ref_name ) return NULL;

    unsigned ref_path_length= 7+strlen(ref_name);

    char* ref_path = (char*) malloc( (ref_path_length)* sizeof(char));
    
    sprintf(ref_path, ".refs/%s", ref_name);

    FILE* f = fopen(ref_path, "r");

    if(!f){ 
        free(ref_path);
        return NULL;
        
    }
    char * ret= (char*) calloc(256, sizeof(char));

    if(!fgets(ret, 256, f)){
        free(ret);
        ret= strdup("");
        //printf("len ret in getref %d" ,strlen(ret));
        fclose(f);
        free(ref_path);
        return ret;
    }else{

        fclose(f);
        free(ref_path);
        return ret;
    }
}//teste ; ok ; 


//q5: 

void myGitAdd(  char * file_or_folder){
    /*
    wow.
    */
    if(! file_or_folder) return;

    int testAdd= isFile(".refs/.add");

    //printf("test add is %d\n" , testAdd);
    if(testAdd){

        //sauvegarde ancienne path du fichier pour pouvoir le supprimer
        WorkTree * wt= ftwt( ".refs/.add"); 
        char * sha= sha256file(file_or_folder);
        appendWorkTree(wt, file_or_folder, sha , getChmod(file_or_folder));
        free(sha);
        
        wttf(wt, ".refs/.add");

        freeWorkTree(wt);
        
    }else{
        WorkTree * wt= initWorkTree();
        char * sha= sha256file(file_or_folder) ;
        appendWorkTree(wt, file_or_folder, sha , getChmod(file_or_folder));
        free(sha);
       
       
        wttf(wt, ".refs/.add");

        freeWorkTree(wt);
    }
}//teste ; semble ok

//q6: 

void myGitCommit(char *branch_name, char *message){
    /*
    je vais essayer de decrire chaque etape comme dans la consigne 
    */
    if (! (isDirectory(".refs")) ){ //cas ou .refs n'existe pas
        fprintf(stderr, "initialisez d'abord les references du projet\n");
        return;
    }
    //changer en .refs/branchname 

    unsigned length_name =strlen(branch_name);
    char * refs_branch_name= calloc((7+length_name), sizeof(char));
    
    sprintf(refs_branch_name, ".refs/%s" , branch_name);
    
    if(!branch_name){ //cas ou branch name n'existe pas
        fprintf(stderr,"la branche n'existe pas et branch_name est NULL\n");
        free(refs_branch_name);
        return;
    }
    if(!isFile(refs_branch_name)){ //cas ou branche name n'existe pas
        fprintf(stderr,"la branche n'existe pas\n");
        free(refs_branch_name);
        return;
    }
    
    char * refHead= getRef("HEAD");
    char * refBranch = getRef(branch_name);
    //printf("refHead refBranch %p %p\n", refHead , refBranch);
   // printf("refHead refBranch %s %s %lu %lu\n", refHead , refBranch, strlen(refHead), strlen(refBranch));
    if(refBranch && refHead){
        if(strcmp(refHead, refBranch)){ //cas ou HEAD et branch name ne "pointent" pas sur la meme chose
            fprintf(stderr ,"head et branchname doivent pointer sur la meme chose\n");
            free(refBranch);
            free(refHead);
            free(refs_branch_name);
            return;
        }
    }else{
        printf("quelque chose s'est mal passe interruption du commit\n"); 
        if(refBranch) free(refBranch);
        if( refHead) free(refHead);
         free(refs_branch_name);
        return;
    }
    free(refBranch);
    free(refHead);
    free(refs_branch_name);
    //charger le wt correspondant a .add
    
    WorkTree* wt = ftwt(".refs/.add");

    //adapter a .add 
   
    char * pathSavedTree=  saveWorkTree(wt, "."); //saveWt dans consigne mais etrange
    //printf("path SavedTree %s\n ", pathSavedTree);
    //enregistrer un instantane de ce wt

    Commit * c = createCommit(pathSavedTree);
//mettre hash utiliser create commit
    char * hashPredecessor = getRef(branch_name); 
    if(hashPredecessor){
        if(strcmp(hashPredecessor,"")){ //si le precedent n'est pas "" on ajoute predecessor
            commitSet(c , "predecessor", hashPredecessor);
        }
    }

    if(message){//si le message n'est pas nul on l'ajoute au commit 
        commitSet(c, "message", message);
    }

    char * commitPath= blobCommit(c);
    //on met la reference de head et la branche a jour grace a blobCommit
    createUpdateRef(branch_name, commitPath);
    createUpdateRef("HEAD", commitPath);


    //liberation de toute la memoire
    freeCommit(c);
    free(commitPath);
    free(hashPredecessor);
    free(pathSavedTree);
    freeWorkTree(wt);
    remove(".add"); //supprimer .add

}//teste semble ok!!!!!!!