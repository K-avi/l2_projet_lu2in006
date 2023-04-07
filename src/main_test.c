#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#include "listeChaine.h"
#include "ex1.h"

#include "ex3.h"
#include "ex4.h"

#include "ex5.h"
#include "ex6.h"

#include "ex7.h"
#include "ex8.h"


#include "ex9.h"
#include "ex11.h"

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
/*
//q.1:
    WorkFile * wfile= createWorkFile("test.tmp");
    
    wfile->hash= strndup("adffeafefea", 256);
//q.2:
    char * wfile_string= wfts (wfile);
   
    printf("%s\n",wfile_string);
//q.3:

    WorkFile * wfile1= stwf(wfile_string);
  //  printf("%s %s %d\n", wfile1->name, wfile1->hash, wfile1->mode);

//q.4:

    WorkTree * wt= initWorkTree();

    wt->tab[0].hash= strndup("adffeafefea", 256);
    wt->tab[0].name= strndup("test.tmp", 256);
    wt->tab[0].mode=4;
    wt->n++;
  

//q.5: 
    int valtrue = inWorkTree( wt, "test.tmp"), valfalse= inWorkTree(wt, "testerkokz");

  //  printf(" valtrue est :%d\nvalfalse est : %d\n",valtrue, valfalse);


//q.6: 

    appendWorkTree(wt, "ex5.c", "afepokfpofea", 777);
    appendWorkTree(wt, "ex5.h", "aaapazzafepokfpofea", 777);

  //  printf("pointer after append is : %s\n", wt->tab[1].name);

//q.7: 

    char * test_wtts = wtts(wt);

  //  printf(" test q7 :\n%s", test_wtts);


//q4.8 : 

    WorkTree * test_stwt= wt_from_string(test_wtts);


     char * test_wtts1 = wtts(test_stwt);

//  printf(" test q8 :\n%s", test_wtts1);
    
//q.9: 

    //int test_q9 = wttf(test_stwt, "testq9.tmp");

//    printf("testq9: %d\n", test_q9);

//q10: 

    WorkTree* testq10= ftwt("testq9.tmp");

    char * str_test_q10 = wtts(testq10);
    //printf("testq10: \n%s", str_test_q10);

*/
/* EX5 :*/
/*
//q1:

    //blobWorkTree(testq10);

//q2: 

   char * test_5_2 = saveWorkTree(wt, "/home/ivan/Documents/L2/doc_s2/struct_donnees/projet");

//q3: 

   WorkTree * wt_ex5 =initWorkTree();


   appendWorkTree(wt_ex5, "testDir", NULL, 777);
   appendWorkTree(wt_ex5, "ex5.c", NULL, 777);
   char * path =saveWorkTree(wt_ex5, "/tmp/projetSD");
    free(path);
     
     
   
   

    char * strWTex5= wtts (wt_ex5);
   printf("%s\n", strWTex5);
   free(strWTex5);
    
   restoreWorkTree(wt_ex5, "/tmp/projetSDrecover");
freeWorkTree(wt_ex5);
//liberation de tt 
    freeWorkTree(wt);
    freeWorkFile(wfile);
    freeWorkFile(wfile1);
    free(wfile_string);
    free(test_wtts);
    freeWorkTree(test_stwt);
    free(test_wtts1);
   

   // free(test_5_2);
   // free(str_test_q10);
   // freeWorkTree(testq10);
*/
    /* EXERCICE 6 : */
/*
//q1:

    kvp * testkvp= createKeyVal("test", "tetest");


//q2:
    char * testKVTS= kvts(testkvp);
    printf("test KVTS: %s\n", testKVTS);

    kvp * testSTKV= stkv(testKVTS);

    printf("testSTKV : %s %s\n" ,testSTKV->key,  testSTKV->value);
//q3: 
    Commit * testInitCommit = initCommit(); 

//q4: 

    unsigned long hashTest= sdbm((unsigned char* )"test");
    printf("hashTest: %lu \n" ,hashTest);
    
//q5: 

    commitSet(testInitCommit, "testo", "testi");
    commitSet(testInitCommit, "testo", "testu");
    commitSet(testInitCommit, "testa", "testu");


//q6: 

    Commit* testCreateCommit = createCommit("zoifepojojpjpzjf");

//q7: 

    char * testCommitGet = commitGet(testInitCommit, "testo");
    printf("testCommitGet : %s\n", testCommitGet);

   char * testCommitGet1= commitGet(testInitCommit, "testatataat");
    printf("testCommitGet1 : %s\n", testCommitGet1);
//q8: 

    char * testCTS= cts(testInitCommit);

    printf("testCTS:\n\n%s\n", testCTS);

    Commit * testSTC = stc(testCTS);

    free(testCTS);

     char * testSTCstr= cts(testSTC);

    printf("testSTCstr:\n\n%s\n", testSTCstr);
//q9: 

    ctf(testInitCommit, "ex6q9.test");

    Commit * testFTC= ftc("ex6q9.test");

    char * testFTCstr= cts(testFTC);

    printf("testFTCstr\n%s", testFTCstr); 

//q10: 

    char * testblobCommit = blobCommit(testInitCommit);

    printf("testblobCommit %s\n", testblobCommit);

    free(testblobCommit);
    free(testFTCstr);
    freeCommit(testFTC);

    free(testSTCstr);

    freeCommit(testSTC);

    free(testKVTS);
    freeKeyVal(testkvp);
    freeKeyVal(testSTKV);
    freeCommit(testInitCommit);
    freeCommit(testCreateCommit);
*/

