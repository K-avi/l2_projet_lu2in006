#ifndef EX_8_H
#define EX_8_H

#include "listeChaine.h"

extern void initBranch() ; //q1

extern int branchExists(char* branch); //q2

extern void createBranch(char* branch); //q3

extern  char* getCurrentBranch(); //q4

extern void printBranch(char* branch); //q5

extern  List* branchList(char* branch); //q6

extern List* getAllCommits(); //q7

extern char * hashToPathCommit ( char * hash ); //utile

#endif