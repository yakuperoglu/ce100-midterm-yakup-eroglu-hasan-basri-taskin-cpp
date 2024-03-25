/**
 * @file main.cpp
 * @brief Program entry point and namespace declaration.
 */

#define _CRT_SECURE_NO_WARNINGS
#include "Bookshelforganizer.h"
#include <iostream>
using namespace std;

/**
 * @file main.cpp
 * @brief Main file containing the entry point of the program.
 */

 /**
  * @brief Main function of the program.
  * @details This function serves as the entry point of the program. It defines the relevant file paths
  *          and initiates the mainMenu function to start the main menu.
  *
  * @param[in] pathFileUsers Path to the file containing user information.
  * @param[in] pathFileBooks Path to the file containing book information.
  * @param[in] pathFileLendingHistories Path to the file containing lending histories.
  * @param[in] pathFileWishlist Path to the file containing wishlists.
  *
  * @return Returns 0 upon successful termination of the program.
  */
int main() {
	const char* pathFileBooks = "books.bin";
	const char* pathFileUsers = "users.bin";
	const char* pathFileWishlist = "wishlists.bin";
	const char* pathFileLendingHistories = "lendinghistories.bin";

	mainMenu(pathFileUsers, pathFileBooks, pathFileLendingHistories, pathFileWishlist);

	return 0;
}