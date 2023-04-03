#include "ex11.h"

#include "ex4.h"
#include "ex7.h"
#include "ex8.h"
#include "listeChaine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//q1:
WorkTree* mergeWorkTrees(WorkTree* wt1, WorkTree* wt2, List** conflicts){
    /*
    fusionne 2 wt et ajoute les conflits a une liste conflicts deja allouee.

    renvoie NULL si: 

        -conflicts=NULL 
        - wt1 ET wt2 sont NULL 

        si SEULEMENT l'un des 2 est NULL   cas:  (!(wt1 && wt2)) && ( wt1 || wt2)
        recopie l'arbre non null et ne modifie pas conflicts
           
    */
    if(!conflicts) return NULL;
    
    if (! (wt1 || wt2)) return NULL; //les 2 arbres sont NULL
    
    else if(wt1 && (!wt2)){  //seul wt1 n'est pas NULL

        WorkTree * ret= initWorkTree();

        for(int i=0 ; i<wt1->n; i++){
            appendWorkTree(ret, wt1->tab[i].name,  wt1->tab[i].hash, wt1->tab[i].mode);
        }
        return ret; 
    }else{//seul wt2 n'est pas NULL

        WorkTree * ret= initWorkTree();

        for(int i=0 ; i<wt2->n; i++){
            appendWorkTree(ret, wt2->tab[i].name,  wt2->tab[i].hash, wt2->tab[i].mode);
        }
        return ret; 
    }
    //aucun des arbres n'est NULL

    WorkTree* ret= initWorkTree();
    /*
    technique utilisee pour savoir quels fichiers recuperer O( len(wt1) + len(wt2)^2 ) 
    (la complexite est relativement catastrophique je trouve...)
        -> creer un tableau skippedWT2 en parcourant wt1 pour savoir quels 
            indexs creent des conflits et ne pas copier (et mettre leurs noms dans la liste)
        -> puis prcourir wt2 en sautant les index a 1 dans skippedWT2 

        ->liberer le tableau
    */
    int * skippedWT2 = (int*) calloc(wt2->n, sizeof(int));

    for (int i=0; i<wt1->n; i++){ 
        /*ajoute elements de wt1 ; regarde quels elements il faut sauter
        et sauvegarde les indexs 
        des elements de wt2 a sauter 
        et ajoute les conflits la liste*/
        int inWT2= inWorkTree(wt2, wt1->tab[i].name);

        if(inWT2!=-1){

            insererFirst(*conflicts , buildCell(wt1->tab[i].name));
            skippedWT2[inWT2]=1;
        }else{
            appendWorkTree(ret, wt1->tab[i].name, wt1->tab[i].hash, wt1->tab[i].mode);
        }
    }

    for (int i=0; i<wt2->n; i++){
        /*
        ajoute les elements de wt2 en verifiant les conflits
        */
        if(!skippedWT2[i]){
            appendWorkTree(ret, wt2->tab[i].name, wt2->tab[i].hash, wt2->tab[i].mode);
        }
    }

    free(skippedWT2);
    return ret;

}//pas teste 


//q2: 
List* merge(char* remote_branch, char* message){
    /*
    ne fait rien si remote_branch est NULL 

    renvoie NULL et un message d'erreur si la fonction echoue a creer
    un Worktree* a partir de .current_branch 
    */
    if(!remote_branch) return NULL;
    char curbranch[256];
    memset(curbranch, 0 , 256* sizeof(char));

    FILE* f = fopen(".current_branch", "r"); 
    if(!f){ //echec lors de l'ouverture de current branch
        fprintf(stderr, "echec lors de l'ouverture de la branche courante\nVerifiez que la branche courante est bien initialisee\n");
        return NULL;
    } 

    if(!fgets(curbranch, 256, f)){ //echec lors de la LECTURE de curr branch
        fprintf(stderr, "echec lors de la recuperation des informations liees a la branche courante\nVerifiez que la branche courante est bien initialisee\n");
        fclose(f);
        return NULL;
    }
    fclose(f);



    char * branch_ref= getRef(curbranch);
//verifications autour de branch_ref: 
    if(!branch_ref){//cas ou le fichier decrit dans .current_branch n'existe pas dans .refs/

        fprintf(stderr, "erreur lors de la lecture des informations liees a la branche courante\n");
        return NULL;
    }else if(strnlen(branch_ref, 256)==0){
    /*
    cas ou le fichier dans .refs/ est vide; peut etre mieux de "fusionner" avec remote et renvoyer ok  
    */

        fprintf(stderr, "il n'y a pas eu de commit sur la branche courante\n");
        free(branch_ref);
        return NULL;
    }


    char * commit_path = hashToPathCommit(branch_ref);
    free(branch_ref);

    /*
    doit verifier -> non NULL ; non == ""

    ensuite -> convertir en path ; ouvrir fichier de wt dans le commit 
    ensuite -> recuperer le commit 
    dans le commit -> recuperer le wt 

    repeter pour remote_branch (au secours)

    une fois que tout ca est fait , appeler la fonction de la q1 
    si la liste est vide -> fusionner ; tout liberer ; renvoyer NULL 
    sinon tout liberer sauf liste -> la renvoyer

    */

    WorkTree * CurWt= ftwt(NULL);
    if(!CurWt){
        fprintf(stderr, "echec lors de la recuperation du commit lie a la branche courante\nVerifiez que les commit sont presents\n");
        return NULL;
    }

     free(commit_path);
    freeWorkTree(CurWt);
    return NULL;
}

//q3: 
void createDeletionCommit(char* branch, List* conflicts, char* message){

}
//a l'aide jpp de ce truc c'est infame 