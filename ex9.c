#include "ex9.h"
#include "ex3.h"
#include "ex4.h"
#include "ex5.h"
#include "ex6.h"
#include "ex8.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//q1: 

void restoreCommit(char* hash_commit){

    if(!hash_commit) return;

    char * commit_path = hashToPathCommit ( hash_commit ) ;
printf("commit path %s\n", commit_path);
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
}//fait ; pas teste

//q2 :

void myGitCheckoutBranch(char* branch){

}

//q3 : 

List* filterList(List* L, char* pattern){
    return NULL;
}

//q4: 

void myGitCheckoutCommit(char* pattern){

}

