#include <iostream>
#include <string.h>

#include "app-validation.h"
#include "shared-util.h"

bool isOrderingConfig (std::string word) {
	return strcmp(word.c_str(), castChar("#ORDEM")) == 0;
};

bool isTextConfig (std::string word) {
	return strcmp(word.c_str(), castChar("#TEXTO")) == 0;
};
