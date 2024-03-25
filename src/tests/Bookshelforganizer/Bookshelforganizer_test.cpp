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

TEST_F(TryTest, enterToContinueTest) {
	simulateUserInput("\n");

	bool result = enterToContinue();

	resetStdinStdout();

	EXPECT_TRUE(result);
}

TEST_F(TryTest, handleInputErrorTest) {
	simulateUserInput("asd\n");

	bool result = handleInputError();

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, getInputTest) {
	simulateUserInput("5\n");
	int result = getInput();
	EXPECT_EQ(5, result);
}

TEST_F(TryTest, getInputTest_WrongInput) {
	simulateUserInput("asd\n");
	int result = getInput();
	EXPECT_EQ(-2, result);
}

TEST_F(TryTest, getInputTest_EmptyInput) {
	simulateUserInput("");
	int result = getInput();
	EXPECT_EQ(-1, result);
}

TEST_F(TryTest, printMainMenuTest) {
	bool result = printMainMenu();
	EXPECT_TRUE(result);
}

TEST_F(TryTest, userMenuTest) {
	bool result = userMenu();
	EXPECT_TRUE(result);
}

TEST_F(TryTest, bookCatalogingMenuTest) {
	bool result = bookCatalogingMenu();
	EXPECT_TRUE(result);
}

TEST_F(TryTest, loanManagementMenuTest) {
	bool result = loanManagementMenu();
	EXPECT_TRUE(result);
}

TEST_F(TryTest, wishListMenuTest) {
	bool result = wishListMenu();
	EXPECT_TRUE(result);
}

TEST_F(TryTest, getNewUserIdTest) {
	const int userCount = 3;
	User users[userCount] = {
		{1, "John", "Doe", "john@example.com", "john123"},
		{2, "Alice", "Smith", "alice@example.com", "alice123"},
		{3, "Bob", "Johnson", "bob@example.com", "bob123"}
	};

	int newUserId = getNewUserId(users, userCount);

	int expectedNewUserId = 4;

	EXPECT_EQ(expectedNewUserId, newUserId);
}

TEST_F(TryTest, getNewUserIdTest_NoUser) {
	const int userCount = 0;
	User users[1];

	int newUserId = getNewUserId(users, userCount);

	int expectedNewUserId = 1;

	EXPECT_EQ(expectedNewUserId, newUserId);
}

TEST_F(TryTest, getNewBookIdTest) {
	const char* pathFileBooks = "testBooks.bin";

	FILE* file = fopen(pathFileBooks, "wb");
	if (file) {
		Book book = { 1, "Book Title 1", "Author 1", "asd" , 0 , 0 , 0 };
		fwrite(&book, sizeof(Book), 1, file);
		fclose(file);
	}

	int newBookId = getNewBookId(pathFileBooks);

	int expectedNewBookId = 2;

	EXPECT_EQ(expectedNewBookId, newBookId);
}

TEST_F(TryTest, getNewBookIdTest_NoBook) {
	const char* pathFileBooks = "testNoBooks.bin";

	int newBookId = getNewBookId(pathFileBooks);

	int expectedNewBookId = 1;

	EXPECT_EQ(expectedNewBookId, newBookId);
}

TEST_F(TryTest, saveBooksTest) {
	const char* path = "testBooks.bin";

	Book books[3] = {
		{ 1, "Book Title 1", "Author 1", "asd" , 0 , 0 ,0 },
		{ 2, "Book Title 2", "Author 2", "asda" , 0 , 0 ,0 },
		{ 3, "Book Title 3", "Author 3", "aassd" , 0 , 0 ,0 }
	};

	int saveResult = saveBooks(path, books, 3);

	int expectedSaveResult = 1;

	EXPECT_EQ(expectedSaveResult, saveResult);
}

TEST_F(TryTest, getNewWishlistIdTest) {
	const char* pathFileWishlist = "testWishlist.bin";

	FILE* file = fopen(pathFileWishlist, "wb");
	if (file) {
		Book book = { 1, "Book Title 1", "Author 1", "dfggc", 0 , 0 ,0 };
		fwrite(&book, sizeof(Book), 1, file);
		fclose(file);
	}

	int newWishlistId = getNewWishlistId(pathFileWishlist);

	int expectedNewWishlistId = 2;

	EXPECT_EQ(expectedNewWishlistId, newWishlistId);
}

