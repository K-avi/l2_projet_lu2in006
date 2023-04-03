#ifndef EX5_H
#define EX5_H


#include "ex4.h"
#include "ex1.h"


extern char * blobWorkTree (WorkTree* wt); //q1
extern char * saveWorkTree (WorkTree * wt, char * path); //q2

extern void restoreWorkTree( WorkTree * wt , char * path); //q3

extern int isDirectory(const char *path) ; //globalement utile
extern int isFile(const char *path); //globalement utile
#endif