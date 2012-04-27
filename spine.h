/* 
 * written by Alexander Rich-Shea as part of 
 * an epub programming project for CSC 323 Spring 2012
 */

#ifndef SPINE
#define SPINE

#include <dirent.h>

typedef struct entryNode {
  
  char location[NAME_MAX+1]; //from dirent.h included in spine.c
  int directory;
  struct entryNode * next;

} entryNode;

typedef struct itemRefNode {

  char idref[NAME_MAX+1];
  struct itemRefNode * next;

} itemRefNode;

typedef struct spine {

  int count;
  char toc[NAME_MAX+1];
  itemRefNode * first;
  itemRefNode * last;

} spine;

itemRefNode * constructItemRefNode( char * id );

int addItemRefNode( itemRefNode * node_ptr, spine * spine_ptr);

//returns 1 on success, 0 on failure
int addSpineFile ( char * name, spine * spine_ptr );

spine * constructSpine();

void * addSpineDirectory (DIR * root_ptr, spine * spine_ptr, char * cwd);

#endif