TEST_F(TryTest, getNewWishlistIdTest_NoBook) {
	const char* pathFileWishlist = "testWishlistNoBook.bin";

	FILE* file = fopen(pathFileWishlist, "wb");
	if (file) {

	}

	int newWishlistId = getNewWishlistId(pathFileWishlist);

	int expectedNewWishlistId = 1;

	EXPECT_EQ(expectedNewWishlistId, newWishlistId);
}

TEST_F(TryTest, getNewWishlistIdTest_NoFile) {
	const char* pathFileWishlist = "non_existent_file.bin";

	int newWishlistId = getNewWishlistId(pathFileWishlist);

	int expectedNewWishlistId = 1;

	EXPECT_EQ(expectedNewWishlistId, newWishlistId);
}

TEST_F(TryTest, loadOwnedBooksTest_ValidFile_ValidUserId) {
	const char* pathFileBooks = "testBooks.bin";
	const int userId = 1;

	FILE* file = fopen(pathFileBooks, "wb");
	if (file) {
		Book books[] = {
			{1, "Book 1", "Author 1", "Genre 1", {1, "John", "", "", ""}, 0, 10},
			{2, "Book 2", "Author 2", "Genre 2", {2, "Alice", "", "", ""}, 0, 20},
			{3, "Book 3", "Author 3", "Genre 3", {3, "Bob", "", "", ""}, 0, 30},
			{4, "Book 4", "Author 4", "Genre 4", {1, "John", "", "", ""}, 0, 10}
		};
		int bookCount = sizeof(books) / sizeof(books[0]);
		fwrite(books, sizeof(Book), bookCount, file);
		fclose(file);
	}

	Book* loadedBooks = NULL;
	int bookCount = loadOwnedBooks(pathFileBooks, &loadedBooks, userId);

	EXPECT_EQ(2, bookCount);

	EXPECT_STREQ("Book 1", loadedBooks[0].title);
	EXPECT_STREQ("Book 4", loadedBooks[1].title);

	free(loadedBooks);
}

TEST_F(TryTest, loadOwnedBooksTest_InvalidFile) {
	const char* pathFileBooks = "non_existent_file1.bin";
	const int userId = 1;

	Book* loadedBooks = NULL;
	int bookCount = loadOwnedBooks(pathFileBooks, &loadedBooks, userId);

	EXPECT_EQ(-1, bookCount);
	EXPECT_EQ(nullptr, loadedBooks);
}

TEST_F(TryTest, loadUsersTest_ValidFile) {
	const char* pathFileUsers = "testUsers.bin";

	FILE* file = fopen(pathFileUsers, "wb");
	if (file) {
		User users[] = {
			{1, "John","dam","asd", "asd"},
			{2, "Alice","aer","segc","asd"},
			{3, "Bob","asedf","dfgh","dth"}
		};
		int userCount = sizeof(users) / sizeof(users[0]);
		fwrite(&userCount, sizeof(int), 1, file);
		fwrite(users, sizeof(User), userCount, file);
		fclose(file);
	}

	User* loadedUsers = NULL;
	int userCount = loadUsers(pathFileUsers, &loadedUsers);

	EXPECT_EQ(3, userCount);

	EXPECT_STREQ("John", loadedUsers[0].name);
	EXPECT_STREQ("Alice", loadedUsers[1].name);
	EXPECT_STREQ("Bob", loadedUsers[2].name);

	free(loadedUsers);
}

TEST_F(TryTest, loadUsersTest_InvalidFile) {
	const char* pathFileUsers = "testNoUsers.bin";

	User* loadedUsers = NULL;
	int userCount = loadUsers(pathFileUsers, &loadedUsers);

	EXPECT_EQ(0, userCount);
	EXPECT_EQ(nullptr, loadedUsers);
}

