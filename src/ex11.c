#include "ex11.h"

#include "ex3.h"
#include "ex4.h"
#include "ex5.h"
#include "ex6.h"
#include "ex7.h"
#include "ex8.h"
#include "ex9.h"
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



    char * branch_ref= getRef(curbranch); //recupere le hash du commit
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


    char * commit_path = hashToPathCommit(branch_ref); //la path complete du commit courant
    free(branch_ref);

    if(!commit_path){
        /*
        cas ou le fichier de commit n'existe pas / plus ou n'a pas pu etre ouvert 
        */

        fprintf(stderr,"erreur : impossible d'acceder au dernier commit\nannulation du merge.\n"); 
        return NULL;
    }

    Commit * cur_commit = ftc(commit_path); //on charge le commit courant 
    free(commit_path);

    char * tree_ref= commitGet(cur_commit, "tree"); //on recupere la reference du worktree
    freeCommit(cur_commit);

    if(!tree_ref){
        /*
        cas ou la reference de tree n'est pas dans le commit
        */
       
        fprintf(stderr,"pas d'arbre dans le commit courant\nannulation du merge.\n");
        return NULL;
    }

    char * tree_path =hashToPath(tree_ref); //on suppose que la conversion en path se passe bien
    free(tree_ref);

    WorkTree * CurWt= ftwt(tree_path); //worktree du commit courant (enfin, c'etait si penible )
    free(tree_path);

    if(!CurWt){  
        //echec lors de l'ouverture du fichier de CurWt ou alors inexistence de celui-ci
        fprintf(stderr, "echec lors de la recuperation de l'arbre t lie a la branche courante\nVerifiez que les commit/worktree sont presents\n");
        return NULL;
    }

    char * remote_ref= getRef(remote_branch); 
    if(!remote_ref){
        /*cas ou echec de lecture remote_branch / pb d'allocation etc*/
        freeWorkTree(CurWt);
        fprintf(stderr, "echec lors de la lecture de la reference distante\nVerifiez que la reference existe\n");
        return NULL;
    }

    char * remote_path_commit = hashToPathCommit(remote_ref);
    free(remote_ref);

    Commit* remote_commit = ftc( remote_path_commit);
    free(remote_path_commit);

    if(! remote_commit){
        /*cas ou echec de lecture remote_branch / pb d'allocation etc*/
        freeWorkTree(CurWt);
        fprintf(stderr, "echec lors de la recuperation commit lie a la branche distante\nVerifiez que les commit/worktree sont presents\n");
        return NULL;
    }

    char * remote_wt_ref= commitGet(remote_commit, "tree");
    freeCommit(remote_commit);

    if(!remote_wt_ref){
        /*cas ou echec de lecture remote_branch / pb d'allocation etc*/
        freeWorkTree(CurWt);
        fprintf(stderr, "echec lors de la recuperation du hash lie a la cle tree dans le commit distant\n");
    }

    char * remote_wt_path = hashToPath(remote_wt_ref);//on suppose que ca ce passe bien etc etc
    free(remote_wt_ref);

    WorkTree * remote_wt = ftwt(remote_wt_path);
    free(remote_wt_path);

    if(!remote_wt){
        /*je devienne fou*/
        
        freeCommit(remote_commit);
        freeWorkTree(CurWt);
        fprintf(stderr, "echec lors de la recuperation du fichier stockant l'arbre du commit distant\n");
    }

    List *ret=initList(); 

    WorkTree * mergedWT =    mergeWorkTrees(CurWt, remote_wt, &ret);
    freeWorkTree(CurWt);
    freeWorkTree(mergedWT);


    if( (*ret)->next ){//un membre a ete ajoute : il y a au moins un conflit
        
        fprintf(stderr, "au moins un conflit a ete detecte: annulation du merge\n");

        freeWorkTree(mergedWT); 
        freeList(ret);
        
        return NULL;
    }else{//aucun conflits : ok de creer un commit et de merge
        
        char * ref_rm_path= getRef(remote_branch); //supprimer reference distante
        remove(ref_rm_path);
        free(ref_rm_path);
        
        remote_ref= getRef(remote_branch);
        char * curbranch_ref= getRef( curbranch);

        char * path_saved_tree = saveWorkTree(mergedWT, ".");

        Commit * c= createCommit(path_saved_tree);
        free(path_saved_tree);
        
        commitSet(c, "predecessor", curbranch_ref);
        commitSet(c, "merged_predecessor", remote_ref);
        free(curbranch_ref); 
        free(remote_ref);

        

        if(message){//si le message n'est pas nul on l'ajoute au commit 
            commitSet(c, "message", message);
        }


        char * new_commitPath= blobCommit(c);
        //on met la reference de head et la branche a jour grace a blobCommit
        createUpdateRef(curbranch, new_commitPath);
        createUpdateRef("HEAD", new_commitPath);
        
        free(new_commitPath); 
        freeCommit(c);

        myGitCheckoutBranch(".current_branch");
    }

    return NULL; //cas jamais atteint; placeholder pour eviter warning "non void function doesnt return etc"   
}

//q3: 
void createDeletionCommit(char* branch, List* conflicts, char* message){

}
//a l'aide jpp de ce truc c'est infame 