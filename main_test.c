#include <stdio.h>
#include <stdlib.h>

#include "listeChaine.h"

int main(){

    List* liste_test= initList();

    insererFirst(liste_test,  buildCell("hehe"));
    insererFirst(liste_test,  buildCell("hoho"));

    char * test_cell = ctos((*liste_test));
  printf("%s \n" ,test_cell);


    char * test_l= ltos(liste_test);
    printf("%s\n", test_l);
  
   // free(test_cell);
    free(test_l);
    /*freeCell((*liste_test)->next);
    freeCell(*liste_test);

    
   // if( (*liste_test)->data) free( (*liste_test)->data);
  //  free( (*liste_test)); 
    free(liste_test);*/

    Cell * c_listGet_test= listGet(liste_test, 0);

    printf("contenu est: %s\n", ctos(c_listGet_test));

    Cell *  c_searchList_test = searchList(liste_test, "haha");
    printf("contenu est: %s\n", ctos(c_searchList_test));

    freeList(liste_test);

    return 0;
}