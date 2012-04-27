
/* 
 * written by Alexander Rich-Shea as part of 
 * an epub programming project for CSC 323 Spring 2012
 */

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include "debug.h"
#include "spine.h"



itemRefNode * constructItemRefNode( char * id ) {
  itemRefNode * node_ptr = malloc(sizeof(itemRefNode));
  strcpy(node_ptr->idref, id);
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
int addSpineFile ( char * name, spine * spine_ptr ) {
  //printf("%s\n", name);
  itemRefNode * node_ptr = constructItemRefNode( name );
  return addItemRefNode( node_ptr, spine_ptr );
  
}

spine * constructSpine() {
    //allocate space for the manifest
  spine * spine_ptr = malloc(sizeof(spine));
  spine_ptr->count = 0;
  spine_ptr->first = NULL;
  spine_ptr->last = NULL;
}

void * addSpineDirectory (DIR * root_ptr, spine * spine_ptr, char * cwd) {

  //this for statement iterates through the entries in the root directory
  //it calls addFile on the files and addDirectory on the directories
 
  DIR * current_dir;
  struct dirent * dir_struct;
  char tempcwd[NAME_MAX+1];
  
  for (dir_struct = readdir( root_ptr ); dir_struct != NULL; dir_struct = readdir( root_ptr )) {
    
    strcpy(tempcwd, cwd);
    
    if (strcmp(dir_struct->d_name, "..") == 0  || strcmp(dir_struct->d_name, ".") == 0) {
      continue;
    }
    
    //check to see if the current directory entry is a directory or a file
    current_dir = opendir( strcat(tempcwd, dir_struct->d_name) );
    //if it's a file...
    if (current_dir == NULL) {
      //printf("%s %s %d %s\n", dir_struct->d_name, tempcwd, errno, strerror(errno));
      addSpineFile( tempcwd, spine_ptr );
    } 
    //if it's a directory...
    else {
      strcat(tempcwd, "/");
      addSpineDirectory( current_dir, spine_ptr, tempcwd);
    }
  }
  
  closedir( root_ptr );
}

/* create_spine takes a linked list of directory the should specify
   the relative location gccof the config file 
*/
spine * create_spine ( entryNode * spine_head ) {
  spine * spine_ptr = constructSpine();
  entryNode * temp;
  DIR * directory_ptr;
  char cwd[NAME_MAX];
  
  for (temp = spine_head; temp != NULL; temp = temp->next) {
    if (temp->directory == 1) {
      debug("create_spine: directory encountered. processing...");
      directory_ptr = opendir(temp->location);
      if (directory_ptr == NULL) {
        printf("could not open %s\n", temp->location);
        return NULL;
      }
      //debug("create_spine: directory opened:");
      //debug(temp->location);
      strcpy(cwd, temp->location);
      strcat(cwd, "/");
      addSpineDirectory(directory_ptr, spine_ptr, cwd);
      debug("create_spine: directory added");
    } else {
      addSpineFile(temp->location, spine_ptr);
    }
  }
  
  return spine_ptr;
  
}



void * destroySpine( spine * spine_ptr ) {
  itemRefNode * next_node;
  itemRefNode * temp_node = spine_ptr->first;
  
  while (temp_node != NULL) {
    next_node = temp_node->next;
    free(temp_node);
    temp_node = next_node;
  }
  
  free(spine_ptr);
}

void * destroyEntryNode( entryNode * node ) {
  entryNode * temp, * next;
  for( temp = node; temp != NULL;) {
    next = temp->next;
    free(temp);
    temp = next;
  }
}

void * printSpine( spine * spine_ptr ) {
  itemRefNode * temp;
  printf("SPINE\n");
  for (temp = spine_ptr->first; temp != NULL; temp = temp->next) {
    printf("%s\n", temp->idref);
  }
}






