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
		void send(int userId, Message message);
    void read(int userId, int messageId);
    void remove(int userId, int messageId);

	private:
		HashTable<Message> *storage;
};

#endif