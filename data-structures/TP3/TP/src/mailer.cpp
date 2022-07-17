#include <iostream>
#include <string.h>
#include <sstream>

#include "mailer.h"
#include "hash-table.h"
#include "binary-tree-validation.h"

Mailer::Mailer(int size) {
	this->storage = new HashTable<Message>(size);
};

std::string Mailer::send(int userId, Message *message) {
	Item<Message> item;

	item.model = message;
	item.key = message->getId();

	int index = this->storage->insert(userId, item);

	std::ostringstream response;
	response << "OK: MENSAGEM " << message->getId() << " PARA " << userId << " ARMAZENADA EM " << index;
	
	return response.str();
};

std::string Mailer::read(int userId, int messageId) {
	Item<Message> item = this->storage->search(userId, messageId);

	int messageUserId = item.model->getUserId();
	bool isUserOwnerOfMessage = userId == messageUserId;
	bool itemExists = isValidNodeItem(item);

	bool isValidMessage = itemExists && isUserOwnerOfMessage;

	std::string result;

	if (isValidMessage) {
		result = item.model->getContent();
	} else {
		result = "MENSAGEM INEXISTENTE";
	}

	std::ostringstream response;
	response << "CONSULTA " << userId << " " << messageId << ": " << result;

	return response.str();
};

std::string Mailer::remove(int userId, int messageId) {
	Item<Message> item = this->storage->search(userId, messageId);
	
	bool itemExists = isValidNodeItem(item);

	std::ostringstream response;

	if (itemExists) {
		this->storage->remove(userId, messageId);

		response << "OK: MENSAGEM APAGADA";
	} else {
		response << "ERRO: MENSAGEM INEXISTENTE";
	}

	return response.str();
};