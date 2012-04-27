/* 
 * written by Alexander Rich-Shea as part of 
 * an epub programming project for CSC 323 Spring 2012
 */

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "manifest.h"

//returns the root directory of the website
DIR * get_root_dir () {
  return opendir(".");
}

//allocate space for and initialize an itemNode based on file location
itemNode * constructItemNode( char * location ) {
  itemNode * node_ptr = malloc(sizeof(itemNode));
  strcpy(node_ptr->href, location);
  node_ptr->next = NULL;
  return node_ptr;
}

//returns the number of nodes in the manifest
int addItemNode( itemNode * node_ptr, manifest * manifest_ptr) {
  if( manifest_ptr->first == NULL ) {
    manifest_ptr->first = node_ptr;
  } else {
    manifest_ptr->last->next = node_ptr;
  }
  
  manifest_ptr->last = node_ptr;
  manifest_ptr->count++;
  return manifest_ptr->count;
}
    

//returns 1 on success, 0 on failure
int addFile ( char * name, manifest * manifest_ptr ) {
  //printf("%s\n", name);
  itemNode * node_ptr = constructItemNode( name );
  return addItemNode( node_ptr, manifest_ptr );
  
}

void * addDirectory (DIR * root_ptr, manifest * manifest_ptr, char * cwd) {

  //this for statement iterates through the entries in the root directory
  //it calls add_file on the files and addDirectory on the directories
 
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
      addFile( tempcwd, manifest_ptr );
    } 
    //if it's a directory...
    else {
      strcat(tempcwd, "/");
      addDirectory( current_dir, manifest_ptr, tempcwd);
    }
  }
  
  closedir( root_ptr );
}

manifest * constructManifest() {
  //allocate space for the manifest
  manifest * manifest_ptr = malloc(sizeof(manifest));
  manifest_ptr->count = 0;
  manifest_ptr->first = NULL;
  manifest_ptr->last = NULL;
}

 
manifest * create_manifest () {
  
  //find the root directory of the website
  DIR* root_ptr = get_root_dir( );
  
  //allocate space for the manifest
  manifest * manifest_ptr = constructManifest();
  
  //char * cwd = malloc(sizeof(char)*(NAME_MAX+1));
  //strcpy(cwd, "");
  
  //run the addDirectory function. It's recursive.
  addDirectory( root_ptr, manifest_ptr, "" );
  return manifest_ptr;
}

void * destroy_manifest( manifest * manifest_ptr ) {
  itemNode * next_node;
  itemNode * temp_node = manifest_ptr->first;
  
  while (temp_node != NULL) {
    next_node = temp_node->next;
    free(temp_node);
    temp_node = next_node;
  }
  
  free(manifest_ptr);
   
}
