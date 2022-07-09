#include <iostream>
#include <string.h>

#include "app-validation.h"
#include "shared-util.h"

bool isSendCommand (std::string word) {
	return strcmp(word.c_str(), castChar("ENTREGA")) == 0;
};

bool isReadCommand (std::string word) {
	return strcmp(word.c_str(), castChar("CONSULTA")) == 0;
};

bool isRemoveCommand (std::string word) {
	return strcmp(word.c_str(), castChar("APAGA")) == 0;
};