TEST_F(TryTest, loadBooksTest) {
	FILE* file = fopen(testFilePathBooks, "wb");
	if (file) {
		int bookCount = 3;
		Book books[] = {
			{1, "Book 1", "Author 1", "Genre 1", {1, "John", "", "", ""}, 0, 10},
			{2, "Book 2", "Author 2", "Genre 2", {2, "Alice", "", "", ""}, 0, 20},
			{3, "Book 3", "Author 3", "Genre 3", {3, "Bob", "", "", ""}, 0, 30},
			{4, "Book 4", "Author 4", "Genre 4", {4, "John", "", "", ""}, 0, 10}
		};
		fwrite(books, sizeof(Book), bookCount, file);

		fclose(file);
	}

	Book* loadedBooks = NULL;
	int bookCount = loadBooks(testFilePathBooks, &loadedBooks);

	int expectedBookCount = 3;
	const char* expectedTitle = "Book 1";

	EXPECT_EQ(expectedBookCount, bookCount);
	EXPECT_STREQ(expectedTitle, loadedBooks[0].title);

	free(loadedBooks);
}

TEST_F(TryTest, loadBooksForUserTest_ValidFile_ValidUserId) {
	const char* pathFileBooks = "testBooksForUser.bin";
	int userId = 1;

	FILE* file = fopen(pathFileBooks, "wb");
	if (file) {
		Book books[] = {
			{1, "Book 1", "Author 1", "Genre 1", {1, "John", "", "", ""}, 0, 10},
			{2, "Book 2", "Author 2", "Genre 2", {2, "Alice", "", "", ""}, 0, 20},
			{3, "Book 3", "Author 3", "Genre 3", {1, "John", "", "", ""}, 0, 30},
			{4, "Book 4", "Author 4", "Genre 4", {3, "Bob", "", "", ""}, 0, 40}
		};
		fwrite(books, sizeof(Book), sizeof(books) / sizeof(books[0]), file);
		fclose(file);
	}

	Book* filteredBooks = NULL;
	int bookCount = loadBooksForUser(pathFileBooks, userId, &filteredBooks);

	EXPECT_EQ(2, bookCount);
	EXPECT_STREQ("Book 1", filteredBooks[0].title);
	EXPECT_STREQ("Book 3", filteredBooks[1].title);

	free(filteredBooks);
}

TEST_F(TryTest, loadBooksForUserTest_InvalidFile) {
	const char* pathFileBooks = ("non_existent_file2.bin");;
	int userId = 1;

	Book* filteredBooks = NULL;
	int bookCount = loadBooksForUser(pathFileBooks, userId, &filteredBooks);

	EXPECT_EQ(-1, bookCount);
	EXPECT_EQ(nullptr, filteredBooks);
}

TEST_F(TryTest, loadLoanedHistoriesTest_EmptyFile) {
	const char* pathFileHistories = "empty_file.bin";

	FILE* file = fopen(pathFileHistories, "wb");
	if (file) {
		fclose(file);
	}

	LoanedHistory* loadedHistories = NULL;
	int historyCount = loadLoanedHistories(pathFileHistories, &loadedHistories);

	EXPECT_EQ(0, historyCount);
	EXPECT_EQ(nullptr, loadedHistories);
}

TEST_F(TryTest, loadLoanedHistoriesTest_NonEmptyFile) {
	const char* pathFileHistories = "non_empty_file.bin";

	FILE* file = fopen(pathFileHistories, "wb");
	if (file) {
		LoanedHistory histories[] = {
			{1, "Book 1", 1, "John", 2, "Alice", 1, 0},
			{2, "Book 2", 2, "Alice", 3, "Bob", 0, 0}
		};
		fwrite(histories, sizeof(LoanedHistory), 2, file);
		fclose(file);
	}

	LoanedHistory* loadedHistories = NULL;
	int historyCount = loadLoanedHistories(pathFileHistories, &loadedHistories);

	EXPECT_EQ(2, historyCount);
	EXPECT_NE(nullptr, loadedHistories);

	free(loadedHistories);
}

