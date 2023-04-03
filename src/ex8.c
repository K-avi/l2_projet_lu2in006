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

    FILE * f = fopen(".current_branch", "w");

    if(!f) return;

    fprintf(f, "master");

    fclose(f);
}//teste; ok

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
}//teste ok

//q3: 

void createBranch(char* branch){
    /*
    cree une branche de nom passe en argument pointant sur la meme ref que HEAD
    ne fait rien si branch==NULL

    ne fait rien si branche existe deja
    */

    if(!branch) return ;
    if(branchExists(branch)) return;

    char * pathRef= getRef("HEAD");

    
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
}//teste ; ok

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

char * hashToPathCommit ( char * hash ) {
 
 char * dirPath = hashToPath(hash);
 char * ret = (char*)calloc ( strnlen(dirPath,256)+2, sizeof (char)) ;

 sprintf ( ret , "%s" , dirPath ) ;

 free(dirPath);
 return ret ;
}

void printBranch(char* branch){

    if(!branch) return;

    char * commitHash = getRef(branch);
    
    if(!commitHash){
         fprintf(stderr, "la branche %s n'existe pas\n", branch);
         return;
    }
   
    if(strlen(commitHash)==0){
        free(commitHash);
        return;
    }

    char * hashToPathCom = hashToPathCommit(commitHash);
    
    if(!hashToPathCom){
        free(commitHash) ;
        return;
    }
  
    Commit * c= ftc(hashToPathCom);
  
    char * commitMsg ;

    while(c){

        
        commitMsg= commitGet(c, "message");
        if(commitMsg) commitMsg= strdup(commitMsg); 
        //permet d'eviter appels a strdup avc NULL; cela dit c'est hideux.
        //pourquoi comment pourquoi ca fait pas de memleaks; 
        //serieusement ca devrait ; pourquoi ca en fait pas
        //et si j'enleve la ligne ca fait des free invalides
        //j'ai aucune idee de pk c'est correct.

        if(commitMsg){
            printf("%s %s\n", commitHash, commitMsg);
            free(commitMsg);
        }else{
            printf("reached print commit hash\n");
            printf("%s\n", commitHash);
        }
       

        if(commitHash)free(commitHash);

        commitHash= commitGet(c, "predecessor");
     
        if(commitHash) commitHash= strdup(commitHash); //atroce 

        if(commitHash){ //verifie que predecessor existe dans le commit

            freeCommit(c);
            c=NULL;
            if(hashToPathCom) free(hashToPathCom); 
            
            hashToPathCom=hashToPathCommit(commitHash); 
           
            //realloue hashtopathcom en la path du predecesseur

            if(!hashToPathCom){ //verifie que cela c'est bien passe
                c=NULL;
            
            }else{

                c=ftc(hashToPathCom);
                //printf("c after ftc %p\n", c);
            }

        }else{

            if(hashToPathCom) free(hashToPathCom);
            hashToPathCom=NULL;

            freeCommit(c); 
            c=NULL;
        }
        
    }
 
    if( commitHash) free(commitHash);
    if(hashToPathCom) free(hashToPathCom);

}//teste; ok ???????????????????????????? 

 
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

    char * commitPath= hashToPathCommit(commit_hash);
    Commit * c = ftc (commitPath  ) ;

    char * commitGetPred=NULL;
   
    insererFirst (l , buildCell (commit_hash) ) ;
    free(commit_hash);
    commit_hash= NULL;

    free(commitPath);
    commitPath=NULL;

    while ( c != NULL ) {

        

        commitGetPred= commitGet(c, "predecessor");
        if(commitGetPred) commitGetPred= strdup(commitGetPred);
        

        if ( commitGetPred != NULL ) {
            
            insererFirst(l, buildCell(commitGetPred));
           
            freeCommit(c);
            free(commitPath);

            commitPath= hashToPathCommit(commitGetPred);

           // printf("commit path %s\n", commitPath);
            c = ftc (  commitPath ) ;

            free(commitGetPred);
        } else { 

            freeCommit(c);
            free(commitPath);

            c = NULL ;
        }
    }
  
    return l;
}//fait a l'aide de la correction ; teste ok


 //q7: 

List* getAllCommits(){
    /*
    */

    List * ret = initList();
    List * content= listdir(".refs");
    
    if(!content) {
       
        freeList(ret); 
        freeList(content);
        return NULL;
    }

    Cell * element = *content; 

    while(element){
        
      //   printf("element entree %p\n", element);
      //   printf("element dat %p\n" , element->data );
        if(!element->data){
            element=element->next; 
        
        }else if(!strcmp(".add", element->data)){

            element=element->next;
        }else{
            List * dataList= branchList(element->data);
            Cell * curcell= *dataList;

           // printf("dataL %p curcell %p \n", dataList, curcell);
            while(curcell){

             //   printf("curcell->data %p\n", curcell->data);
                
                if(curcell->data){    
                    if(!searchList(ret, curcell->data)){
                        insererFirst(ret, buildCell(curcell->data));    
                    }
                    
                }
                curcell=curcell->next;
            }

            freeList(dataList);
            dataList=NULL;
            element=element->next;
            }

       // printf("element sortie %p\n", element);
    }


    freeList(content);
    return ret;
}//teste; semble ok; construit a l'aide de solution 