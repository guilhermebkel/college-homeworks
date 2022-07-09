#include <iomanip>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>

#include "msgassert.h"
#include "memlog.h"
#include "app-util.h"
#include "shared-util.h"
#include "app-memlog.h"
#include "mailer.h"
#include "app-validation.h"

int main(int argc, char ** argv) {
	std::string memoryLogOutputFilePath = "../data/memlog/output/log.out";

	iniciaMemLog(castChar(memoryLogOutputFilePath));
	ativaMemLog();

	ParsedArgs parsedArgs = parseArgs(argc, argv);

	std::ifstream inputFile(parsedArgs.inputFilePath);
	erroAssert(!inputFile.fail(), "Input file was not found.");

	int mailerHashTableSize;
	inputFile >> mailerHashTableSize;

	Mailer *mailer = new Mailer(mailerHashTableSize);

	FILE *outputFile;
  outputFile = fopen(parsedArgs.outputFilePath, "wt");
	erroAssert(outputFile != NULL, "Failed to create output file.");

	while (true) {
		std::string result;
		inputFile >> result;

		if (isSendCommand(result)) {
			defineFaseMemLog(MemoryLogLevel::MAILER_SEND);

			int userId;
			inputFile >> userId;

			int messageId;
			inputFile >> messageId;

			int messageWordsCount;
			inputFile >> messageWordsCount;

			std::string messageContent;

			for (int i = 0; i < messageWordsCount; i++) {
				std::string word;
				inputFile >> word;

				messageContent.append(word);

				bool isLastWord = i == messageWordsCount - 1;

				if (!isLastWord) {
					messageContent.append(" ");
				}
			}

			Message message;
			message.id = messageId;
			message.content = messageContent;

			std::string response = mailer->send(userId, message);
			fprintf(outputFile, "%s\n", response.c_str());
		}

		if (isReadCommand(result)) {
			defineFaseMemLog(MemoryLogLevel::MAILER_READ);

			int userId;
			inputFile >> userId;

			int messageId;
			inputFile >> messageId;

			std::string response = mailer->read(userId, messageId);
			fprintf(outputFile, "%s\n", response.c_str());
		}

		if (isRemoveCommand(result)) {
			defineFaseMemLog(MemoryLogLevel::MAILER_REMOVE);

			int userId;
			inputFile >> userId;

			int messageId;
			inputFile >> messageId;

			std::string response = mailer->remove(userId, messageId);
			fprintf(outputFile, "%s\n", response.c_str());
		}

		bool finishedReadingFile = inputFile.eof();

		if (finishedReadingFile) {
			break;
		}
	}

	finalizaMemLog();

	return 0;
}