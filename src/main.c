#include <stdlib.h>
#include "thesh.h"

int main(int argc, char **argv){
  // Load config files, if any.
  // Run command loop.
  thesh_loop();
  // Perform any shutdown/cleanup.
  return EXIT_SUCCESS;
}
