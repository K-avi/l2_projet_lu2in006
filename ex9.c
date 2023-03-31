#include "ex9.h"
#include "ex3.h"
#include "ex4.h"
#include "ex5.h"
#include "ex6.h"
#include "ex7.h"
#include "ex8.h"
#include "listeChaine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//q1: 

void restoreCommit(char* hash_commit){

    if(!hash_commit) return;

    char * commit_path = hashToPathCommit ( hash_commit ) ;

    Commit * c = ftc ( commit_path ) ;

    char * treePath = commitGet(c, "tree");
    if(!treePath) {
        freeCommit(c); 
        free(commit_path); 
        return;
    }
    char * tree_hash = hashToPath(treePath);

    WorkTree * wt = ftwt ( tree_hash ) ;
    
    restoreWorkTree ( wt , "/tmp/tmpdir" ) ;

    freeWorkTree(wt);
    free(commit_path);
    free(tree_hash);
    freeCommit(c);
}//teste ; OK

//q2 :

void myGitCheckoutBranch(char* branch){
    if(!branch) return;

    FILE * f = fopen(".current_branch", "w");
    fprintf(f, "%s" ,branch);
    fclose(f);

    char * refBranch = getRef(branch);

    f=fopen(".refs/HEAD", "w");
    fprintf(f, "%s", refBranch);
    fclose(f);

    restoreCommit(refBranch);

    free(refBranch);
}// teste; ok

//q3 : 

List* filterList(List* L, char* pattern){
    if(! (L && pattern)) return NULL; 

    List * ret =initList();

    Cell * curcell= *L;
    unsigned len = strnlen(pattern , 256);

    while(curcell){
        if(curcell->data){
        if(!strncmp(pattern, curcell->data, len)){
            insererFirst(ret, buildCell(curcell->data));
        }
        }
        curcell=curcell->next;
    }

    return ret; 
}//teste ; ok

//q4: 


unsigned list_size (List  L ){
    /*
    */
    if(!L) return 0;

    List tmp = L;
    unsigned ret= 0;
    while(tmp){

        if(tmp->data)  ret++;

        tmp=tmp->next;
    }

    return ret; 
}//pas teste 

void myGitCheckoutCommit(char* pattern){
    if(!pattern) {
        printf("pointeur NULL passe a myGitCheckoutCommit()\n");
        return;
    }

    List * L = getAllCommits();
    
        printf("L is %p \n%s\n", L, (*L)->data);
    List * filtered_list = filterList (L , pattern ) ;
    freeList(L);


    List tmpList= *filtered_list;

    unsigned taille = list_size(tmpList);


    if( !taille ){ //cas sans element
        printf ( "Aucun pattern ne correspond au pattern passe. \n" ) ;
        
    }
    else if ( taille==1) { //cas avec 1 element

        printf("tmp data is : %s\n", tmpList->data);
        printf("un seul match trouvé : restauration du directory\n");
        char * commit_hash = ( listGet ( filtered_list , 0) ) -> data ;
        createUpdateRef ( "HEAD" , commit_hash ) ;
        restoreCommit ( commit_hash ) ;
       
    } else { //cas avec plusieurs elements
      
        printf ( "Plusieurs patterns correspondent :\n" ) ;    
        Cell * tmp = *filtered_list; 

        while(tmp){
            if(tmp->data) printf("-> %s\n", tmp->data);
            tmp=tmp->next;
        }
        
    }

    freeList(filtered_list);
   
}//pas teste 