TEST_F(TryTest, loadLoanedHistoriesTest_InvalidFile) {
	const char* pathFileHistories = "non_existent_file3.bin";

	LoanedHistory* loadedHistories = NULL;
	int historyCount = loadLoanedHistories(pathFileHistories, &loadedHistories);

	EXPECT_EQ(0, historyCount);
	EXPECT_EQ(nullptr, loadedHistories);
}

TEST_F(TryTest, saveLoanedHistoriesTest_FileOpened) {
	const char* pathFileHistories = "testHistories.bin";

	int result = saveLoanedHistories(pathFileHistories, nullptr, 0);

	EXPECT_EQ(1, result);

	FILE* file = fopen(pathFileHistories, "rb");
	EXPECT_NE(nullptr, file);

	fclose(file);
	remove(pathFileHistories);
}

TEST_F(TryTest, bookCatalogingTest_1) {
	simulateUserInput("1\nasd\nasd\nasd\n23\n\n8\n");

	bool result = bookCataloging(testFilePathBooks);

	resetStdinStdout();


	EXPECT_FALSE(result);
}

TEST_F(TryTest, bookCatalogingTest_2) {
	simulateUserInput("2\n1\n\n8\n\n8\n\nasd\n8\n");

	bool result = bookCataloging(testFilePathBooks);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, bookCatalogingTest_3) {
	simulateUserInput("3\n2\nasd\nasd\nasd\n23\n\n8\n");

	bool result = bookCataloging(testFilePathBooks);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, bookCatalogingTest_4) {
	simulateUserInput("4\n\n8\n");

	bool result = bookCataloging(testFilePathBooks);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, bookCatalogingTest_5) {
	simulateUserInput("5\n8\n\n8");

	bool result = bookCataloging(testFilePathBooks);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, bookCatalogingTest_6) {
	simulateUserInput("6\n\n8\n\n8\n\nasd\n\n8\n");

	bool result = bookCataloging(testFilePathBooks);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, bookCatalogingTest_7) {
	simulateUserInput("1\nasd\nasd\nasd\n23\n\n7\n\n8");

	bool result = bookCataloging(testFilePathBooks);

	resetStdinStdout();


	EXPECT_FALSE(result);
}

TEST_F(TryTest, updateBookTest_All) {

	const int BookCount = 5;
	Book books[BookCount] = {
		{1, "Book 1", "Author 1", "Genre 1", {1, "John", "", "", ""}, 0, 10},
		{2, "Book 2", "Author 2", "Genre 2", {2, "Alice", "", "", ""}, 0, 20},
		{3, "Book 3", "Author 3", "Genre 3", {3, "Bob", "", "", ""}, 0, 30},
		{4, "Book 4", "Author 4", "Genre 4", {4, "Mike", "", "", ""}, 0, 40},
		{5, "Book 5", "Author 5", "Genre 5", {5, "Eve", "", "", ""}, 0, 50}
	};
	const int bookIdToUpdate = 3;
	const char* updatedTitle = "Updated Book Title";
	const char* updatedAuthor = "Updated Author";
	const char* updatedGenre = "Updated Genre";
	const int updatedCost = 100;
	simulateUserInput("\n6\n\n6");

	bool result = updateBook(books, BookCount, bookIdToUpdate, updatedTitle, updatedAuthor, updatedGenre, updatedCost, testFilePathBooks);

	resetStdinStdout();

	EXPECT_TRUE(result);
}

TEST_F(TryTest, addBookMenuTest_All) {
	simulateUserInput("asd\nasd\nasd\n-3\n\n");

	bool result = addBookMenu(testFilePathBooks);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, deleteBookTest_IsfoundFalse) {
	const char* pathFileBooks = "non_existent_file5.bin";
	Book books[3] = {
		{1, "Book 1", "Author 1", "Genre 1", {1, "John", "", "", ""}, 0, 10},
		{2, "Book 2", "Author 2", "Genre 2", {2, "Alice", "", "", ""}, 0, 20},
		{3, "Book 3", "Author 3", "Genre 3", {3, "Bob", "", "", ""}, 0, 30}
	};
	int bookCount = 3;

	bool result = deleteBook(123, pathFileBooks, books, bookCount);

	EXPECT_FALSE(result);
}
