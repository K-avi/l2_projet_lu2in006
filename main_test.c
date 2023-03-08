#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ex4.h"
#include "listeChaine.h"
#include "ex3.h"
#include "ex1.h"

int main(){

//TESTS EX2
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
    
//test EX2q2.7: 

    List * liste_test_lecture = stol( "ah | bh");

    char * string_testlect = ltos(liste_test_lecture);
  
    printf("ok enft cv %s\n",string_testlect);
    
    free(string_testlect);
    

//test EX2q2.8: 

    ltof( liste_test_lecture, "test.tmp");

    List * copie_liste_test_lecture= ftol("ppzppzep");

    printf("%p\n ", copie_liste_test_lecture);

    char * string_cp_testlect = ltos(copie_liste_test_lecture);
    
 
    printf("en train de prier. %s\n",string_cp_testlect);
    
    free(string_cp_testlect);
    freeList(liste_test_lecture);
    freeList(copie_liste_test_lecture);

*/
/*
//TESTS EX3: 

//q3.1: 

    List * test_listdir= listdir("./");

    char * str_testlisdir= ltos(test_listdir);

    printf("%s\n", str_testlisdir);

    freeList(test_listdir); 
    free(str_testlisdir);

//q3.2: 
    int test_32_vrai= file_exists("main_test.c");

    printf("test_32 %d\n", test_32_vrai);

    int test_32_faux= file_exists("blablablibloblu");

    printf("test_32 %d\n", test_32_faux);

//q3.3 : 

    cp("a.tmp", "b.tmp");

//q3.4: 

    char * hash= sha256file("tmp1.tmp");

    char * hash_path= hashToPath(hash); 

    printf("hash : %s\nhashpath: %s\n", hash , hash_path);

    free(hash); 
    free(hash_path);

//q3.5: 

    blobFile("tmp1.tmp");
*/

//EX4: 

//q.1:
    WorkFile * wfile= createWorkFile("test.tmp");
    
    wfile->hash= strndup("adffeafefea", 256);
//q.2:
    char * wfile_string= wfts (wfile);
   
    printf("%s\n",wfile_string);
//q.3:

    WorkFile * wfile1= stwf(wfile_string);
    printf("%s %s %d\n", wfile1->name, wfile1->hash, wfile1->mode);

//q.4:

    WorkTree * wt= initWorkTree();

    wt->tab[0].hash= strndup("adffeafefea", 256);
    wt->tab[0].name= strndup("test.tmp", 256);
    wt->tab[0].mode=4;
    wt->n++;
    freeWorkFile(wfile);
    freeWorkFile(wfile1);
    free(wfile_string);

    int valtrue = inWorkTree( wt, "test.tmp"), valfalse= inWorkTree(wt, "testerkokz");

    printf(" valtrue est :%d\nvalfalse est : %d\n",valtrue, valfalse);

    freeWorkTree(wt);

    return 0;
}