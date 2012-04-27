/* 
 * written by Alexander Rich-Shea as part of 
 * an epub programming project for CSC 323 Spring 2012
 */

#include "process_input_file.c"

void * main ( int argc, char ** argv) {
  spine * my_spine;
  metadata * my_metadata;
  
  debug(argv[1]);
  debug("main: calling get_spine_and_metadata");
  
  get_spine_and_metadata( argv[1], &my_spine, &my_metadata);
  
  debug("main: calling printMetadata");
  printMetadata( my_metadata );
  debug("main: calling printSpine");
  printSpine( my_spine );
  
  destroyMetadata( my_metadata );
  destroySpine( my_spine );
  
}