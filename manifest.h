/* 
 * written by Alexander Rich-Shea as part of 
 * an epub programming project for CSC 323 Spring 2012
 */

#ifndef MANIFEST
#define MANIFEST

#include <dirent.h>
#define TYPEMAX 100 

typedef struct itemNode {
  char  href[NAME_MAX+1]; //NAME_MAX is supplied by dirent.h and does not include the terminating null character
  char  media_type[TYPEMAX];
  struct itemNode * next;

} itemNode;

typedef struct manifest {

  int count;
  itemNode * first;
  itemNode * last;

} manifest;


DIR * get_root_dir ();

itemNode * constructItemNode( char * location );

int addItemNode( itemNode * node_ptr, manifest * manifest_ptr);

int addFile ( char * name, manifest * manifest_ptr );

void * addDirectory (DIR * root_ptr, manifest * manifest_ptr, char * cwd);

manifest * constructManifest();

//This is the function you wanna use. It creates a manifest of the current working directory
manifest * create_manifest ();

//This is what you use on the manifest to free it
void * destroy_manifest( manifest * manifest_ptr );

#endif