//EX7: 
/*
//q1: 

    initRefs();

//q2: 
    createUpdateRef("HEAD", "abababa");
    createUpdateRef("bagaba", "abababagababa");
    createUpdateRef("HEAD", "babababi");
    createUpdateRef("HEAD", "");
//q3: 
    deleteRef("bagaba");
     deleteRef("bagaba");

//q4: 

   // char * testGetRef= getRef("HEAD");
   // char * testGetRefNull= getRef("je n'existe pas!");
  //  printf( "testGetRef %s\n", testGetRef);

   // printf("test GetRefNull %s\n",testGetRefNull);

   // free(testGetRef);
//q5: 
    myGitAdd("tmp");
    myGitAdd("ex6.h");
//q6: 

    myGitCommit("master", "tous mes espoirs et reves");

    myGitAdd("ex6.c");
    myGitAdd("main_test.c");

    myGitCommit("master", "si ca marche je crie");
    //ca marche ???? ; j'y crois pas ???? 
*/


//EX8: 
/*
//q1: 
    initBranch();

//q2:
    int brancheExistTest1 = branchExists("master");
    int brancheExistTest2= branchExists("babobibu");

    printf("master exists : %d babobibu exists : %d\n", brancheExistTest1 , brancheExistTest2);

//q3: 

    createBranch("dev");

//q4: 

    char * testGetCurBranch = getCurrentBranch();

    printf("current branch : %s\n" , testGetCurBranch);

    free(testGetCurBranch);*/

//q5: 

    /*initRefs();

    myGitAdd("main_test.c");
    myGitCommit("master", "test 1 commit");

    printBranch("master");

    myGitAdd("ex8.c");
    myGitCommit("master", "test apres 2e commit");

    printBranch("master");
*/

//q6: 
    /*
    List * testLBranch = branchList("master"); 

    char * strtestlbranch = ltos(testLBranch);

    printf("test lbranch : %s\n", strtestlbranch);

    free(strtestlbranch); 
    freeList(testLBranch);
    */
    
//q7: 
/*

    List * testGetAll = getAllCommits();

    char * GetAllStr= ltos(testGetAll); 

    printf("test getallcommit %s", GetAllStr);

    free(GetAllStr);
    freeList(testGetAll);*/


//EX 9  :

//q1:

    initRefs();

    myGitAdd("ex9.c"); 
    myGitAdd("ex9.h"); 
    myGitAdd("main_test.c"); 
    myGitAdd("tmp");

    myGitCommit("master", "test ex9.1");
//  NE PAS DECOMMENTER ; DANGEREUX     !!!
   // restoreCommit("74554e8caf71a1d7c38455808dcd10a9021e28545307aaedbe71491f5a2eb30c.c");


//q2

  //  myGitCheckoutBranch("master");

//q3: 

    List * ltest= initList();

    insererFirst(ltest, buildCell("titi")); 
    insererFirst(ltest, buildCell("tito"));
    insererFirst(ltest, buildCell("toto"));  

    List * filterListTest= filterList(ltest, "ti");

    char * strListTest= ltos(filterListTest);

    printf("test filterList:\n%s\n", strListTest);

    free(strListTest);

    freeList(ltest);
    freeList(filterListTest);

//q4:

    List * testGetAll = getAllCommits();

    char * GetAllStr= ltos(testGetAll); 

    printf("\ntest getallcommit %s\n", GetAllStr);

    free(GetAllStr);
    freeList(testGetAll);

    myGitCheckoutCommit("93");
//ex11: 

//q1: 


//q2: 
    merge("test-creation", "ca ne va pas marcher je pense.");

    return 0;
}