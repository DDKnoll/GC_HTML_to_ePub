
#include "spine.c"



void * main (int argc, char ** argv) {
  spine * spine_ptr = constructSpine();
  itemRefNode * itemRef1 = constructItemRefNode( "node1" );
  
  addItemRefNode(itemRef1, spine_ptr);
  printSpine( spine_ptr );
  
  addFile( "node2", spine_ptr );
  printSpine(spine_ptr);
  
  DIR * current = opendir(".");
  addDirectory( current, spine_ptr, "./");
  printSpine(spine_ptr);
  
  destroySpine( spine_ptr );
  
}
  
  
  