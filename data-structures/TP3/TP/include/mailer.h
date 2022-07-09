#ifndef MAILER_H
#define MAILER_H

#include <iostream>
#include <string>

#include "hash-table.h"

typedef struct Message {
	int id;
	std::string content;
} Message;

class Mailer {
  public:
    Mailer(int size);
		std::string send(int userId, Message message);
    std::string read(int userId, int messageId);
    std::string remove(int userId, int messageId);

	private:
		HashTable<Message> *storage;
};

#endif