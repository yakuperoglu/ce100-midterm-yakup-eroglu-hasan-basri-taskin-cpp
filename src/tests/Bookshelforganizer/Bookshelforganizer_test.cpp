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

TEST_F(TryTest, updateBookTest_NotFound) {
	const char* pathFileBooks = "testBooks.bin";
	Book books[3] = {
		{1, "Book 1", "Author 1", "Genre 1", {1, "John", "", "", ""}, 0, 10},
		{2, "Book 2", "Author 2", "Genre 2", {2, "Alice", "", "", ""}, 0, 20},
		{3, "Book 3", "Author 3", "Genre 3", {3, "Bob", "", "", ""}, 0, 30}
	};
	int bookCount = 3;

	bool result = updateBook(books, bookCount, 10, "New Title", "New Author", "New Genre", 50, pathFileBooks);

	EXPECT_FALSE(result);
}

TEST_F(TryTest, deleteBookMenuTest_InvalidBookId) {
	const char* pathFileBooks = "test_books.bin";

	simulateUserInput("-1\n6asd\n\n");

	bool result = deleteBookMenu(pathFileBooks);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, updateBookMenuTest_noBookId) {
	const char* pathFileBooks = "testbooks.bin";

	simulateUserInput("-1\n6asd\n\n");

	bool result = updateBookMenu(pathFileBooks);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, updateBookMenuTest_yesCost) {
	const char* pathFileBooks = "testbooks.bin";

	simulateUserInput("2\nasd\nasd\nasd\n6\nasd\n");

	bool result = updateBookMenu(pathFileBooks);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, updateBookMenuTest_noCost) {
	const char* pathFileBooks = "testbooks.bin";

	simulateUserInput("2\nasd\nasd\nasd\n-1\n\n6\n");

	bool result = updateBookMenu(pathFileBooks);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, updateBookMenuTest_wrongId) {
	const char* pathFileBooks = "testbooks.bin";

	simulateUserInput("43\nasd\nasd\nasd\n13\n\n6\n");

	bool result = updateBookMenu(pathFileBooks);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, selectBooksByPriceMenuTest_All) {
	const char* pathFileBooks = "testbooks.bin";

	Book books[5] = {
		{1, "Book 1", "Author 1", "Genre 1", {1, "John", "", "", ""}, 0, 10},
		{2, "Book 2", "Author 2", "Genre 2", {2, "Alice", "", "", ""}, 0, 20},
		{3, "Book 3", "Author 3", "Genre 3", {3, "Bob", "", "", ""}, 0, 30},
		{4, "Book 4", "Author 4", "Genre 4", {4, "Emma", "", "", ""}, 0, 40},
		{5, "Book 5", "Author 5", "Genre 5", {5, "David", "", "", ""}, 0, 50}
	};

	saveBooks(testFilePathBooks, books, 5);

	simulateUserInput("43\nasd\nasd\nasd\n13\n\n6\n");

	bool result = selectBooksByPriceMenu(pathFileBooks);

	resetStdinStdout();

	EXPECT_TRUE(result);
}

TEST_F(TryTest, selectBooksByPriceMenuTest_budgetNoMoney) {
	const char* pathFileBooks = "testbooks.bin";

	Book books[5] = {
		{1, "Book 1", "Author 1", "Genre 1", {1, "John", "", "", ""}, 0, 10},
		{2, "Book 2", "Author 2", "Genre 2", {2, "Alice", "", "", ""}, 0, 20},
		{3, "Book 3", "Author 3", "Genre 3", {3, "Bob", "", "", ""}, 0, 30},
		{4, "Book 4", "Author 4", "Genre 4", {4, "Emma", "", "", ""}, 0, 40},
		{5, "Book 5", "Author 5", "Genre 5", {5, "David", "", "", ""}, 0, 50}
	};

	saveBooks(testFilePathBooks, books, 5);

	simulateUserInput("-3\nasd\nasd\nasd\n13\n\n6\n");

	bool result = selectBooksByPriceMenu(pathFileBooks);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, calculateBookCostsTest_BooksFound) {
	const char* pathFileBooks = "testbooks.bin";

	Book books[5] = {
		{1, "Book 1", "Author 1", "Genre 1", {1, "John", "", "", ""}, 0, 10},
		{2, "Book 2", "Author 2", "Genre 2", {2, "Alice", "", "", ""}, 0, 20},
		{3, "Book 3", "Author 3", "Genre 3", {3, "Bob", "", "", ""}, 0, 30},
		{4, "Book 4", "Author 4", "Genre 4", {4, "Emma", "", "", ""}, 0, 40},
		{5, "Book 5", "Author 5", "Genre 5", {5, "David", "", "", ""}, 0, 50}
	};

	saveBooks(testFilePathBooks, books, 5);

	simulateUserInput("-3\nasd\nasd\nasd\n13\n\n6\n");

	bool result = calculateBookCosts(pathFileBooks);

	resetStdinStdout();

	EXPECT_TRUE(result);
}

