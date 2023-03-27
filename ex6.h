#ifndef EX6_H 
#define EX6_H

typedef struct key_value_pair {
    char * key ;
    char * value ;
} kvp ;

typedef struct hash_table {
    kvp ** T ;
    int n ;
    int size ;
} HashTable ;

typedef HashTable Commit ;

#define _COMMIT_SIZE 30

extern kvp* createKeyVal(char* key, char* val); //q6.1
extern void freeKeyVal( kvp* k); //q6.1

extern char * kvts( kvp * k); //q6.2
extern kvp * stkv( char * str); //q6.2

extern Commit * initCommit(); //q6.3

extern unsigned long sdbm(unsigned char* str); //q6.4

extern void commitSet(Commit* c, char* key, char* value); //q6.5

extern Commit* createCommit(char* hash); //q6.6

extern char* commitGet(Commit* c, char* key); //q6.7

extern char* cts(Commit* c); //q6.8
extern Commit* stc(char* ch); //q6.8

extern void ctf(Commit* c, char* file); //q6.9 
extern Commit* ftc(char* file); //q6.9

extern char* blobCommit(Commit* c); //q6.10

extern char*  sha256file_c( char * c_string); //utile pour questions plus tard

extern void freeCommit( Commit* c); //pas demande mais necessaire

#endif