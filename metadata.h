/* 
 * written by Alexander Rich-Shea as part of 
 * an epub programming project for CSC 323 Spring 2012
 */

#ifndef METADATA
#define METADATA

#include <dirent.h>
#define MAX_LINE 200

typedef struct metadata {

 char title[MAX_LINE];
 char language[MAX_LINE];
 char identifier[MAX_LINE];
 char author[MAX_LINE];

} metadata;


metadata * constructMetadata( char * title, 
                              char * author,
                              char * language, 
                              char * identifier);
                              
void * destroyMetadata ( metadata * metadata_ptr );

void * printMetadata( metadata * metadata_ptr );

#endif
