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

  while ((option = getopt(argc, argv, "i:I:o:O:m:M:s:S:")) != EOF) {
    switch(option) {
      case 'i':
        strcpy(parsedArgs.inputFilePath, optarg);
        break;
      case 'I':
        strcpy(parsedArgs.inputFilePath, optarg);
        break;
      case 'o':
        strcpy(parsedArgs.outputFilePath, optarg);
        break;
      case 'O':
        strcpy(parsedArgs.outputFilePath, optarg);
        break;
      case 'm':
        strcpy(parsedArgs.median, optarg);
        break;
      case 'M':
        strcpy(parsedArgs.median, optarg);
        break;
      case 's':
        strcpy(parsedArgs.partitionSize, optarg);
        break;
      case 'S':
        strcpy(parsedArgs.partitionSize, optarg);
        break;
      default:
        exit(1);
    }
  }

  return parsedArgs;
}
