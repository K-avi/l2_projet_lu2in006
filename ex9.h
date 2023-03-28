#ifndef EX_9_H
#define EX_9_H

#include "listeChaine.h"

extern void restoreCommit(char* hash_commit); //q1

extern void myGitCheckoutBranch(char* branch);// q2

extern List* filterList(List* L, char* pattern); //q3

extern void myGitCheckoutCommit(char* pattern); //q4

#endif