/**
 * @file Try.cpp
 *
 * @brief This file contains implementations of various utility functions and defines a global user variable.
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdexcept>
#include <regex>
#include <fstream>
#include <stdio.h>
#include <limits>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "Try.h"

 /**
  * @brief Clears the console screen.
  *
  * This function clears the console screen based on the operating system.
  */
User loggedUser;

//TOOLS

void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

/**
 * @brief Waits for the user to press enter to continue.
 *
 * This function prompts the user to press enter to continue and waits for the input.
 *
 * @return Always returns 1.
 */
int enterToContinue() {
	printf("\nPress enter to continue");
	while (getchar() != '\n');
	return 1;
}
/**
 * @brief Handles input error by clearing the input buffer.
 *
 * This function is responsible for handling input errors by clearing the input buffer
 * until a newline character or EOF is encountered. It then prints an error message
 * indicating that the input is invalid and prompts the user to enter a number.
 *
 * @return Always returns 0.
 */
int handleInputError() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
	printf("Invalid input. Please enter a number.\n");
	return 0;
}
/**
 * @brief Gets user input from standard input.
 *
 * This function reads a line of input from standard input (stdin), attempts to parse
 * it as an integer, and returns the parsed integer value. If an error occurs during
 * input or parsing, appropriate error codes are returned.
 *
 * @return The integer input by the user, or error codes (-1 or -2) if an error occurs.
 */
int getInput() {
	char line[256];
	int choice, result;

	if (fgets(line, sizeof(line), stdin) == NULL) {
		return -1;
	}

	result = sscanf(line, "%d", &choice);
	if (result != 1) {
		return -2;
	}

	return choice;
}

//TOOLS


//PRINTMENU
/**
 * @brief Prints the main menu options.
 *
 * This function prints the main menu options for the Virtual Bookshelf Organizer
 * program, prompting the user to select an option by entering a corresponding number.
 *
 * @return Always returns 1.
 */
int printMainMenu() {
	printf("Welcome To Virtual Bookshelf Organizer\n\n");
	printf("1. Login\n");
	printf("2. Register\n");
	printf("3. Exit Program\n");
	printf("Please enter a number to select: ");
	return 1;
}


/**
 * @brief Prints the user operations menu.
 *
 * This function prints the user operations menu, providing options for managing
 * books, loans, and wishlists, and prompts the user to select an option by entering
 * a corresponding number.
 *
 * @return Always returns 1.
 */
int userMenu() {
	clearScreen();
	printf("Welcome to User Operations\n\n");
	printf("1. Book Cataloging\n");
	printf("2. Loan Management\n");
	printf("3. WishList Management\n");
	printf("4. Return to Main Menu\n");
	printf("Please enter a number to select: ");
	return 1;
}
/**
 * @brief Prints the book cataloging menu.
 *
 * This function prints the book cataloging menu, providing options for adding,
 * deleting, updating, and viewing books in the catalog, and prompts the user to
 * select an option by entering a corresponding number.
 *
 * @return Always returns 1.
 */
int bookCatalogingMenu() {
	clearScreen();
	printf("Welcome to Book Operations\n\n");
	printf("1. Add Book\n");
	printf("2. Delete Book\n");
	printf("3. Update Book\n");
	printf("4. View Catalog\n");
	printf("5. View Books by Price\n");
	printf("6. minCostArrangingBooks\n");
	printf("7. Minimum cost of arranging books\n");
	printf("8. Return User Operations\n");
	printf("Please enter a number to select: ");
	return 1;
}

/**
 * @brief Prints the loan management menu.
 *
 * This function prints the loan management menu, providing options for giving and
 * borrowing books, as well as showing borrowed and given books, and prompts the user
 * to select an option by entering a corresponding number.
 *
 * @return Always returns 1.
 */
int loanManagementMenu() {
	clearScreen();
	printf("Loan Management Menu\n\n");
	printf("1. Give Book\n");
	printf("2. Borrow Book\n");
	printf("3. Show borrowed books\n");
	printf("4. Show given books\n");
	printf("5. Show suggestions for books to borrow\n");
	printf("6. Return to User Operations Menu\n");
	printf("Please enter a number to select: ");
	return 1;
}

/**
 * @brief Prints the wishlist management menu.
 *
 * This function prints the wishlist management menu, providing options for adding,
 * deleting, and marking books as acquired in the wishlist, as well as viewing and
 * searching the wishlist, and prompts the user to select an option by entering a
 * corresponding number.
 *
 * @return Always returns 1.
 */
int wishListMenu() {
	clearScreen();
	printf("WishList Management Menu\n\n");
	printf("1. Add Book to Wishlist\n");
	printf("2. Delete Book from Wishlist\n");
	printf("3. Mark as Acquired\n");
	printf("4. View Wishlist\n");
	printf("5. Search Wishlist\n");
	printf("6. Return to User Operations Menu\n");
	printf("Please enter a number to select: ");
	return 1;
}

//PRINTMENU


//IDK
/**
 * @brief Gets a new unique user ID.
 *
 * This function determines a new unique user ID based on the existing user IDs
 * in the provided array of users. If the user count is zero, it returns 1. Otherwise,
 * it builds a max heap using the user IDs and returns the maximum ID incremented by 1.
 *
 * @param users An array of User structures containing existing user information.
 * @param userCount The number of users in the array.
 * @return A new unique user ID.
 */
int getNewUserId(User users[], int userCount) {
	if (userCount == 0)
		return 1;

	buildMaxHeap(users, userCount);

	int maxId = users[0].id;

	return maxId + 1;
}
/**
 * @brief Gets a new unique book ID.
 *
 * This function determines a new unique book ID based on the existing book IDs
 * loaded from the specified file. If no books are loaded or the file is empty, it
 * returns 1. Otherwise, it loads the books, sorts them by ID, and returns the maximum
 * ID incremented by 1.
 *
 * @param pathFileBooks The path to the file containing the book information.
 * @return A new unique book ID.
 */
