#ifndef LISTE_CHAINE
#define LISTE_CHAINE 


    typedef struct cell{
        char *data; 
        struct cell * next; 
    }Cell; 
    typedef Cell* List; 

#endif 