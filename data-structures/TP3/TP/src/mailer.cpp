#include <iostream>
#include <string.h>

#include "mailer.h"
#include "hash-table.h"

Mailer::Mailer(int size) {
	this->storage = new HashTable<Message>(size);
};

void Mailer::send(int userId, Message message) {
	Item<Message> item;

	item.model = message;
	item.key = message.id;

	int index = this->storage->insert(userId, item);

	std::cout << "OK: MENSAGEM " << message.id << " PARA " << userId << " ARMAZENADA EM " << index << std::endl;
};

void Mailer::read(int userId, int messageId) {
	Item<Message> item = this->storage->search(userId, messageId);

	bool itemExists = item.key != -1;

	std::string result;

	if (itemExists) {
		result = item.model.content;
	} else {
		result = "MENSAGEM INEXISTENTE";
	}

	std::cout << "CONSULTA " << userId << " " << messageId << " " << result << std::endl;
};

void Mailer::remove(int userId, int messageId) {
	Item<Message> item = this->storage->remove(userId, messageId);

	bool deleted = item.key != -1;

	if (deleted) {
		std::cout << "OK: MENSAGEM APAGADA" << std::endl;
	} else {
		std::cout << "ERRO: MENSAGEM INEXISTENTE" << std::endl;
	}
};