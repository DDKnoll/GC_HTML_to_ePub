/* 
 * written by Alexander Rich-Shea as part of 
 * an epub programming project for CSC 323 Spring 2012
 *
 * Modified by Dugan Knoll to test the container_xml_creator.c functions
 */


#include "process_input_file.h"
#include "spine.h"
#include "ePub_xml_creator.h"
#include "manifest.h"
#include "metadata.h"
#include "debug.h"

void * main ( int argc, char ** argv) {
  spine * my_spine;
  metadata * my_metadata;
  manifest * my_manifest;
  
  debug(argv[1]);
  debug("main: calling get_spine_and_metadata");
  
  get_spine_and_metadata( argv[1], &my_spine, &my_metadata);

  debug("main: calling create_manifest");  
  my_manifest = create_manifest();

  debug("main: calling write_all_xml");
  write_all_xml(my_metadata, my_manifest, my_spine);
  
  destroyMetadata( my_metadata );
  destroySpine( my_spine );
  destroy_manifest(my_manifest);
  
}