TEST_F(TryTest, calculateBookCostsTest_BooksNotFound) {
	const char* pathFileBooks = "testNoBooks.bin";

	simulateUserInput("-3\nasd\nasd\nasd\n13\n\n6\n");

	bool result = calculateBookCosts(pathFileBooks);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, CalculateBookCostsMenuTest_CheckFunctionality) {
	const char* pathFileBooks = "testBooks.bin";

	simulateUserInput("-3\nasd\nasd\nasd\n13\n\n6\n");

	bool result = calculateBookCostsMenu(pathFileBooks);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, mainMenuTest_WrongInput) {
	simulateUserInput("35\nasd\nasd\nasd\n3\n3");

	bool result = mainMenu(testFilePathUsers, testFilePathBooks, testFilePathLendingHistories, testFilePathWishlist);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, mainMenuTest_1) {
	simulateUserInput("1\nasd\nasd\nasd\n4\n3\n");

	bool result = mainMenu(testFilePathUsers, testFilePathBooks, testFilePathLendingHistories, testFilePathWishlist);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, mainMenuTest_2) {
	simulateUserInput("2\nasd\nasd\nasd\nasd\nas\n3\n3");

	bool result = mainMenu(testFilePathUsers, testFilePathBooks, testFilePathLendingHistories, testFilePathWishlist);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, mainMenuTest_3) {
	simulateUserInput("3\n");

	bool result = mainMenu(testFilePathUsers, testFilePathBooks, testFilePathLendingHistories, testFilePathWishlist);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, userOperationsTest_WrongInput) {
	simulateUserInput("35\nasd\nasd\nasd\n4\n4\n");

	bool result = userOperations(testFilePathBooks, testFilePathLendingHistories, testFilePathWishlist);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, userOperationsTest_1) {
	simulateUserInput("1\n7\n4\n");

	bool result = userOperations(testFilePathBooks, testFilePathLendingHistories, testFilePathWishlist);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, userOperationsTest_2) {
	simulateUserInput("2\n6\n4\n");

	bool result = userOperations(testFilePathBooks, testFilePathLendingHistories, testFilePathWishlist);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, userOperationsTest_3) {
	simulateUserInput("3\n6\n4\n");

	bool result = userOperations(testFilePathBooks, testFilePathLendingHistories, testFilePathWishlist);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, loginUserTest_FailedFileOpen) {
	const char* nonExistingFilePath = "empty_file.bin";

	User testUser;
	strcpy(testUser.email, "test@example.com");
	strcpy(testUser.password, "test123");

	simulateUserInput("asd_input");

	int result = loginUser(testUser, nonExistingFilePath);

	resetStdinStdout();

	EXPECT_EQ(result, 0);
	EXPECT_FALSE(result);
}

TEST_F(TryTest, loginUserTest_UsersRegistered) {
	simulateUserInput("\n\n\n");

	User testUser = {};
	int result = loginUser(testUser, testFilePathUsers);

	resetStdinStdout();

	EXPECT_EQ(result, 0);
}

TEST_F(TryTest, loginUserTest_NoUsersRegistered) {
	FILE* emptyFile = fopen(testFilePathUsers, "wb");

	simulateUserInput("\n\n\n");

	fclose(emptyFile);

	User testUser = {};

	int result = loginUser(testUser, testFilePathUsers);

	resetStdinStdout();

	EXPECT_EQ(result, 0);
}

TEST_F(TryTest, registerUserMenuTest_UserRegistered) {

	simulateUserInput("asd\nasd\nasd\nasd\n\n");

	int result = registerUserMenu(testFilePathUsers);

	resetStdinStdout();

	EXPECT_EQ(result, 1);
}

