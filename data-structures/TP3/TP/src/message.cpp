#include <iostream>
#include <string.h>
#include <sstream>

#include "message.h"

Message::Message(int id, int userId, std::string content) {
	this->id = id;
	this->userId = userId;
	this->content = content;
};

int Message::getId() {
	return this->id;
};

std::string Message::getContent() {
	return this->content;
};

int Message::getUserId() {
	return this->userId;
};
