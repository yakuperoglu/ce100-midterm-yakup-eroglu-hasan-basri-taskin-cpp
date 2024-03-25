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