TEST_F(TryTest, registerUserMenuTest_NoFile) {
	testFilePathUsers = "non_existent_file6.bin";

	simulateUserInput("asd\nasd\nasd\nasd\n\n");

	int result = registerUserMenu(testFilePathUsers);

	resetStdinStdout();

	EXPECT_EQ(result, 1);
}

TEST_F(TryTest, viewWishlistCatalogForFuncTest_NoBook) {
	testFilePathWishlist = "non_existent_file7.bin";

	simulateUserInput("\n\n");

	bool result = viewWishlistCatalogForFunc(testFilePathWishlist);

	resetStdinStdout();

	EXPECT_TRUE(result);
}

TEST_F(TryTest, wishListTest_1) {
	simulateUserInput("1\nasd\nasd\nasd\n23\n\n3\n\n\n6");

	bool result = wishList(testFilePathBooks, testFilePathWishlist);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, wishListTest_10) {
	simulateUserInput("1\nasd\nasd\nasd\n23\n\n4\n\n6");

	bool result = wishList(testFilePathBooks, testFilePathWishlist);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, wishListTest_11) {
	simulateUserInput("1\nasd\nasd\nasd\n23\n\n2\n1\n\n6");

	bool result = wishList(testFilePathBooks, testFilePathWishlist);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, wishListTest_12) {
	simulateUserInput("1\nasd\nasd\nasd\n23\n\n2\n7\n\n6");

	bool result = wishList(testFilePathBooks, testFilePathWishlist);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, wishListTest_9) {
	simulateUserInput("1\nasd\nasd\nasd\n23\n\n3\n1\n\n6");

	bool result = wishList(testFilePathBooks, testFilePathWishlist);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, wishListTest_2) {
	simulateUserInput("2\n1\n\n6\n\nasd\n\na\n6\n\nasd\n6\n");

	bool result = wishList(testFilePathBooks, testFilePathWishlist);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, wishListTest_3) {
	simulateUserInput("3\n\n6\n");

	bool result = wishList(testFilePathBooks, testFilePathWishlist);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, wishListTest_4) {
	simulateUserInput("4\n\n6\n");

	bool result = wishList(testFilePathBooks, testFilePathWishlist);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, wishListTest_5) {
	simulateUserInput("5\nasd\n\n6\n");

	bool result = wishList(testFilePathBooks, testFilePathWishlist);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, wishListTest_6) {
	simulateUserInput("asd\n\n\n6\n");

	bool result = wishList(testFilePathBooks, testFilePathWishlist);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, wishListTest_7) {
	simulateUserInput("-23\n\n6\n");

	bool result = wishList(testFilePathBooks, testFilePathWishlist);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, wishListTest_8BinarySearch1) {
	simulateUserInput("1\nasd\nasd\nasd\n23\n\n5\nasd\n\n6\n");

	bool result = wishList(testFilePathBooks, testFilePathWishlist);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, wishListTest_8BinarySearch2) {
	simulateUserInput("1\nqwe\nqwe\nqwe\n23\n\n5\nasd\n\n6\n");

	bool result = wishList(testFilePathBooks, testFilePathWishlist);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, wishListTest_8BinarySearch3) {
	simulateUserInput("1\nzxc\nzxc\nzxc\n23\n\n5\nzxc\n\n6\n");

	bool result = wishList(testFilePathBooks, testFilePathWishlist);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, loanManagementTest_1) {
	simulateUserInput("asd\nasd\n\n6\n6\n");

	bool result = loanManagement(testFilePathBooks, testFilePathLendingHistories);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, loanManagementTest_2) {
	simulateUserInput("1\n\n6\n");

	bool result = loanManagement(testFilePathBooks, testFilePathLendingHistories);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, loanManagementTest_3) {
	simulateUserInput("2\n1\n6\n6\n");

	bool result = loanManagement(testFilePathBooks, testFilePathLendingHistories);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, loanManagementTest_4) {
	simulateUserInput("3\n\n6\n6\n");

	bool result = loanManagement(testFilePathBooks, testFilePathLendingHistories);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, loanManagementTest_5) {
	simulateUserInput("4\n\n6\n6\n");

	bool result = loanManagement(testFilePathBooks, testFilePathLendingHistories);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, loanManagementTest_6) {
	simulateUserInput("5\n\n6\n6\n");

	bool result = loanManagement(testFilePathBooks, testFilePathLendingHistories);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, loanManagementTest_7) {
	simulateUserInput("234\n\n6\n");

	bool result = loanManagement(testFilePathBooks, testFilePathLendingHistories);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, suggestBooksToBorrowTest) {


	simulateUserInput("5\n\n6\n6\n");

	bool result = suggestBooksToBorrow(testFilePathBooks);

	resetStdinStdout();

	EXPECT_FALSE(result);
}

