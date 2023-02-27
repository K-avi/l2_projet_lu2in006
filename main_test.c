#include <stdio.h>
#include <stdlib.h>

#include "listeChaine.h"

int main(){

   /* List* liste_test= initList();

    insererFirst(liste_test,  buildCell("hehe"));
    insererFirst(liste_test,  buildCell("hoho"));

    char * test_cell = ctos((*liste_test));
    printf("%s \n" ,test_cell);


    char * test_l= ltos(liste_test);
    printf("%s\n", test_l);
  
    // free(test_cell);
    free(test_l);
    freeCell((*liste_test)->next);
    freeCell(*liste_test);

    
    // if( (*liste_test)->data) free( (*liste_test)->data);
    //  free( (*liste_test)); 
    free(liste_test);

    Cell * c_listGet_test= listGet(liste_test, 0);

    printf("le contenu est: %s\n", ctos(c_listGet_test));

    Cell *  c_searchList_test = searchList(liste_test, "haha");
    printf("le contenu est: %s\n", ctos(c_searchList_test));

    freeList(liste_test);
    */
//test q2.7: 

    List * liste_test_lecture = stol( "ah | bh");

    char * string_testlect = ltos(liste_test_lecture);
  
    printf("ok enft cv %s\n",string_testlect);
    
    free(string_testlect);
    

//test q2.8: 

    ltof( liste_test_lecture, "test.tmp");

    List * copie_liste_test_lecture= ftol("ppzppzep");

    printf("%p\n ", copie_liste_test_lecture);

    char * string_cp_testlect = ltos(copie_liste_test_lecture);
    
 
    printf("en train de prier. %s\n",string_cp_testlect);
    
    free(string_cp_testlect);
    freeList(liste_test_lecture);
    freeList(copie_liste_test_lecture);


    return 0;
}