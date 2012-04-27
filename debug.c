#include <stdio.h>

#define DEBUG 1


void debug( char * message ) {
  if (DEBUG) {
    printf("%s\n", message);
  }
}