int getNewBookId(const char* pathFileBooks) {
	Book* books;
	int count = loadBooks(pathFileBooks, &books);
	if (count == 0)
		return 1;

	randomizedQuickSortBookIds(books, 0, count - 1);

	int newId = books[count - 1].id + 1;
	free(books);
	return newId;
}
/**
 * @brief Saves book information to a file.
 *
 * This function saves the provided array of Book structures to the specified file.
 * If successful, it returns 1; otherwise, it returns 0.
 *
 * @param path The path to the file where book information will be saved.
 * @param books An array of Book structures containing book information.
 * @param count The number of books in the array.
 * @return 1 if successful, 0 otherwise.
 */
int saveBooks(const char* path, Book* books, int count) {
	FILE* file = fopen(path, "wb");
	if (file != NULL) {
		fwrite(books, sizeof(Book), count, file);
		fclose(file);
		return 1;
	}
}
/**
 * @brief Gets a new unique wishlist ID.
 *
 * This function determines a new unique wishlist ID based on the existing book IDs
 * loaded from the specified file. If no books are loaded or the file is empty, it
 * returns 1. Otherwise, it loads the books, sorts them by ID, and returns the maximum
 * ID incremented by 1.
 *
 * @param pathFileWishlist The path to the file containing the wishlist information.
 * @return A new unique wishlist ID.
 */
int getNewWishlistId(const char* pathFileWishlist) {
	Book* books;
	int count = loadBooks(pathFileWishlist, &books);
	if (count == 0)
		return 1;

	randomizedQuickSortBookIds(books, 0, count - 1);

	int newId = books[count - 1].id + 1;
	free(books);
	return newId;
}

//IDK


//Load
/**
 * @brief Loads books owned by a specific user from a file.
 *
 * This function loads books owned by a specific user from the specified file.
 * It reads book records from the file and filters out books owned by the given user.
 * The loaded books are stored in the dynamically allocated 'books' array.
 *
 * @param pathFileBooks The path to the file containing book information.
 * @param books A pointer to a pointer to Book structures where loaded books will be stored.
 * @param userId The ID of the user whose owned books are to be loaded.
 * @return The number of books owned by the user loaded from the file, or -1 if the file cannot be opened.
 */
int loadOwnedBooks(const char* pathFileBooks, Book** books, int userId) {
	FILE* file = fopen(pathFileBooks, "rb");
	if (!file) {
		printf("Failed to open file\n");
		return -1;
	}

	Book temp;
	int count = 0;
	while (fread(&temp, sizeof(Book), 1, file) == 1) {
		if (temp.owner.id == userId) {
			*books = (Book*)realloc(*books, (count + 1) * sizeof(Book));
			(*books)[count] = temp;
			count++;
		}
	}
	fclose(file);
	return count;
}
/**
 * @brief Loads user information from a file.
 *
 * This function loads user information from the specified file. It reads the number of
 * users first and then reads user records from the file. The loaded users are stored
 * in the dynamically allocated 'users' array.
 *
 * @param pathFileUsers The path to the file containing user information.
 * @param users A pointer to a pointer to User structures where loaded users will be stored.
 * @return The number of users loaded from the file, or 0 if the file cannot be opened.
 */
int loadUsers(const char* pathFileUsers, User** users) {
	FILE* file = fopen(pathFileUsers, "rb");
	if (!file) {
		*users = NULL;
		return 0;
	}

	int count;
	fread(&count, sizeof(int), 1, file);

	*users = (User*)malloc(sizeof(User) * count);
	fread(*users, sizeof(User), count, file);

	fclose(file);
	return count;
}

/**
 * @brief Loads books from a file.
 *
 * This function loads book information from the specified file. It reads book records
 * from the file and stores them in the dynamically allocated 'books' array.
 *
 * @param path The path to the file containing book information.
 * @param books A pointer to a pointer to Book structures where loaded books will be stored.
 * @return The number of books loaded from the file, or 0 if the file cannot be opened.
 */
int loadBooks(const char* path, Book** books) {
	FILE* file = fopen(path, "rb");
	if (file == NULL) return 0;

	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, 0, SEEK_SET);

	int count = size / sizeof(Book);
	*books = (Book*)malloc(size);

	fread(*books, sizeof(Book), count, file);
	fclose(file);

	return count;
}

/**
 * @brief Loads books owned by a specific user from a file.
 *
 * This function loads books owned by a specific user from the specified file.
 * It reads book records from the file and filters out books owned by the given user.
 * The loaded books are stored in the dynamically allocated 'filteredBooks' array.
 *
 * @param pathFileBooks The path to the file containing book information.
 * @param userId The ID of the user whose owned books are to be loaded.
 * @param filteredBooks A pointer to a pointer to Book structures where loaded books will be stored.
 * @return The number of books owned by the user loaded from the file, or -1 if the file cannot be opened.
 */
int loadBooksForUser(const char* pathFileBooks, int userId, Book** filteredBooks) {
	int size = 0;

	FILE* file = fopen(pathFileBooks, "rb");
	if (file == NULL) {
		return -1;
	}

	Book temp;
	while (fread(&temp, sizeof(Book), 1, file) == 1) {
		if (temp.owner.id == userId) {
			size++;
			*filteredBooks = (Book*)realloc(*filteredBooks, size * sizeof(Book));
			(*filteredBooks)[size - 1] = temp;
		}
	}

	fclose(file);
	return size;
}

