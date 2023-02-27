#include "listeChaine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List*  initList(){


    List * ret =(List*) malloc( sizeof (List ));
    
    *ret= (Cell*) malloc(sizeof(Cell));

    (*ret)->data= NULL; 
    (*ret)->next= NULL;

    return ret; 
}


//q2.2

Cell * buildCell( char * ch){

    
    Cell * ret = malloc(sizeof(Cell)); 

    ret->data=strdup(ch);

    return ret; 
}

//q2.3

void insererFirst (List* L , Cell* c){
    if( !c) return;

    c->next=(*L);

    *L=c;
}

//q2.4: 

char * ctos(Cell* c ){
    
    return c->data;
}

char * ltos (List* l){
    if(!l) return NULL;

    unsigned length=0; 

    List tmp=*l ; 

    while(tmp){
        length+= strlen(tmp->data);
        tmp=tmp->next;
    }

    char * ret= (char*) malloc(length * sizeof(char));

    tmp=*l; 

    while( tmp){ 
        if(tmp->next)
            sprintf(ret, "%s | ", ctos(tmp) );
        else{
            sprintf(ret, "%s | ", ctos(tmp) );
        }
    }

    return ret;
}

//q2.5: 

Cell* listGet (List *L , int i){

    if(! L ) return NULL; 
    int cpt=0;

    List l= *L;
    while(cpt<i && l ){
        l=l->next;
        cpt++;
    }

    return l;
}

//q2.6:

Cell * searchList(List* L, char * str){

    List tmp= *L; 

    while( tmp){
        if(!strcmp(tmp->data, str)) break;
        tmp=tmp->next;
    }
    return tmp;
}

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
}


//q2.8: 


void ltof( List*l , char * path){

    FILE * f = fopen( path, "w");
    char * list = ltos(l);
    fprintf(f, "%s\n", list );

    free(l);
    fclose(f);

}

List* ftol (char * path){


    FILE * f = fopen( path, "r");
    char list[256]; 

    fgets( list, 256, f);

    return stol(list);
}
