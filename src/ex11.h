#ifndef EX_11_H
#define EX_11_H

#include "ex4.h"
#include "listeChaine.h"


extern WorkTree* mergeWorkTrees(WorkTree* wt1, WorkTree* wt2, List** conflicts) ;//q1

extern List* merge(char* remote_branch, char* message);  //q2

extern void createDeletionCommit(char* branch, List* conflicts, char* message); //q3


#endif
