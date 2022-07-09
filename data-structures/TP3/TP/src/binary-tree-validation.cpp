#include <iostream>
#include <string.h>

#include "binary-tree-validation.h"
#include "mailer.h"

template <typename Model>
bool isValidNodeItem (Item<Model> item) {
	return item.key != -1;
};

template bool isValidNodeItem<Message>(Item<Message> item);