TEST_F(TryTest, SwapTest_SwapBooks) {
	Book book1 = { 1, "Book 1", "Author 1", "Genre 1", {1, "John", "", "", ""}, 0, 10 };
	Book book2 = { 2, "Book 2", "Author 2", "Genre 2", {2, "Alice", "", "", ""}, 0, 20 };

	swap(&book1, &book2);

	EXPECT_EQ(book1.id, 1);
}

TEST_F(TryTest, PartitionTest_PartitionBooks) {
	Book books[5] = {
		{1, "Book 1", "Author 1", "Genre 1", {1, "John", "", "", ""}, 0, 10},
		{2, "Book 2", "Author 2", "Genre 2", {2, "Alice", "", "", ""}, 0, 20},
		{3, "Book 3", "Author 3", "Genre 3", {3, "Bob", "", "", ""}, 0, 30},
		{4, "Book 4", "Author 4", "Genre 4", {4, "Mike", "", "", ""}, 0, 40},
		{5, "Book 5", "Author 5", "Genre 5", {5, "Eve", "", "", ""}, 0, 50}
	};

	int pivotIndex = partition(books, 0, 4);

	EXPECT_EQ(books[pivotIndex].id, 5);
	EXPECT_EQ(pivotIndex, 4);
}

TEST_F(TryTest, RandomPartitionTest_RandomPartitionBooks) {
	Book books[5] = {
		{1, "Book 1", "Author 1", "Genre 1", {1, "John", "", "", ""}, 0, 10},
		{2, "Book 2", "Author 2", "Genre 2", {2, "Alice", "", "", ""}, 0, 20},
		{3, "Book 3", "Author 3", "Genre 3", {3, "Bob", "", "", ""}, 0, 30},
		{4, "Book 4", "Author 4", "Genre 4", {4, "Mike", "", "", ""}, 0, 40},
		{5, "Book 5", "Author 5", "Genre 5", {5, "Eve", "", "", ""}, 0, 50}
	};

	int pivotIndex = randomPartition(books, 0, 4);

	EXPECT_GE(pivotIndex, 0);
	EXPECT_LE(pivotIndex, 4);
}

TEST_F(TryTest, RandomizedQuickSortTest_RandomizedQuickSortBooks) {
	Book books[5] = {
		{4, "Book 4", "Author 4", "Genre 4", {4, "Mike", "", "", ""}, 0, 40},
		{1, "Book 1", "Author 1", "Genre 1", {1, "John", "", "", ""}, 0, 10},
		{3, "Book 3", "Author 3", "Genre 3", {3, "Bob", "", "", ""}, 0, 30},
		{2, "Book 2", "Author 2", "Genre 2", {2, "Alice", "", "", ""}, 0, 20},
		{5, "Book 5", "Author 5", "Genre 5", {5, "Eve", "", "", ""}, 0, 50}
	};

	int result = randomizedQuickSortBookIds(books, 0, 4);

	EXPECT_EQ(result, 1);
}

TEST_F(TryTest, FindLCSTest_LCSBetweenStrings) {
	const char* s1 = "abcd";
	const char* s2 = "acdb";

	double expectedLCS = 0.5;

	double result = findLCS(s1, s2);

	bool isEqual = (result == expectedLCS);

	EXPECT_FALSE(isEqual);
}

TEST_F(TryTest, MainMatrixTest_BooksFoundTest) {
	const char* testFilePathBooks = "test_books.txt";

	Book books[] = {
		{1, "Book 1", "Author 1", "Genre 1", {1, "John", "", "", ""}, 0, 10},
		{2, "Book 2", "Author 2", "Genre 2", {2, "Alice", "", "", ""}, 0, 20},
		{3, "Book 3", "Author 3", "Genre 3", {3, "Bob", "", "", ""}, 0, 30},
		{4, "Book 4", "Author 4", "Genre 4", {1, "John", "", "", ""}, 0, 10}
	};
	int bookCount = sizeof(books) / sizeof(books[0]);

	FILE* file = fopen(testFilePathBooks, "wb");
	if (file) {
		fwrite(books, sizeof(Book), bookCount, file);
		fclose(file);
	}

	simulateUserInput("\n");

	int result = mainMatrix(testFilePathBooks);

	EXPECT_EQ(result, 0);
}

