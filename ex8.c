#include "ex8.h"
#include "ex1.h"
#include "ex3.h"
#include "ex5.h"
#include "ex6.h"
#include "ex7.h"
#include "listeChaine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//q1: 

void initBranch(){
    /*
    cree le fichier cache .current_branches s'il n'existe pas et 
    ecrit "master" dedans ; si le fichier existe deja, la fonction ne 
    fait rien.
    */

    if(isFile(".current_branch")){
        return;
    }

    FILE * f = fopen(".current_branc", "w");

    if(!f) return;

    fprintf(f, "master");

    fclose(f);
}

//q2 :

int branchExists(char* branch){
    /*
    renvoie un nombre != 0 si la branche de nom passe en argument existe
    dans le directory .refs 
    0 si branch=NULL ou si il n'y a pas de reference a ce nom.
    */

    if(!branch) return 0;

    unsigned pathLength= strnlen(branch,256) +7;

    char * pathRef= (char*) calloc( pathLength , sizeof(char));
    snprintf(pathRef, pathLength, ".refs/%s", branch);

    int ret= isFile(pathRef);

    free(pathRef);

    return ret;
}

//q3: 

void createBranch(char* branch){
    /*
    cree une branche de nom passe en argument pointant sur la meme ref que HEAD
    ne fait rien si branch==NULL

    ne fait rien si branche existe deja
    */

    if(!branch) return ;
    if(branchExists(branch)) return;

    char * pathRef= getRef(".refs/HEAD");

    int newBranchLength = strnlen(branch, 256) + 7;
    char * newBranchRef= (char*) calloc(newBranchLength, sizeof(char));

    snprintf(newBranchRef, newBranchLength, ".refs/%s", branch);


    FILE * f= fopen(newBranchRef, "w");

    if(!f){

        free(newBranchRef); 
        if(pathRef) free(pathRef);

        return;
    }

    if(!pathRef){
        /*
        cas :HEAD n'existe pas; etant donne que ce n'est pas normal on pourrait 
        afficher un message d'erreur et supprimer f ? 
        */
        fclose(f);


    }else{
        /*
        cas : HEAD existe et est vide ou contient la reference d'un commit; 
        dans les 2 situations on fait la meme chose; 
        peut etre les verifier separement est plus efficace
        (pas besoin d'appeller fprintf si  pathRef=="" )
        */
        fprintf(f, "%s", pathRef);
        fclose(f);
        free(pathRef);
    }

    free(newBranchRef);
}

//q4: 

char* getCurrentBranch(){
    /*
    renvoie la 1e ligne de .current_branch si elle existe, NULL sinon
    renvoie egalement NULL si fgets() se passe mal
    */

    FILE * f = fopen(".current_branch", "r"); 
    if(!f) return NULL;

    char line[256]; 
    memset(line, 0 , 256* sizeof(char));

    if(!fgets(line, 256, f)){
    //s'assure que fgets() se passe bien avant de continuer
        fclose(f); 
        return NULL;
    }

    fclose(f);

    int retLength = strnlen(line, 256)+1;

    char * ret = (char*) calloc( retLength, sizeof(char));
    snprintf(ret, retLength, "%s", line);

    return ret;
}

 //q.5: 

void printBranch(char* branch){

    if(!branch) return;

    char * commitHash = getRef(branch);
    
    if(!commitHash) return;
    if(strcmp(commitHash, "")) return;


    char * hashToPathCom = sha256file_c(commitHash);

    Commit * c= ftc(hashToPathCom);

    while(c){
        char * commitMsg= commitGet(c, "message");

        if(commitMsg){
            printf("%s %s\n", commitHash, commitMsg);
            free(commitMsg);
        }else{
            printf("%s\n", commitHash);
        }

        free(commitHash); 

        commitHash= commitGet(c, "predecessor");
        
        if(commitHash){ //verifie que predecessor existe dans le commit

            freeCommit(c);
            free(hashToPathCom); 

            hashToPathCom=sha256file_c(commitHash); 
            //realloue hashtopathcom en la path du predecesseur

            if(!hashToPathCom){ //verifie que cela c'est bien passe
                c=NULL;
            }else{

                c=ftc(commitHash);
            }
        }else{
            free(hashToPathCom);
            freeCommit(c); 
            c=NULL;
        }
        
    }

    if(commitHash)free(commitHash);
    if(hashToPathCom) free(hashToPathCom);

}//pas teste 

 //q6: 

List* branchList(char* branch){
    /*
    renvoie la liste contenant les hash des commit de branch dans 
    l'ordre chronologique

    renvoie NULL dans plusieurs cas d'erreurs
    */
    if(!branch) return NULL;

    List * l= initList(); 

    char * commit_hash = getRef ( branch ) ;

    if(!commit_hash){
        freeList(l);
        return NULL;
    }

    char * commitPath= sha256file_c(commit_hash);
    Commit * c = ftc (commitPath  ) ;

    char * commitGetPred=NULL;

    while ( c != NULL ) {

        insererFirst (l , buildCell (commit_hash) ) ;

        commitGetPred= commitGet(c, "predecessor");

        if ( commitGetPred != NULL ) {
           
           
            freeCommit(c);
            free(commitPath);

            commitPath= sha256file_c(commitGetPred);
            c = ftc (  commitPath ) ;

            free(commitGetPred);
        } else { 

            freeCommit(c);
            free(commitPath);

            c = NULL ;
        }
    }

    return l;
}//fait a l'aide de la correction ; pas teste 


 //q7: 

List* getAllCommits(){
    /*
    */

    List * ret = initList();

    List * content= listdir(".refs");

    Cell * element = *content; 

    while(element){

        

        List * dataList= branchList(element->data);

        Cell * curcell= *dataList;


        while(curcell){
            if(!searchList(ret, curcell->data)){
                insererFirst(ret, buildCell(curcell->data));
                
            }
            curcell=curcell->next;
        }
        freeList(dataList);
        element=element->next;
    }


    freeList(content);
    return ret;
}//pas teste; construit a l'aide de solution 