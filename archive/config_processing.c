/* 
 * config_processing
 * written by Alexander Rich-Shea
 *
 * Purpose: This file provides functions for processing 
 * the config file of our program
 *
 * salient functions:
 * manifest - a list of all files
 * spine - the list of files in a spine
 * 
 * mainly it's here to create a list of nodes
 * the list will first contain
 */

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

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

itemRefNode * constructItemNode( char * id ) {
  itemRefNode * node_ptr = malloc(sizeof(itemRefNode));
  strcpy(node_ptr->href, id);
  node_ptr->next = NULL;
  return node_ptr;
}

int addItemRefNode( itemRefNode * node_ptr, spine * spine_ptr) {
  if( spine_ptr->first == NULL ) {
    spine_ptr->first = node_ptr;
  } else {
    spine_ptr->last->next = node_ptr;
  }
  
  spine_ptr->last = node_ptr;
  spine_ptr->count++;
  return spine_ptr->count;
}

//returns 1 on success, 0 on failure
int addFile ( char * name, spine * spine_ptr ) {
  //printf("%s\n", name);
  itemNode * node_ptr = constructItemRefNode( name );
  return addItemRefNode( node_ptr, spine_ptr );
  
}

/* create_spine takes a linked list of directory the should specify
   the relative location of the config file 
*/
spine * create_spine ( char * location ) {
  
}


void * destroy_spine( spine * spine_ptr ) {
  itemRefNode * next_node;
  itemRefNode * temp_node = spine_ptr->first;
  
  while (temp_node != NULL) {
    next_node = temp_node->next;
    free(temp_node);
    temp_node = next_node;
  }
  
  free(spine_ptr);
}

spine * constructSpine() {
    //allocate space for the manifest
  spine * spine_ptr = malloc(sizeof(spine));
  spine_ptr->count = 0;
  spine_ptr->first = NULL;
  spine_ptr->last = NULL;
}