TEST_F(TryTest, DeleteBookTest_BookIdFoundTest) {
	const char* testFilePathBooks = "test_books.txt";

	Book books[] = {
		{1, "Book 1", "Author 1", "Genre 1", {1, "John", "", "", ""}, 0, 10},
		{2, "Book 2", "Author 2", "Genre 2", {2, "Alice", "", "", ""}, 0, 20},
		{3, "Book 3", "Author 3", "Genre 3", {3, "Bob", "", "", ""}, 0, 30}
	};

	int bookCount = sizeof(books) / sizeof(books[0]);

	bool isFound = deleteBook(2, testFilePathBooks, books, bookCount);

	EXPECT_TRUE(isFound);
}

TEST_F(TryTest, DeleteBookTest_BookDeletedSuccessfullyTest) {
	const char* testFilePathBooks = "test_books.txt";

	Book books[] = {
		{1, "Book 1", "Author 1", "Genre 1", {1, "John", "", "", ""}, 0, 10},
		{2, "Book 2", "Author 2", "Genre 2", {2, "Alice", "", "", ""}, 0, 20},
		{3, "Book 3", "Author 3", "Genre 3", {3, "Bob", "", "", ""}, 0, 30}
	};

	int bookCount = sizeof(books) / sizeof(books[0]);

	bool isFound = deleteBook(2, testFilePathBooks, books, bookCount);

	EXPECT_TRUE(isFound);
}

TEST_F(TryTest, viewCatalog_BooksExistTest) {

	const char* testFilePathBooks = "test_books.txt";

	Book books[] = {
		{1, "Book 1", "Author 1", "Genre 1", {1, "John", "", "", ""}, 0, 10},
		{2, "Book 2", "Author 2", "Genre 2", {2, "Alice", "", "", ""}, 0, 20},
		{3, "Book 3", "Author 3", "Genre 3", {3, "Bob", "", "", ""}, 0, 30}
	};
	simulateUserInput("\n\n");

	int bookCount = sizeof(books) / sizeof(books[0]);


	int result = viewCatalog(testFilePathBooks);

	EXPECT_EQ(result, 1);
}

TEST_F(TryTest, ViewCatalogForFuncTest_NoBooksOwnedTest) {
	const char* testFilePathBooks = "testBooks.txt";

	simulateUserInput("3\n7\n");

	int result = viewCatalogForFunc(testFilePathBooks);

	EXPECT_EQ(result, 1);
}

TEST_F(TryTest, ViewCatalogForFuncTest_BooksExistTest) {
	const char* testFilePathBooks = "test_books.txt";

	Book books[] = {
		{1, "Book 1", "Author 1", "Genre 1", {1, "John", "", "", ""}, 0, 10},
		{2, "Book 2", "Author 2", "Genre 2", {2, "Alice", "", "", ""}, 0, 20},
		{3, "Book 3", "Author 3", "Genre 3", {3, "Bob", "", "", ""}, 0, 30}
	};

	int bookCount = sizeof(books) / sizeof(books[0]);

	simulateUserInput("3\n");

	int result = viewCatalogForFunc(testFilePathBooks);

	EXPECT_EQ(result, 1);
}

TEST_F(TryTest, DeleteBookMenuTest_DeleteBookSuccessTest) {
	const char* testFilePathBooks = "test_books.txt";
	const int testBookId = 1;

	simulateUserInput("2\n7\n");

	bool result = deleteBookMenu(testFilePathBooks);

	EXPECT_FALSE(result);
}

TEST_F(TryTest, UpdateBookMenuTest_InputErrorTest) {
	const char* testFilePathBooks = "test_books.txt";

	simulateUserInput("-1\n\nasd\n");

	bool result = updateBookMenu(testFilePathBooks);

	EXPECT_FALSE(result);
}

TEST_F(TryTest, UpdateBookMenuTest_UpdateSuccessfulTest) {
	const char* testFilePathBooks = "test_books.txt";

	simulateUserInput("1\nasd\nqwe\nsdf\n50\n\nasd\n");

	bool result = updateBookMenu(testFilePathBooks);


	EXPECT_TRUE(result);
}

