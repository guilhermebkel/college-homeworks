#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "app-util.h"

ParsedArgs parseArgs (int argc, char **argv) {
  extern char * optarg;
  extern int optind;

  int option;

  ParsedArgs parsedArgs;

  while ((option = getopt(argc, argv, "i:o:")) != EOF) {
    switch(option) {
      case 'i':
        strcpy(parsedArgs.inputFilePath, optarg);
        break;
      case 'o':
        strcpy(parsedArgs.outputFilePath, optarg);
        break;
      default:
        exit(1);
    }
  }

  return parsedArgs;
}
