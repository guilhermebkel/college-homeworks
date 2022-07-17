#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>

class Message {
  public:
    Message(int id, int userId, std::string content);
		int getId();
		std::string getContent();
		int getUserId();

	private:
		int id;
		std::string content;
		int userId;
};

#endif