TEST_F(TryTest, UpdateBookMenuTest_WrongPrice) {
	const char* testFilePathBooks = "test_books.txt";

	simulateUserInput("1\nasd\nqwe\nsdf\n-1\n\nasd\n");

	bool result = updateBookMenu(testFilePathBooks);


	EXPECT_FALSE(result);
}

TEST_F(TryTest, UpdateBookMenuTest_NoBookId) {
	const char* testFilePathBooks = "test_books.txt";

	simulateUserInput("25\nasd\nqwe\nsdf\n5\n\nasd\n");

	bool result = updateBookMenu(testFilePathBooks);


	EXPECT_FALSE(result);
}

TEST_F(TryTest, BorrowBookTest_BorrowBook_SuccessfulBorrow) {
	const char* testBooksFile = "testBooks.bin";
	const char* testHistoriesFile = "testHistories.bin";

	Book testBook = { 2, "Test Book", "Test Author", "Test Genre", {2, "Owner Name", "", "", ""}, 0, 10 };
	FILE* bookFile = fopen(testBooksFile, "wb");
	fwrite(&testBook, sizeof(Book), 1, bookFile);
	fclose(bookFile);

	User loggedUser = { 3, "Logged User", "", "", "" };


	bool result = borrowBook(2, testBooksFile, testHistoriesFile);

	EXPECT_TRUE(result);

	remove(testBooksFile);
	remove(testHistoriesFile);
}

TEST_F(TryTest, BorrowBookTest_BorrowBook_BookNotFound) {
	const char* testBooksFile = "testBooks.bin";
	const char* testHistoriesFile = "testHistories.bin";

	FILE* bookFile = fopen(testBooksFile, "wb");
	fclose(bookFile);

	bool result = borrowBook(1, testBooksFile, testHistoriesFile);

	EXPECT_FALSE(result);

	remove(testBooksFile);
	remove(testHistoriesFile);
}

TEST_F(TryTest, GiveBackBookTest_GiveBackBook_SuccessfulGiveBack) {
	const char* testBooksFile = "testBooks.bin";
	const char* testHistoriesFile = "testHistories.bin";

	LoanedHistory testHistory;
	testHistory.bookId = 1;
	testHistory.debtorUserId = 1;
	testHistory.hasGivenBack = 0;

	FILE* historyFile = fopen(testHistoriesFile, "wb");
	fwrite(&testHistory, sizeof(LoanedHistory), 1, historyFile);
	fclose(historyFile);

	Book testBook;
	testBook.id = 1;
	testBook.isBorrowed = 1;

	FILE* bookFile = fopen(testBooksFile, "wb");
	fwrite(&testBook, sizeof(Book), 1, bookFile);
	fclose(bookFile);

	bool result = giveBackBook(1, testBooksFile, testHistoriesFile);
	EXPECT_FALSE(result);

	remove(testBooksFile);
	remove(testHistoriesFile);
}

TEST_F(TryTest, GiveBackBookTest_GiveBackBook_BookNotBorrowedByUser) {
	const char* testBooksFile = "testBooks.bin";
	const char* testHistoriesFile = "testHistories.bin";

	LoanedHistory testHistory;
	testHistory.bookId = 1;
	testHistory.debtorUserId = 2;
	testHistory.hasGivenBack = 0;

	FILE* historyFile = fopen(testHistoriesFile, "wb");
	fwrite(&testHistory, sizeof(LoanedHistory), 1, historyFile);
	fclose(historyFile);

	Book testBook;
	testBook.id = 1;
	testBook.isBorrowed = 1;

	FILE* bookFile = fopen(testBooksFile, "wb");
	fwrite(&testBook, sizeof(Book), 1, bookFile);
	fclose(bookFile);

	bool result = giveBackBook(1, testBooksFile, testHistoriesFile);

	EXPECT_FALSE(result);

	remove(testBooksFile);
	remove(testHistoriesFile);
}

