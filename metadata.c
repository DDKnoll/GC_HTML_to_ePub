#ifndef METADATA_FILE
#define METADATA_FILE
/* 
 * written by Alexander Rich-Shea as part of 
 * an epub programming project for CSC 323 Spring 2012
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "metadata.h"



metadata * constructMetadata( char * title, 
                              char * author,
                              char * language, 
                              char * identifier) {
  metadata * metadata_ptr = malloc(sizeof(metadata));
  strcpy(metadata_ptr->title, title);
  strcpy(metadata_ptr->language, language);
  strcpy(metadata_ptr->identifier, identifier);
  strcpy(metadata_ptr->author, author);
  
  return metadata_ptr;
}

void * destroyMetadata ( metadata * metadata_ptr ) {
  free(metadata_ptr);
}

void * printMetadata( metadata * metadata_ptr ) {
    printf("METADATA\n%s\n%s\n%s\n%s\n", metadata_ptr->title, 
                                         metadata_ptr->author,
                                         metadata_ptr->language,
                                         metadata_ptr->identifier);
                                         
}

#endif
