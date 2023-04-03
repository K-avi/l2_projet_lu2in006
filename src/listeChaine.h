#ifndef LISTE_CHAINE
#define LISTE_CHAINE 


typedef struct cell{

    char *data; 
    struct cell * next; 

}Cell; 
typedef Cell* List; 

extern List*  initList();

extern Cell * buildCell( char * ch); //q2.2

extern void insererFirst (List* L , Cell* c); //q2.3

extern char * ctos(Cell* c ); //q2.4
extern char * ltos ( const List* l); //q2.4

extern Cell* listGet ( const List *L , int i); //q2.5

extern Cell * searchList(const List* L, char * str) ;//q2.6

extern List* stol(char *s) ; //q2.7

extern void ltof( List*l , char * path); //q2.8
extern List* ftol (char * path); //q2.8

extern void freeList(List * list);
extern void freeCell( Cell * cell);

#endif 