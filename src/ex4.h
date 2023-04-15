#ifndef EX4_H 
#define EX4_H 


typedef struct {
    char * name ;
    char * hash ;
    int mode ;
} WorkFile ;

typedef struct {
    WorkFile * tab ;
    int size ;
    int n ;
} WorkTree ;

#define WTREE_SIZE 64 //ex4.4

extern WorkFile* createWorkFile(const char* name); //ex4.1:

extern char* wfts(WorkFile* wf) ; //ex4.2

extern WorkFile* stwf(const char* ch); //ex4.3

extern WorkTree* initWorkTree() ; //ex4.4

extern int inWorkTree(WorkTree* wt, char* name); //ex4.5

extern int appendWorkTree(WorkTree* wt, char* name, char* hash, int mode); //EX4.6

extern char* wtts(WorkTree* wt) ; //ex4.7

extern WorkTree * wt_from_string( char * str) ;// ex4.8

extern int wttf(WorkTree * wt , char * file); //ex4.9

extern WorkTree * ftwt( char * file); //ex4.10


extern int getChmod(const char * path); //pour ex5

extern void setMode ( int mode , char * path ) ; //pour ex5

//necessaire ms pas demande

extern void freeWorkFile(WorkFile * wfile);
extern void freeWorkTree (WorkTree* wtree);




#endif