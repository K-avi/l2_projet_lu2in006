#ifndef EX3_H 
#define EX3_H 


#include "listeChaine.h"

extern List* listdir(char* root_dir) ;//q3.1

extern int file_exists( char * str); //q3.2

extern void cp (const char *from , const char * to); //q3.3

extern char* hashToPath(char* hash); //q3.4

extern void blobFile(char* file); //q3.5
#endif