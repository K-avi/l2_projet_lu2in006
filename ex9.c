#include "ex9.h"
#include "ex3.h"
#include "ex4.h"
#include "ex5.h"
#include "ex6.h"
#include "ex7.h"
#include "ex8.h"

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
    
    restoreWorkTree ( wt , "." ) ;

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
}//ecrit ; pas teste

//q3 : 

List* filterList(List* L, char* pattern){
    return NULL;
}

//q4: 

void myGitCheckoutCommit(char* pattern){

}