TEST_F(TryTest, BorrowBookMenuTest_BorrowBookMenu_NotSuccessfulBorrow) {
	const char* testBooksFile = "testBooks.bin";
	const char* testHistoriesFile = "testHistories.bin";

	Book testBook = { 1, "Test Book", "Test Author", "Test Genre", {2, "Owner Name", "", "", ""}, 0, 10 };
	FILE* bookFile = fopen(testBooksFile, "wb");
	fwrite(&testBook, sizeof(Book), 1, bookFile);
	fclose(bookFile);

	simulateUserInput("\n\nasd\n2\n\n");


	bool result = borrowBookMenu(testBooksFile, testHistoriesFile);

	EXPECT_FALSE(result);

	remove(testBooksFile);
	remove(testHistoriesFile);
}

TEST_F(TryTest, BorrowBookMenuTest_BorrowBookMenu_SuccessfulBorrow) {
	const char* testBooksFile = "testBooks.bin";
	const char* testHistoriesFile = "testHistories.bin";

	Book testBook = { 1, "Test Book", "Test Author", "Test Genre", {2, "Owner Name", "", "", ""}, 0, 10 };
	FILE* bookFile = fopen(testBooksFile, "wb");
	fwrite(&testBook, sizeof(Book), 1, bookFile);
	fclose(bookFile);

	simulateUserInput("1\n2\n1\n2\n1\n");


	int result = borrowBookMenu(testBooksFile, testHistoriesFile);

	EXPECT_EQ(result, 1);

	remove(testBooksFile);
	remove(testHistoriesFile);
}

TEST_F(TryTest, BorrowBookMenuTest_BorrowBookMenu_NoAvailableBooks) {
	const char* testBooksFile = "testBooks.bin";
	const char* testHistoriesFile = "testHistories.bin";

	Book testBook = { 1, "Test Book", "Test Author", "Test Genre", {2, "Owner Name", "", "", ""}, 1, 10 };
	FILE* bookFile = fopen(testBooksFile, "wb");
	fwrite(&testBook, sizeof(Book), 1, bookFile);
	fclose(bookFile);

	simulateUserInput("\n\nasd\n\nas\n\n");

	int result = borrowBookMenu(testBooksFile, testHistoriesFile);

	EXPECT_EQ(result, 0);

	remove(testBooksFile);
	remove(testHistoriesFile);
}

TEST_F(TryTest, BorrowBookMenuTest_BorrowBook_SuccessfulBorrow) {
	const char* testBooksFile = "testBooks.bin";
	const char* testHistoriesFile = "testHistories.bin";

	Book testBook = { 1, "Test Book", "Test Author", "Test Genre", {2, "Owner Name", "", "", ""}, 0, 10 };
	FILE* bookFile = fopen(testBooksFile, "wb");
	fwrite(&testBook, sizeof(Book), 1, bookFile);
	fclose(bookFile);

	simulateUserInput("\nasd\n45\n\n");

	bool result = borrowBookMenu(testBooksFile, testHistoriesFile);

	EXPECT_FALSE(result);

	remove(testBooksFile);
}

TEST_F(TryTest, BorrowBookMenuTest_BorrowBook_ErrorBorrow) {
	const char* testBooksFile = "testBooks.bin";
	const char* testHistoriesFile = "testHistories.bin";

	Book testBook = { 1, "Test Book", "Test Author", "Test Genre", {1, "Owner Name", "", "", ""}, 1, 10 };
	FILE* bookFile = fopen(testBooksFile, "wb");
	fwrite(&testBook, sizeof(Book), 1, bookFile);
	fclose(bookFile);

	simulateUserInput("\nasd\n45\n\n");

	int result = borrowBookMenu(testBooksFile, testHistoriesFile);

	EXPECT_FALSE(result);

	remove(testBooksFile);
}

TEST_F(TryTest, GiveBackBookMenu_ReturnBook_SuccessfulReturn) {
	const char* testBooksFile = "testBooks.bin";
	const char* testHistoriesFile = "testHistories.bin";

	LoanedHistory testHistory;
	testHistory.bookId = 1;
	testHistory.debtorUserId = 1;
	testHistory.hasGivenBack = 0;
	testHistory.bookOwnerId = 1;

	FILE* historyFile = fopen(testHistoriesFile, "wb");
	fwrite(&testHistory, sizeof(LoanedHistory), 1, historyFile);
	fclose(historyFile);

	LoanedHistory* testHistories = NULL;
	int historyCount = loadLoanedHistories(testHistoriesFile, &testHistories);

	Book testBook;
	testBook.id = 1;
	testBook.isBorrowed = 1;

	FILE* bookFile = fopen(testBooksFile, "wb");
	fwrite(&testBook, sizeof(Book), 1, bookFile);
	fclose(bookFile);

	Book* testBooks = NULL;
	int bookCount = loadBooks(testBooksFile, &testBooks);

	simulateUserInput("\n\n\n");

	bool result = giveBackBookMenu(testBooksFile, testHistoriesFile);
	bool result2 = writeBorrowedBooksToConsole(testHistoriesFile);
	bool result3 = writeGivenBooksToConsole(testHistoriesFile);

	EXPECT_TRUE(result);

	remove(testBooksFile);
	remove(testHistoriesFile);
}

