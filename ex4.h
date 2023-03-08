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

#define WTREE_SIZE 16 //ex4.4

extern WorkFile* createWorkFile(const char* name); //ex4.1:

extern char* wfts(WorkFile* wf) ; //ex4.2

extern WorkFile* stwf(const char* ch); //ex4.3

extern WorkTree* initWorkTree() ; //ex4.4

extern int inWorkTree(WorkTree* wt, char* name); //ex4.5

//necessaire ms en + 

extern void freeWorkFile(WorkFile * wfile);
extern void freeWorkTree (WorkTree* wtree);

#endif