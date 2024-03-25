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