TEST_F(TryTest, GiveBackBookMenu_ReturnBook_SuccessfulReturn1) {
	const char* testBooksFile = "testBooks.bin";
	const char* testHistoriesFile = "testHistories.bin";

	LoanedHistory testHistory;
	testHistory.bookId = 1;
	testHistory.debtorUserId = 1;
	testHistory.hasGivenBack = 0;

	FILE* historyFile = fopen(testHistoriesFile, "wb");
	fwrite(&testHistory, sizeof(LoanedHistory), 1, historyFile);
	fclose(historyFile);

	LoanedHistory* testHistories = NULL;
	int historyCount = loadLoanedHistories(testHistoriesFile, &testHistories);

	Book testBook;
	testBook.id = 1;
	testBook.isBorrowed = 1;

	FILE* bookFile = fopen(testBooksFile, "wb");
	fwrite(&testBook, sizeof(Book), 1, bookFile);
	fclose(bookFile);

	Book* testBooks = NULL;
	int bookCount = loadBooks(testBooksFile, &testBooks);

	simulateUserInput("2\n1\n");

	bool result = giveBackBookMenu(testBooksFile, testHistoriesFile);

	EXPECT_TRUE(result);

	remove(testBooksFile);
	remove(testHistoriesFile);
}

TEST_F(TryTest, SuggestBooksToBorrow_SuggestedBooksReturned_Correctly) {
	const char* testBooksFile = "testBooks.bin";

	Book testBooks[5];
	for (int i = 0; i < 5; ++i) {
		testBooks[i].id = i + 1;
		snprintf(testBooks[i].title, sizeof(testBooks[i].title), "Test Book %d", i + 1);
		snprintf(testBooks[i].author, sizeof(testBooks[i].author), "Test Author %d", i + 1);
		snprintf(testBooks[i].genre, sizeof(testBooks[i].genre), "Test Genre %d", i + 1);
		testBooks[i].isBorrowed = 0;
		testBooks[i].owner.id = i + 1;
		snprintf(testBooks[i].owner.name, sizeof(testBooks[i].owner.name), "Owner Name %d", i + 1);
	}

	FILE* bookFile = fopen(testBooksFile, "wb");
	fwrite(testBooks, sizeof(Book), 5, bookFile);
	fclose(bookFile);

	simulateUserInput("\n\n\n\n");

	bool suggestedCount = suggestBooksToBorrow(testBooksFile);

	EXPECT_FALSE(suggestedCount);

	remove(testBooksFile);
}

TEST_F(TryTest, MinFunctionTest_ReturnsCorrectMinimumValue) {
	int a = 5, b = 10;
	int result1 = min(a, b);
	EXPECT_EQ(result1, a) << "Expected " << a << " but got " << result1;
}

TEST_F(TryTest, minCostArrangingBooksTest) {
	const char* testBooksFile = "testBooks.bin";

	Book testBook;
	testBook.id = 1;
	testBook.isBorrowed = 1;

	FILE* bookFile = fopen(testBooksFile, "wb");
	fwrite(&testBook, sizeof(Book), 1, bookFile);
	fclose(bookFile);

	Book* testBooks = NULL;
	int bookCount = loadBooks(testBooksFile, &testBooks);

	simulateUserInput("2\n1\n");

	bool result = minCostArrangingBooks(testBooksFile);

	EXPECT_TRUE(result);

	remove(testBooksFile);
}

int main(int argc, char** argv) {
#ifdef ENABLE_TRY_TEST
	::testing::InitGoogleTest(&argc, argv);
	::testing::GTEST_FLAG(color) = "no";
	return RUN_ALL_TESTS();
#else
	return 0;
#endif
}