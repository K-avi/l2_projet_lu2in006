#include "listeChaine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List*  initList(){


    List * ret =(List*) malloc( sizeof (List ));
    
    (*ret)= (Cell*) malloc(sizeof(Cell));

    (*ret)->data= NULL; 
    (*ret)->next= NULL;

    return ret; 

}//teste ; ok


//q2.2

Cell * buildCell( char * ch){

    
    Cell * ret = malloc(sizeof(Cell)); 
    
    if(ch)ret->data=strdup(ch); //cas ou ch est null; pourrait se comporter differement 
    else ret->data=NULL; //peut etre retourner NULL si ch est NULL?

    ret->next=NULL;

    return ret; 
}//teste ; ok

//q2.3

void insererFirst (List* L , Cell* c){
    /*
    ne duplique pas c mais l'assigne
    faire attention a ne pas manipuler c ailleurs pour eviter les effets de bord. 
    (possibilite de dupliquer c si problematique)
    */
    if( !c) return;

    c->next=(*L);

    *L=c;
}//teste ; ok

//q2.4: 

char * ctos(Cell* c ){
    /*
    retourne une contenant 
    la chaine de caractere de c->data.
    NULL si la chaine ou c est NULL.
    ne duplique pas la chaine, potentiellement dangereux?
    */
    if(!c) return NULL;
    if(!c->data) return NULL;

    return (c->data);

}//teste ; ok 

char * ltos ( const List* l){
    if(!l) return NULL;

    unsigned length=0; 

    List tmp=*l ; 

    while(tmp){
        if(tmp->data){
            length+= strlen(tmp->data) +3;
            //on suppose que l'appel a strlen() ne pose pas de pb
        }
        tmp=tmp->next;
    }
    length-=2; 

    //pas besoin d'espace ou de | pour la premiere string donc on enleve 3 a la longueur finale
    //initialiser length a -3 me parait etrange, mais sans doute plus efficace ? 

    char * ret= (char*) malloc(length * sizeof(char));

    tmp=*l; 
    snprintf( ret , length , "%s", ctos(tmp));

    tmp=tmp->next;
    while( tmp){ 
       
        //snprintf empeche ret de deborder et evite les erreurs si la longueur a mal ete calculee
        char * c =ctos(tmp); 
        if(c){
            snprintf(ret +strnlen(ret, length) ,length, " | %s", c ); 
        }
        tmp=tmp->next;
    }
  
    return ret;
}//teste ; semble ok; pourrait sans doute etre fait plus efficacement. Cependant semble safe? 

//q2.5: 

Cell* listGet ( const List *L , int i){

    if(! L ) return NULL; 
    int cpt=0;

    List l= *L;
    while(cpt<i && l ){
        l=l->next;
        cpt++;
    }

    return l;
}//teste; ok 

//q2.6:

Cell * searchList(const List* L, char * str){

    List tmp= *L; 

    while( tmp){
        if(tmp->data){
            if(!strcmp(tmp->data, str)) break;
        }
        tmp=tmp->next;
    }
    return tmp;

}//teste; ok

//q2.7: 

List* stol(char *s){
    List * ret = initList();

    char * tmp1=s, *tmp2=s;

    char * tmp_dup=NULL;

    while(tmp1){

        while (*tmp2!='|'){
            tmp2++;
        }   
        tmp_dup= strndup(tmp1, tmp2-tmp1); //peut etre -1

        insererFirst(ret, buildCell(tmp_dup)); //attention

        free(tmp_dup);
        tmp1=tmp2;
        ++tmp1;

        tmp2=tmp1;
    }

    return ret; 

}//pas teste 


//q2.8: 


void ltof( List*l , char * path){

    FILE * f = fopen( path, "w");
    char * list = ltos(l);
    fprintf(f, "%s\n", list );

    free(l);
    fclose(f);

}//pas teste 

List* ftol (char * path){


    FILE * f = fopen( path, "r");
    if(!f) return NULL;

    char list[256]; 

    fgets( list, 256, f);

    fclose(f);
    return stol(list);

}//pas teste 




//pas partie des questions mais necessaire 

void freeCell( Cell * cell){

    if(!cell) return ; 
  
    if(cell->data) free(cell->data);
    free(cell);
}//teste ; ok 

void freeList(List * list){

    if(! list) return;

    List cells1 = (*list) , cells2= (*list) ;

    while(cells1){
        
        cells2=cells2->next;

        freeCell(cells1); 
        cells1=cells2;
    }

    free(list);  
}//teste; ok
