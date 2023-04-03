#ifndef EX7_H 
#define EX7_H

extern void initRefs(); //q1

extern void createUpdateRef(char* ref_name, char* hash) ;//q2

extern void deleteRef(char* ref_name) ; //q3

extern char* getRef(char* ref_name); //q4

extern void myGitAdd( char* file_or_folder); //q5

extern void myGitCommit(char* branch_name, char* message); 

#endif