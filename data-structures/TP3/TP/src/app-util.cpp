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

  parsedArgs.quickSortPivot = -1;
  parsedArgs.quickSortMaxPartitionSize = -1;

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
        parsedArgs.quickSortPivot = atoi(optarg);
        break;
      case 'M':
        parsedArgs.quickSortPivot = atoi(optarg);
        break;
      case 's':
        parsedArgs.quickSortMaxPartitionSize = atoi(optarg);
        break;
      case 'S':
        parsedArgs.quickSortMaxPartitionSize = atoi(optarg);
        break;
      default:
        exit(1);
    }
  }

  return parsedArgs;
}
