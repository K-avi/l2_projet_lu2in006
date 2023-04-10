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

    unsigned ret_length; 
    //permet de garder trace de la longueur de ret pendant qu'on le "remplit" 
    while( tmp){ 
       
        //snprintf empeche ret de deborder et evite les erreurs si la longueur a mal ete calculee
        char * c =ctos(tmp); 
        if(c){
            ret_length= strnlen( ret ,length);
            snprintf(ret +ret_length ,length -ret_length, " | %s", c ); 
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
    /*
    renvoie la cellule de la liste contenant str dans sa case de donnee 
    si elle existe et NULL sinon.
    */
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

    if(!s) return NULL;

    List * ret = initList();

    char * tmp1=s, *tmp2=s;

    char * tmp_dup=NULL;

    unsigned lenght1=0, length2=0;

    while(*tmp1){
 //   printf("tmp1 entree %s\n", tmp1);
        while (*tmp2!='|' && *tmp2!='\0'){
            tmp2++;
            length2++;
        }  
        
        tmp_dup= strndup(tmp1, length2-lenght1); //peut etre -1
        lenght1=length2;
      //  printf("length2 est %u , tmp_dup %s\n", length2, tmp_dup );
        
        if(tmp_dup){
            insererFirst(ret, buildCell(tmp_dup)); //attention
        }

        free(tmp_dup);

        tmp1=tmp2;
        if(*tmp1){ //s'assure que l'on est bien a '|' et pas au caractere de fin de string '\0'
            ++tmp1;
        }

        tmp2=tmp1;

    }

    return ret; 

}//teste ; semble ok 


//q2.8: 


void ltof( List*l , char * path){

    FILE * f = fopen( path, "w");
    char * str_list = ltos(l);
    fprintf(f, "%s\n", str_list );

    
    fclose(f);
    free(str_list);
}//teste ; ok 

List* ftol (char * path){


    FILE * f = fopen( path, "r");
    if(!f) return NULL;

    char list[256]; 
   
    if(!fgets( list, 256, f)){
         printf("reached catching empty file\n");
        fclose(f);
        return NULL;
    }

   
    fclose(f);

    unsigned size = strcspn(list, "\n"); 

    //trouve la 1e occurrence du caractere de fin de ligne ; donc de la fin de la liste 
    //(on suppose que les strings de data ne contiennent pas de \n)
    char *clean_list= strndup( list, size);

    List * ret= stol(clean_list);

    free(clean_list);
    return ret;

}//teste ; semble ok




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
