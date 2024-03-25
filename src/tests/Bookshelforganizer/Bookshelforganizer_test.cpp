#define _CRT_SECURE_NO_WARNINGS
#include "../../try/header/try.h"  
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "gtest/gtest.h"

class BookshelforganizerTest : public ::testing::Test {
protected:
	const char* inputTest = "inputTest.txt";
	const char* outputTest = "outputTest.txt";
	void SetUp() override {
		// Setup test data
	}

	void TearDown() override {
		remove("inputTest");
		remove("outputTest");
		remove("testBooks.bin");
		remove("testNoBooks.bin");
		remove("testWishlist.bin");
		remove("testWishlistNoBook.bin");
		remove("non_existent_file.bin");
		remove("non_existent_file1.bin");
		remove("non_existent_file2.bin");
		remove("non_existent_file3.bin");
		remove("non_existent_file4.bin");
		remove("non_existent_file5.bin");
		remove("non_existent_file6.bin");
		remove("non_existent_file7.bin");
		remove("testNoUsers.bin");
		remove("testBooksForUser.bin");
		remove("empty_file.bin");
		remove("non_empty_file.bin");
		remove("testHistories.bin");

	}
	void simulateUserInput(const char* userInput) {
		FILE* fileinput = fopen(inputTest, "wb");
		fputs(userInput, fileinput);
		fclose(fileinput);
		freopen(inputTest, "rb", stdin);
		freopen(outputTest, "wb", stdout);
	}

	void readOutput(const char* outputFilePath, char* buffer, size_t bufferSize) {
		FILE* fileoutput = fopen(outputFilePath, "rb");
		size_t charsRead = fread(buffer, sizeof(char), bufferSize - 1, fileoutput);
		fclose(fileoutput);
		buffer[charsRead] = '\0';
		removeClearScreenCharsFromOutputFile(buffer);
	}

	void resetStdinStdout() {
		fclose(stdin);
		fflush(stdout);
#ifdef _WIN32
		freopen("CON", "a", stdout);
		freopen("CON", "r", stdin);
#else
		freopen("/dev/tty", "a", stdout);
		freopen("/dev/tty", "r", stdin);
#endif // _WIN32
	}

	void removeClearScreenCharsFromOutputFile(char* str) {
		char* src = str;
		char* dst = str;
		while (*src) {
			if (*src != '\f') {
				*dst++ = *src;
			}
			src++;
		}
		*dst = '\0';
	}

};

const char* testFilePathUsers = "testUsers.bin";
const char* testFilePathBooks = "testBooks.bin";
const char* testFilePathLendingHistories = "testHistories.bin";
const char* testFilePathWishlist = "testWishlist.bin";
