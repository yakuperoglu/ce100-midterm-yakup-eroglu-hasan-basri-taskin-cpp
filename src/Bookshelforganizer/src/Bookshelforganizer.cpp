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
#include "Bookshelforganizer.h"

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

/**
 * @brief Loads loaned histories from a file.
 *
 * This function loads loaned histories from the specified file. It reads loaned history
 * records from the file and stores them in the dynamically allocated 'histories' array.
 *
 * @param pathFileHistories The path to the file containing loaned histories.
 * @param histories A pointer to a pointer to LoanedHistory structures where loaded loaned histories will be stored.
 * @return The number of loaned histories loaded from the file, or 0 if the file cannot be opened or is empty.
 */
int loadLoanedHistories(const char* pathFileHistories, LoanedHistory** histories) {
	FILE* file = fopen(pathFileHistories, "rb+");
	if (!file) {
		file = fopen(pathFileHistories, "wb+");
	}

	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	if (fileSize == 0) {
		*histories = NULL;
		fclose(file);
		return 0;
	}

	rewind(file);
	int count = fileSize / sizeof(LoanedHistory);
	*histories = (LoanedHistory*)malloc(fileSize);

	fread(*histories, sizeof(LoanedHistory), count, file);
	fclose(file);

	return count;
}

/**
 * @brief Saves loaned histories to a file.
 *
 * This function saves loaned history records to the specified file.
 *
 * @param pathFileHistories The path to the file where loaned histories will be saved.
 * @param histories An array of LoanedHistory structures containing loaned history records.
 * @param count The number of loaned histories to save.
 * @return 1 if successful, 0 otherwise.
 */
int saveLoanedHistories(const char* pathFileHistories, LoanedHistory* histories, int count) {
	FILE* file = fopen(pathFileHistories, "wb");

	fwrite(histories, sizeof(LoanedHistory), count, file);
	fclose(file);

	return 1;
}

//Load

//Algorithms

//quick Sort
/**
 * @brief Swaps two Book structures.
 *
 * This function swaps the contents of two Book structures.
 *
 * @param a Pointer to the first Book structure.
 * @param b Pointer to the second Book structure.
 */
void swap(Book* a, Book* b) {
	Book temp = *a;
	a = b;
	*b = temp;
}
/**
 * @brief Partitions an array of books based on a pivot element.
 *
 * This function partitions an array of books based on a pivot element (the ID of
 * the last element in the array). It rearranges the elements of the array in such
 * a way that all elements smaller than the pivot are placed before it, and all
 * elements greater than or equal to the pivot are placed after it.
 *
 * @param arr The array of books to partition.
 * @param low The index of the first element of the array.
 * @param high The index of the last element of the array.
 * @return The index of the pivot element after partitioning.
 */
int partition(Book arr[], int low, int high) {
	int pivot = arr[high].id;
	int i = low - 1;

	for (int j = low; j <= high - 1; j++) {
		if (arr[j].id < pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}
/**
 * @brief Chooses a random pivot and partitions the array of books.
 *
 * This function chooses a random pivot element from the array of books and partitions
 * the array based on this pivot. It rearranges the elements of the array in such
 * a way that all elements smaller than the pivot are placed before it, and all
 * elements greater than or equal to the pivot are placed after it.
 *
 * @param arr The array of books to partition.
 * @param low The index of the first element of the array.
 * @param high The index of the last element of the array.
 * @return The index of the pivot element after partitioning.
 */
int randomPartition(Book arr[], int low, int high) {
	int n = high - low + 1;
	int pivot = rand() % n;
	swap(&arr[low + pivot], &arr[high]);
	return partition(arr, low, high);
}

/**
 * @brief Sorts an array of books using randomized quicksort.
 *
 * This function sorts an array of books using the randomized quicksort algorithm.
 * It first partitions the array using a random pivot element and then recursively
 * sorts the subarrays before and after the pivot.
 *
 * @param arr The array of books to sort.
 * @param low The index of the first element of the array.
 * @param high The index of the last element of the array.
 * @return Always returns 1.
 */
int randomizedQuickSortBookIds(Book arr[], int low, int high) {
	if (low < high) {
		int pi = randomPartition(arr, low, high);
		randomizedQuickSortBookIds(arr, low, pi - 1);
		randomizedQuickSortBookIds(arr, pi + 1, high);
	}
	return 1;
}
//quick Sort

//Longest Common Subsequence
/**
 * @brief Finds the Longest Common Subsequence (LCS) between two strings.
 *
 * This function calculates the length of the LCS between two strings using dynamic programming.
 * It returns the ratio of the LCS length to the length of the shorter string.
 *
 * @param s1 The first string.
 * @param s2 The second string.
 * @return The ratio of the LCS length to the length of the shorter string.
 */
double findLCS(const char* s1, const char* s2) {
	int m = strlen(s1);
	int n = strlen(s2);

	//Creating 2D array with dynamic memory allocation bc c++ does not support array resizing with non-constant values.
	int** L = (int**)malloc((m + 1) * sizeof(int*));
	for (int i = 0; i <= m; i++) {
		L[i] = (int*)malloc((n + 1) * sizeof(int));
	}

	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			if (i == 0 || j == 0)
				L[i][j] = 0;
			else if (s1[i - 1] == s2[j - 1])
				L[i][j] = L[i - 1][j - 1] + 1;
			else
				L[i][j] = (L[i - 1][j] > L[i][j - 1]) ? L[i - 1][j] : L[i][j - 1];
		}
	}

	int len = L[m][n];

	for (int i = 0; i <= m; i++) {
		free(L[i]);
	}
	free(L);

	return len / (double)(m < n ? m : n);
}
//Longest Common Subsequence

//Heap Sort
/**
 * @brief Heapifies the array of users.
 *
 * This function heapifies the array of users based on their IDs.
 *
 * @param users The array of users to be heapified.
 * @param n The number of users in the array.
 * @param i The index of the current element being heapified.
 */
void heapify(User users[], int n, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && users[left].id > users[largest].id)
		largest = left;

	if (right < n && users[right].id > users[largest].id)
		largest = right;

	if (largest != i) {
		User swap = users[i];
		users[i] = users[largest];
		users[largest] = swap;

		heapify(users, n, largest);
	}
}
/**
 * @brief Builds a max heap from the array of users.
 *
 * This function builds a max heap from the array of users based on their IDs.
 *
 * @param users The array of users to build the max heap from.
 * @param n The number of users in the array.
 */
void buildMaxHeap(User users[], int n) {
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(users, n, i);
}
//heap Sort

//Knapsack Implementation with Dynamic Programming
/**
 * @brief Finds the maximum of two integers.
 *
 * This function returns the maximum of two integers.
 *
 * @param a The first integer.
 * @param b The second integer.
 * @return The maximum of the two integers.
 */
int max(int a, int b) {
	return (a > b) ? a : b;
}
//Knapsack Implementation with Dynamic Programming

//Binary Search
/**
 * @brief Performs binary search to find a book by title in a sorted array of books.
 *
 * This function performs binary search to find a book by title in a sorted array of books.
 * It returns the index of the book if found, otherwise, it returns -1.
 *
 * @param books The array of books to search in.
 * @param low The lowest index of the search range.
 * @param high The highest index of the search range.
 * @param targetTitle The title of the book to search for.
 * @return The index of the book if found, otherwise -1.
 */
int binarySearchBookByTitle(Book books[], int low, int high, const char* targetTitle) {
	while (low <= high) {
		int mid = low + (high - low) / 2;
		int res = strcmp(targetTitle, books[mid].title);

		// Check if targetTitle is present at mid
		if (res == 0)
			return mid;

		// If targetTitle greater, ignore left half
		if (res > 0) low = mid + 1;

		// If targetTitle is smaller, ignore right half
		else high =
			mid - 1;
	}

	// If we reach here, then the element was not present
	return -1;
}
//Binary Search

/**
 * @brief Computes the minimum cost of arranging books using matrix chain multiplication.
 *
 * This function computes the minimum cost of arranging books using matrix chain multiplication.
 * It constructs a cost matrix, performs matrix chain multiplication, and returns the minimum cost.
 *
 * @param p An array representing the dimensions of the matrices.
 * @param n The number of matrices.
 * @return The minimum cost of arranging books.
 */
int MatrixChainOrder(int p[], int n) {
	int** m = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		m[i] = (int*)malloc(n * sizeof(int));
	}

	for (int i = 1; i < n; i++) {
		m[i][i] = 0;
	}

	for (int L = 2; L < n; L++) {
		for (int i = 1; i < n - L + 1; i++) {
			int j = i + L - 1;
			m[i][j] = INT_MAX;
			for (int k = i; k <= j - 1; k++) {
				int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (q < m[i][j]) {
					m[i][j] = q;
				}
			}
		}
	}

	int result = m[1][n - 1];

	for (int i = 0; i < n; i++) {
		free(m[i]);
	}
	free(m);

	return result;
}
/**
 * @brief Main function to calculate the minimum cost of arranging books.
 *
 * This function is the main entry point to calculate the minimum cost of arranging books.
 * It loads book information from a file, constructs an array of costs, computes the minimum cost
 * using MatrixChainOrder function, and prints the result.
 *
 * @param pathFileBooks The path to the file containing book information.
 * @return 0 if successful, otherwise an error code.
 */
int mainMatrix(const char* pathFileBooks) {
	Book* books = NULL;
	int bookCount = loadBooks(pathFileBooks, &books);

	if (bookCount <= 0) {
		printf("No books found.");
		enterToContinue();
		return 0;
	}

	int* costs = (int*)malloc((bookCount + 1) * sizeof(int));
	if (!costs) { printf("Memory allocation failed for costs array."); free(books); enterToContinue(); return 0; }

	for (int i = 0; i < bookCount; i++) {
		costs[i] = books[i].cost;
	}

	int result = MatrixChainOrder(costs, bookCount + 1);

	printf("Minimum number of multiplications is %d\n", result);

	free(costs);
	free(books);
	enterToContinue();

	return 0;
}
/**
 * @brief Calls the main function to calculate the minimum cost of arranging books.
 *
 * This function calls the main function `mainMatrix()` to calculate the minimum cost of arranging books.
 *
 * @param pathFileBooks The path to the file containing book information.
 * @return Always returns 0.
 */
int callMainMatrix(const char* pathFileBooks) {

	mainMatrix(pathFileBooks);
	return 0;
}
/**
 * @brief Finds the minimum of two integers.
 *
 * This function returns the minimum of two integers.
 *
 * @param a The first integer.
 * @param b The second integer.
 * @return The minimum of the two integers.
 */
int min(int a, int b) {
	return a < b ? a : b;
}

/**
 * @brief Computes the minimum cost of arranging books using dynamic programming.
 *
 * This function computes the minimum cost of arranging books using dynamic programming.
 * It loads owned books from a file, constructs a cost matrix, performs matrix chain multiplication,
 * reconstructs the optimal ordering, and prints the minimum cost.
 *
 * @param pathToBooksFile The path to the file containing book information.
 * @return 1 if successful, 0 otherwise.
 */
int minCostArrangingBooks(const char* pathToBooksFile) {
	clearScreen();

	// Load ownedBooks from file
	// Assuming loadOwnedBooks function returns an array of Book structs
	// Implement this function accordingly

	Book* ownedBooks = NULL;
	int numBooks = loadOwnedBooks(pathToBooksFile, &ownedBooks, loggedUser.id);


	Book* books = (Book*)malloc(numBooks * sizeof(Book));
	// Assuming ownedBooks array is copied to books array

	int** costMatrix = (int**)malloc(numBooks * sizeof(int*));
	for (int i = 0; i < numBooks; i++) {
		costMatrix[i] = (int*)malloc(numBooks * sizeof(int));
	}

	// Fill cost matrix with maximum values
	for (int i = 0; i < numBooks; i++) {
		for (int j = 0; j < numBooks; j++) {
			costMatrix[i][j] = INT_MAX;
		}
	}

	// Fill diagonal with 0 as single book multiplication cost is 0
	for (int i = 0; i < numBooks; i++) {
		costMatrix[i][i] = 0;
	}

	// Perform Matrix Chain Multiplication Order Dynamic Programming
	for (int chainLen = 2; chainLen < numBooks; chainLen++) {
		for (int i = 0; i < numBooks - chainLen + 1; i++) {
			int j = i + chainLen - 1;
			for (int k = i; k <= j - 1; k++) {
				int cost = costMatrix[i][k] + costMatrix[k + 1][j]
					+ books[i - 1].cost * books[k].cost * books[j].cost;
				costMatrix[i][j] = min(costMatrix[i][j], cost);
			}
		}
	}

	// Reconstruct optimal ordering
	// This part depends on how you want to handle the ordering information

	// For simplicity, let's just print the minimum cost
	printf("Minimum cost of arranging books: %d\n", costMatrix[0][numBooks - 1]);

	enterToContinue();

	// Free dynamically allocated memory
	for (int i = 0; i < numBooks; i++) {
		free(costMatrix[i]);
	}
	free(costMatrix);
	free(books);

	return 1;
}

//Algorithms


//BookCataloging
/**
 * @brief Allows users to perform book cataloging operations.
 *
 * This function allows users to perform various book cataloging operations such as adding, deleting,
 * updating, and viewing books in the catalog. Users can select operations from a menu until they choose
 * to return to the main menu.
 *
 * @param pathFileBooks The path to the file containing book information.
 * @return Always returns 0.
 */
int bookCataloging(const char* pathFileBooks) {
	int choice;

	while (1) {
		bookCatalogingMenu();
		choice = getInput();

		if (choice == -2) {
			handleInputError();
			enterToContinue();
			continue;
		}

		switch (choice) {
		case 1:
			addBookMenu(pathFileBooks);
			break;
		case 2:
			deleteBookMenu(pathFileBooks);
			break;
		case 3:
			updateBookMenu(pathFileBooks);
			break;
		case 4:
			viewCatalog(pathFileBooks);
			break;
		case 5:
			selectBooksByPriceMenu(pathFileBooks);
			break;
		case 6:
			callMainMatrix(pathFileBooks);
			break;
		case 7:
			minCostArrangingBooks(pathFileBooks);
			break;
		case 8:
			return 0;
		default:
			clearScreen();
			printf("Invalid choice. Please try again.\n");
			enterToContinue();
			break;
		}
	}
}
/**
 * @brief Adds a new book to the book catalog.
 *
 * This function adds a new book to the book catalog file.
 *
 * @param newBook Pointer to the new book to be added.
 * @param pathFileBooks The path to the file containing book information.
 * @return 1 if the book is successfully added, 0 otherwise.
 */
int addBook(const Book* newBook, const char* pathFileBooks) {
	FILE* file = fopen(pathFileBooks, "ab");
	if (!file) { return 0; }
	fwrite(newBook, sizeof(Book), 1, file);
	fclose(file);
	return 1;
}
/**
 * @brief Deletes a book from the book catalog.
 *
 * This function deletes a book with the specified ID from the book catalog file.
 *
 * @param bookId The ID of the book to be deleted.
 * @param pathFileBooks The path to the file containing book information.
 * @param books Array of books.
 * @param bookCount The number of books in the array.
 * @return True if the book is successfully deleted, false otherwise.
 */
bool deleteBook(int bookId, const char* pathFileBooks, Book* books, int bookCount) {
	bool isFound = false;
	int i;
	for (i = 0; i < bookCount; ++i) {
		if (books[i].id == bookId) {
			isFound = true;
			for (int j = i; j < bookCount - 1; ++j) { books[j] = books[j + 1]; }
			bookCount--;
			break;
		}
	}

	if (isFound) {
		saveBooks(pathFileBooks, books, bookCount);
		printf("Book with ID '%d' has been deleted successfully.\n", bookId);
	}
	else {
		printf("There is no book with ID '%d'.\n", bookId);
	}

	return isFound;
}
/**
 * @brief Updates information of a book in the book catalog.
 *
 * This function updates the information of a book with the specified ID in the book catalog file.
 *
 * @param books Array of books.
 * @param bookCount The number of books in the array.
 * @param bookId The ID of the book to be updated.
 * @param title The new title of the book.
 * @param author The new author of the book.
 * @param genre The new genre of the book.
 * @param cost The new cost of the book.
 * @param pathFileBooks The path to the file containing book information.
 * @return True if the book information is successfully updated, false otherwise.
 */
bool updateBook(Book* books, int bookCount, int bookId, const char* title, const char* author, const char* genre, int cost, const char* pathFileBooks) {
	bool isFound = false;
	for (int i = 0; i < bookCount; ++i) {
		if (books[i].id == bookId) {
			strncpy(books[i].title, title, sizeof(books[i].title) - 1);
			strncpy(books[i].author, author, sizeof(books[i].author) - 1);
			strncpy(books[i].genre, genre, sizeof(books[i].genre) - 1);
			books[i].cost = cost;
			books[i].title[sizeof(books[i].title) - 1] = '\0';
			books[i].author[sizeof(books[i].author) - 1] = '\0';
			books[i].genre[sizeof(books[i].genre) - 1] = '\0';
			isFound = true;
			break;
		}
	}
	if (isFound) {
		return saveBooks(pathFileBooks, books, bookCount);
	}
	else {
		return false;
	}
}
/**
 * @brief Displays the catalog of owned books.
 *
 * This function displays the catalog of books owned by the current user.
 *
 * @param filePathBooks The path to the file containing book information.
 * @return Always returns 1.
 */
int viewCatalog(const char* filePathBooks) {
	clearScreen();
	Book* books = NULL;
	int bookCount = loadOwnedBooks(filePathBooks, &books, loggedUser.id);

	if (bookCount <= 0) {
		printf("No books owned.\n");
	}
	else {
		for (int i = 0; i < bookCount; i++) {
			printf("ID: %d, Title: %s, Author: %s, Genre: %s, Cost: %d\n",
				books[i].id, books[i].title, books[i].author, books[i].genre, books[i].cost);
		}
	}

	enterToContinue();
	free(books);
	return 1;
}
/**
 * @brief Displays the catalog of owned books without clearing the screen.
 *
 * This function displays the catalog of books owned by the current user without clearing the screen.
 *
 * @param filePathBooks The path to the file containing book information.
 * @return Always returns 1.
 */
int viewCatalogForFunc(const char* filePathBooks) {
	clearScreen();
	Book* books = NULL;
	int bookCount = loadOwnedBooks(filePathBooks, &books, loggedUser.id);

	if (bookCount <= 0) {
		printf("No books owned.\n");
	}
	else {
		for (int i = 0; i < bookCount; i++) {
			printf("ID: %d, Title: %s, Author: %s, Genre: %s, Cost: %d\n",
				books[i].id, books[i].title, books[i].author, books[i].genre, books[i].cost);
		}
	}

	free(books);
	return 1;
}
/**
 * @brief Displays the menu for adding a new book.
 *
 * This function displays a menu for the user to input information about a new book to be added to the catalog.
 * After entering the book details, it adds the book to the catalog file.
 *
 * @param pathFileBooks The path to the file containing book information.
 * @return 1 if the book is successfully added, 0 otherwise.
 */
int addBookMenu(const char* pathFileBooks) {
	clearScreen();
	Book newBook;

	printf("Enter book name: ");
	fgets(newBook.title, sizeof(newBook.title), stdin);
	newBook.title[strcspn(newBook.title, "\n")] = 0;

	printf("Enter author: ");
	fgets(newBook.author, sizeof(newBook.author), stdin);
	newBook.author[strcspn(newBook.author, "\n")] = 0;

	printf("Enter Genre: ");
	fgets(newBook.genre, sizeof(newBook.genre), stdin);
	newBook.genre[strcspn(newBook.genre, "\n")] = 0;

	printf("Enter Cost: ");
	int cost = getInput();
	if (cost < 0) {
		printf("Invalid input for cost.\n");
		enterToContinue();
		return 0;
	}
	newBook.cost = cost;

	newBook.owner = loggedUser;
	newBook.isBorrowed = 0;
	newBook.id = getNewBookId(pathFileBooks);

	if (!addBook(&newBook, pathFileBooks)) { printf("Failed to add book.\n"); enterToContinue(); return 0; }

	printf("Book added successfully.\n");
	enterToContinue();
	return 1;
}
/**
 * @brief Displays the menu for deleting a book.
 *
 * This function displays a menu for the user to select a book to delete from the catalog.
 * After selecting the book, it deletes the book from the catalog file.
 *
 * @param pathFileBooks The path to the file containing book information.
 * @return True if the book is successfully deleted, false otherwise.
 */
bool deleteBookMenu(const char* pathFileBooks) {
	clearScreen();
	Book* books = NULL;
	int bookCount = loadBooks(pathFileBooks, &books);
	if (bookCount == 0) { printf("No books available to delete.\n"); enterToContinue(); return false; }

	viewCatalogForFunc(pathFileBooks);
	printf("Enter the ID of the book to delete: ");
	int bookId = getInput();

	if (bookId < 0) { handleInputError(); enterToContinue(); return false; }

	bool result = deleteBook(bookId, pathFileBooks, books, bookCount);
	enterToContinue();
	if (books != NULL) {
		free(books);
	}
	return result;
}
/**
 * @brief Displays the menu for updating a book.
 *
 * This function displays a menu for the user to select a book to update from the catalog.
 * After selecting the book, it prompts the user to enter new details for the book and updates the information.
 *
 * @param pathFileBooks The path to the file containing book information.
 * @return True if the book information is successfully updated, false otherwise.
 */
bool updateBookMenu(const char* pathFileBooks) {
	clearScreen();
	Book* books = NULL;
	int bookCount = loadBooks(pathFileBooks, &books);

	if (bookCount <= 0) {
		printf("No books available.\n");
		enterToContinue();
		return false;
	}

	viewCatalogForFunc(pathFileBooks);
	printf("Enter the ID of the book to update: ");
	int bookId = getInput();

	if (bookId < 0) {
		handleInputError();
		enterToContinue();
		return false;
	}

	char title[100], author[100], genre[100];
	int cost;

	printf("Enter the new name for the book: ");
	fgets(title, sizeof(title), stdin); title[strcspn(title, "\n")] = 0;
	printf("Enter author name: ");
	fgets(author, sizeof(author), stdin); author[strcspn(author, "\n")] = 0;
	printf("Enter genre: ");
	fgets(genre, sizeof(genre), stdin); genre[strcspn(genre, "\n")] = 0;
	printf("Enter Cost: ");
	cost = getInput();

	if (cost < 0) {
		handleInputError();
		enterToContinue();
		return false;
	}

	bool updateResult = updateBook(books, bookCount, bookId, title, author, genre, cost, pathFileBooks);
	if (updateResult) {
		printf("Book with ID '%d' has been updated successfully.\n", bookId);
	}
	else {
		printf("Failed to update book. No book found with ID '%d'.\n", bookId);
	}

	enterToContinue();
	return updateResult;
}
/**
 * @brief Displays the menu for selecting books within a budget.
 *
 * This function displays a menu for the user to enter a budget.
 * It then selects books from the catalog file whose costs do not exceed the budget.
 *
 * @param pathFileBooks The path to the file containing book information.
 * @return 1 if books are successfully selected within the budget, 0 otherwise.
 */
int selectBooksByPriceMenu(const char* pathFileBooks) {
	clearScreen();
	int budget;

	printf("Enter your budget: ");
	budget = getInput();
	if (budget < 0) {
		printf("Invalid input for budget.\n");
		enterToContinue();
		return 0;
	}

	Book* books = NULL;
	int bookCount = loadBooks(pathFileBooks, &books);
	if (bookCount <= 0) {
		printf("No books found.\n");
		enterToContinue();
		return 0;
	}

	int** dp = (int**)malloc((bookCount + 1) * sizeof(int*));
	for (int i = 0; i <= bookCount; i++) {
		dp[i] = (int*)malloc((budget + 1) * sizeof(int));
		memset(dp[i], 0, (budget + 1) * sizeof(int));
	}

	for (int i = 0; i <= bookCount; i++) {
		for (int w = 0; w <= budget; w++) {
			if (i == 0 || w == 0)
				dp[i][w] = 0;
			else if (books[i - 1].cost <= w)
				dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - books[i - 1].cost] + 1);
			else
				dp[i][w] = dp[i - 1][w];
		}
	}

	int w = budget;
	printf("Selected Books within your budget:\n");
	for (int i = bookCount; i > 0 && w > 0; i--) {
		if (dp[i][w] != dp[i - 1][w]) {
			printf("ID: %d, Title: %s, Author: %s, Genre: %s, Cost: %d\n",
				books[i - 1].id, books[i - 1].title, books[i - 1].author, books[i - 1].genre, books[i - 1].cost);
			w -= books[i - 1].cost;
		}
	}

	for (int i = 0; i <= bookCount; i++) {
		free(dp[i]);
	}
	free(dp);
	free(books);
	enterToContinue();
	return 1;
}
/**
 * @brief Calculates the minimum cost for multiplying all book costs matrices.
 *
 * This function calculates the minimum cost required for multiplying all book costs matrices using dynamic programming.
 *
 * @param pathFileBooks The path to the file containing book information.
 * @return 1 if the minimum cost is successfully calculated, 0 otherwise.
 */
int calculateBookCosts(const char* pathFileBooks) {
	Book* books = NULL;
	int bookCount = loadBooks(pathFileBooks, &books);
	if (bookCount <= 0) {
		printf("No books found.\n");
		return 0;
	}

	int* costs = (int*)malloc((bookCount + 1) * sizeof(int));
	costs[0] = 0;
	for (int i = 0; i < bookCount; i++) {
		costs[i + 1] = books[i].cost;
	}

	int minCost = MatrixChainOrder(costs, bookCount + 1);
	printf("Minimum cost for multiplying all book costs matrices is: %d\n", minCost);

	free(costs);
	free(books);
	return 1;
}

/**
 * @brief Displays the menu for calculating the minimum cost for multiplying all book costs matrices.
 *
 * This function displays a menu for the user to calculate the minimum cost required for multiplying all book costs matrices.
 *
 * @param pathFileBooks The path to the file containing book information.
 * @return Always returns 0.
 */
int calculateBookCostsMenu(const char* pathFileBooks) {
	calculateBookCosts(pathFileBooks);
	enterToContinue();
	return 0;
}

//BookCataloging


//LoanManagement
/**
 * @brief Manages book loan operations.
 *
 * This function displays a menu for managing book loan operations such as borrowing, returning, and viewing borrowed books.
 * It prompts the user to select an action and performs the corresponding operation.
 *
 * @param pathFileBooks The path to the file containing book information.
 * @param pathFileHistories The path to the file containing loan histories.
 * @return Always returns 0.
 */
int loanManagement(const char* pathFileBooks, const char* pathFileHistories) {
	int choice;

	while (1) {
		loanManagementMenu();
		choice = getInput();

		if (choice == -2) {
			handleInputError();
			enterToContinue();
			continue;
		}

		switch (choice) {
		case 1:
			giveBackBookMenu(pathFileBooks, pathFileHistories);
			break;
		case 2:
			borrowBookMenu(pathFileBooks, pathFileHistories);
			break;
		case 3:
			viewBorrowedBooks(pathFileHistories);
			break;
		case 4:
			viewGivenBooks(pathFileHistories);
			break;
		case 5:
			suggestBooksToBorrow(pathFileBooks);
			break;
		case 6:
			return 0;
		default:
			printf("Invalid choice. Please try again.\n");
			enterToContinue();
			break;
		}
	}
}

/**
 * @brief Borrows a book.
 *
 * This function borrows a book by updating its status in the catalog and adding a loan history entry.
 *
 * @param bookId The ID of the book to borrow.
 * @param pathFileBooks The path to the file containing book information.
 * @param pathFileHistories The path to the file containing loan histories.
 * @return 1 if the book is successfully borrowed, 0 otherwise.
 */
int borrowBook(int bookId, const char* pathFileBooks, const char* pathFileHistories) {
	Book* books = NULL;
	int bookCount = loadBooks(pathFileBooks, &books);
	Book releatedBook;
	int found = 0;

	for (int i = 0; i < bookCount; i++) {
		if (books[i].id == bookId && books[i].isBorrowed == 0 && books[i].owner.id != loggedUser.id) {
			books[i].isBorrowed = 1;
			releatedBook = books[i];
			found = 1;
			break;
		}
	}

	if (!found) {
		printf("Book not found, already borrowed, or you are trying to borrow your own book.\n");
		free(books);
		return 0;
	}

	if (!saveBooks(pathFileBooks, books, bookCount)) { printf("Error updating book information.\n"); free(books); return 0; }

	LoanedHistory* histories = NULL;
	int historyCount = loadLoanedHistories(pathFileHistories, &histories);

	LoanedHistory newHistory;
	newHistory.bookId = bookId;
	newHistory.bookOwnerId = releatedBook.owner.id;
	newHistory.debtorUserId = loggedUser.id;
	newHistory.isApproved = 1;
	newHistory.hasGivenBack = 0;

	// Fixed size arrays cannot be cast directly because they are not a pointer type.
	// Therefore, we use the strcpy function to copy strings.
	strcpy(newHistory.bookName, releatedBook.title);
	strcpy(newHistory.bookOwnerName, releatedBook.owner.name);
	strcpy(newHistory.debtorUserName, loggedUser.name);


	histories = (LoanedHistory*)realloc(histories, (historyCount + 1) * sizeof(LoanedHistory));
	histories[historyCount] = newHistory;
	historyCount++;

	if (!saveLoanedHistories(pathFileHistories, histories, historyCount)) { printf("Failed to save the loan history.\n"); free(histories); free(books); return 0; }

	free(histories);
	free(books);
	return 1;
}

/**
 * @brief Gives back a borrowed book.
 *
 * This function marks a borrowed book as returned in the loan history and updates its status in the catalog.
 *
 * @param bookId The ID of the book to return.
 * @param pathFileBooks The path to the file containing book information.
 * @param pathFileHistories The path to the file containing loan histories.
 * @return 1 if the book is successfully returned, 0 otherwise.
 */
int giveBackBook(int bookId, const char* pathFileBooks, const char* pathFileHistories) {
	LoanedHistory* histories = NULL;
	int historyCount = loadLoanedHistories(pathFileHistories, &histories);
	int historyUpdated = 0;

	for (int i = 0; i < historyCount; i++) {
		if (histories[i].bookId == bookId && histories[i].debtorUserId == loggedUser.id && histories[i].hasGivenBack == 0) {
			histories[i].hasGivenBack = 1;
			historyUpdated = 1;
			break;
		}
	}

	if (!historyUpdated) {
		printf("This book was not borrowed by you or it has already been returned.\n");
		free(histories);
		return 0;
	}

	if (!saveLoanedHistories(pathFileHistories, histories, historyCount)) { printf("Failed to update the loan history.\n"); free(histories); return 0; }

	Book* books = NULL;
	int bookCount = loadBooks(pathFileBooks, &books);
	for (int i = 0; i < bookCount; i++) {
		if (books[i].id == bookId) {
			books[i].isBorrowed = 0;
			break;
		}
	}
	if (!saveBooks(pathFileBooks, books, bookCount)) { printf("Failed to update book information.\n"); free(histories); free(books); return 0; }

	free(histories);
	free(books);
	return 1;
}

/**
 * @brief Displays the menu for borrowing a book.
 *
 * This function displays a menu for the user to select a book to borrow from the available options.
 * It then borrows the selected book and updates the loan history.
 *
 * @param pathFileBooks The path to the file containing book information.
 * @param pathFileHistories The path to the file containing loan histories.
 * @return 1 if the book is successfully borrowed, 0 otherwise.
 */
int borrowBookMenu(const char* pathFileBooks, const char* pathFileHistories) {
	clearScreen();
	printf("Available Books to Borrow (excluding your own books):\n");

	Book* books = NULL;
	int bookCount = loadBooks(pathFileBooks, &books);
	if (bookCount > 0) {
		int availableCount = 0;
		for (int i = 0; i < bookCount; i++) {
			if (books[i].isBorrowed == 0 && books[i].owner.id != loggedUser.id) {
				printf("ID: %d Title: %s Author: %s Genre: %s\n", books[i].id, books[i].title, books[i].author, books[i].genre);
				availableCount++;
			}
		}
		if (availableCount == 0) {
			printf("No available books to borrow.\n");
			enterToContinue();
			free(books);
			return 0;
		}
	}
	else {
		printf("No books found.\n");
		enterToContinue();
		free(books);
		return 0;
	}

	printf("\nEnter the ID of the Book to Borrow: ");
	int bookId = getInput();

	if (bookId == -1 || bookId == -2) {
		handleInputError();
		enterToContinue();
		free(books);
		return 0;
	}

	if (!borrowBook(bookId, pathFileBooks, pathFileHistories)) { printf("An error occurred while borrowing the book.\n"); }
	else {
		printf("The book has been successfully borrowed.\n");
	}

	enterToContinue();
	free(books);
	return 1;
}

/**
 * @brief Displays the menu for giving back a borrowed book.
 *
 * This function displays a menu for the user to select a borrowed book to return.
 * It then marks the selected book as returned in the loan history and updates the book status.
 *
 * @param pathFileBooks The path to the file containing book information.
 * @param pathFileHistories The path to the file containing loan histories.
 * @return 1 if the book is successfully returned, 0 otherwise.
 */
int giveBackBookMenu(const char* pathFileBooks, const char* pathFileHistories) {
	clearScreen();
	printf("Books You Have Borrowed:\n");

	LoanedHistory* histories = NULL;
	int historyCount = loadLoanedHistories(pathFileHistories, &histories);

	Book* books = NULL;
	int bookCount = loadBooks(pathFileBooks, &books);

	int borrowedBooksDisplayed = 0;
	for (int i = 0; i < historyCount; i++) {
		if (histories[i].debtorUserId == loggedUser.id && histories[i].hasGivenBack == 0) {
			for (int j = 0; j < bookCount; j++) {
				if (books[j].id == histories[i].bookId) {
					printf("ID: %d Title: %s Author: %s Genre: %s\n", books[j].id, books[j].title, books[j].author, books[j].genre);
					borrowedBooksDisplayed++;
					break;
				}
			}
		}
	}

	if (borrowedBooksDisplayed == 0) {
		printf("You have not borrowed any books.\n");
	}
	else {
		printf("\nEnter the ID of the Book to Return: ");
		int bookId = getInput();

		if (bookId < 0) {
			handleInputError();
			free(histories);
			free(books);
			enterToContinue();
			return 0;
		}

		if (!giveBackBook(bookId, pathFileBooks, pathFileHistories)) {
			printf("An error occurred while returning the book.\n");
		}
		else { printf("The book has been successfully returned.\n"); }
	}

	free(histories);
	free(books);
	enterToContinue();
	return 1;
}

/**
 * @brief Displays the borrowed books of the current user.
 *
 * This function displays the borrowed books of the current user by reading loan histories.
 *
 * @param pathFileHistories The path to the file containing loan histories.
 * @return Always returns 1.
 */
int viewBorrowedBooks(const char* pathFileHistories) {
	clearScreen();
	writeBorrowedBooksToConsole(pathFileHistories);
	enterToContinue();
	return 1;
}
/**
 * @brief Displays the books given by the user to others.
 *
 * This function displays the books given by the user to others by reading loan histories.
 *
 * @param pathFileHistories The path to the file containing loan histories.
 * @return Always returns 1.
 */
int viewGivenBooks(const char* pathFileHistories) {
	clearScreen();
	writeGivenBooksToConsole(pathFileHistories);
	enterToContinue();
	return 1;
}
/**
 * @brief Writes the borrowed books of the current user to the console.
 *
 * This function retrieves loan histories, filters borrowed books of the current user, and prints them to the console.
 *
 * @param pathFileHistories The path to the file containing loan histories.
 * @return 1 if the user has borrowed books, 0 otherwise.
 */
int writeBorrowedBooksToConsole(const char* pathFileHistories) {
	LoanedHistory* histories = NULL;
	int count = loadLoanedHistories(pathFileHistories, &histories);
	int hasBorrowedBooks = 0;

	for (int i = 0; i < count; i++) {
		if (histories[i].debtorUserId == loggedUser.id && !histories[i].hasGivenBack) {
			printf("Book ID: %d, Book Name: %s, Owner Name : %s\n",
				histories[i].bookId, histories[i].bookName, histories[i].bookOwnerName);
			hasBorrowedBooks = 1;
		}
	}

	if (!hasBorrowedBooks) {
		printf("You didn't borrowed any books\n");
	}

	free(histories);
	return hasBorrowedBooks;
}
/**
 * @brief Writes the given books of the user to the console.
 *
 * This function retrieves loan histories, filters books given by the user, and prints them to the console.
 *
 * @param pathFileHistories The path to the file containing loan histories.
 * @return 1 if the user has given books, 0 otherwise.
 */
int writeGivenBooksToConsole(const char* pathFileHistories) {
	LoanedHistory* histories = NULL;
	int count = loadLoanedHistories(pathFileHistories, &histories);
	int hasGivenBooks = 0;

	for (int i = 0; i < count; i++) {
		if (histories[i].bookOwnerId == loggedUser.id && histories[i].hasGivenBack == 0) {
			printf("Book ID: %d, Book Name: %s, Debtor Name Surname: %s\n",
				histories[i].bookId, histories[i].bookName, histories[i].debtorUserName);
			hasGivenBooks = 1;
		}
	}

	if (!hasGivenBooks) {
		printf("You haven't given any books.\n");
	}

	free(histories);
	return hasGivenBooks;
}
/**
 * @brief Suggests books for the user to borrow.
 *
 * This function suggests books for the user to borrow based on the titles of the books they already own.
 *
 * @param pathFileBooks The path to the file containing book information.
 * @return The number of suggested books.
 */
int suggestBooksToBorrow(const char* pathFileBooks) {
	Book* books = NULL, * userBooks = NULL, * suggestedBooks = NULL;
	int booksCount = loadBooks(pathFileBooks, &books);
	int userBooksCount = loadBooksForUser(pathFileBooks, loggedUser.id, &userBooks);
	int suggestedCount = 0;

	for (int i = 0; i < booksCount; ++i) {
		bool isOwnedByUser = false;
		for (int j = 0; j < userBooksCount; ++j) {
			if (books[i].id == userBooks[j].id) {
				isOwnedByUser = true;
				break;
			}
		}

		if (!isOwnedByUser && !books[i].isBorrowed) {
			for (int j = 0; j < userBooksCount; ++j) {
				if (findLCS(books[i].title, userBooks[j].title) > 0.000001) {
					suggestedBooks = (Book*)realloc(suggestedBooks, (suggestedCount + 1) * sizeof(Book));
					suggestedBooks[suggestedCount++] = books[i];
					break;
				}
			}
		}
	}

	printf("Suggested Books:\n");
	for (int i = 0; i < suggestedCount; ++i) {
		printf("ID: %d, Title: %s, Author: %s, Genre: %s\n",
			suggestedBooks[i].id, suggestedBooks[i].title, suggestedBooks[i].author, suggestedBooks[i].genre);
	}
	enterToContinue();

	free(books);
	free(userBooks);
	free(suggestedBooks);

	return suggestedCount;
}
//Wishlist
/**
 * @brief Deletes a book from the wishlist.
 *
 * This function deletes a book from the wishlist by its ID.
 *
 * @param bookId The ID of the book to delete.
 * @param pathFileWishlist The path to the wishlist file.
 * @param books An array of books in the wishlist.
 * @param bookCount The number of books in the wishlist.
 * @return true if the book is successfully deleted, false otherwise.
 */
bool deleteBookToWishlist(int bookId, const char* pathFileWishlist, Book* books, int bookCount) {
	bool isFound = false;
	int i;
	for (i = 0; i < bookCount; ++i) {
		if (books[i].id == bookId) {
			isFound = true;
			for (int j = i; j < bookCount - 1; ++j) { books[j] = books[j + 1]; }
			bookCount--;
			break;
		}
	}

	if (isFound) {
		saveBooks(pathFileWishlist, books, bookCount);
		printf("Book with ID '%d' has been deleted successfully.\n", bookId);
	}
	else {
		printf("There is no book with ID '%d'.\n", bookId);
	}

	return isFound;
}
/**
 * @brief Adds a book to the wishlist.
 *
 * This function adds a new book to the wishlist.
 *
 * @param newBook Pointer to the new book to add.
 * @param pathFileWishlist The path to the wishlist file.
 * @return 1 if the book is successfully added, 0 otherwise.
 */
int addBookToWishlist(const Book* newBook, const char* pathFileWishlist) {
	FILE* file = fopen(pathFileWishlist, "ab");
	if (!file) { return 0; }
	fwrite(newBook, sizeof(Book), 1, file);
	fclose(file);
	return 1;
}
/**
 * @brief Displays a menu for adding a book to the wishlist.
 *
 * This function prompts the user to input details of a book and adds it to the wishlist.
 *
 * @param pathFileWishlist The path to the wishlist file.
 * @return 1 if the book is successfully added, 0 otherwise.
 */
int addBookToWishlistMenu(const char* pathFileWishlist) {
	clearScreen();
	Book newBook;

	printf("Enter book name: ");
	fgets(newBook.title, sizeof(newBook.title), stdin);
	newBook.title[strcspn(newBook.title, "\n")] = 0;

	printf("Enter author: ");
	fgets(newBook.author, sizeof(newBook.author), stdin);
	newBook.author[strcspn(newBook.author, "\n")] = 0;

	printf("Enter Genre: ");
	fgets(newBook.genre, sizeof(newBook.genre), stdin);
	newBook.genre[strcspn(newBook.genre, "\n")] = 0;

	printf("Enter Cost: ");
	int cost = getInput();
	if (cost < 0) { printf("Invalid input for cost.\n"); enterToContinue(); return 0; }
	newBook.cost = cost;

	newBook.owner = loggedUser;
	newBook.isBorrowed = 0;
	newBook.id = getNewWishlistId(pathFileWishlist);

	if (!addBookToWishlist(&newBook, pathFileWishlist)) { printf("Failed to add book.\n"); enterToContinue(); return 0; }

	printf("Book added successfully.\n");
	enterToContinue();
	return 1;
}
/**
 * @brief Displays a menu for deleting a book from the wishlist.
 *
 * This function prompts the user to input the ID of the book to delete from the wishlist.
 *
 * @param pathFileWishlist The path to the wishlist file.
 * @return true if the book is successfully deleted, false otherwise.
 */
bool deleteBookFromWishlistMenu(const char* pathFileWishlist) {
	clearScreen();
	Book* books = NULL;
	int bookCount = loadBooks(pathFileWishlist, &books);
	if (bookCount == 0) {
		printf("No books available to delete.\n");
		enterToContinue();
		return false;
	}

	viewCatalogForFunc(pathFileWishlist);
	printf("Enter the ID of the book to delete: ");
	int bookId = getInput();

	if (bookId < 0) { handleInputError(); enterToContinue(); return false; }

	bool result = deleteBookToWishlist(bookId, pathFileWishlist, books, bookCount);
	enterToContinue();
	if (books != NULL) {
		free(books);
	}
	return result;
}
/**
 * @brief Displays the wishlist.
 *
 * This function displays the books in the wishlist.
 *
 * @param pathFileWishlist The path to the wishlist file.
 * @return 1 if the wishlist is displayed successfully, 0 otherwise.
 */
int viewWishlist(const char* pathFileWishlist) {
	clearScreen();
	Book* books = NULL;
	int bookCount = loadOwnedBooks(pathFileWishlist, &books, loggedUser.id);

	if (bookCount <= 0) {
		printf("No books owned.\n");
	}
	else {
		for (int i = 0; i < bookCount; i++) {
			printf("ID: %d, Title: %s, Author: %s, Genre: %s, Cost: %d\n",
				books[i].id, books[i].title, books[i].author, books[i].genre, books[i].cost);
		}
	}

	enterToContinue();
	free(books);
	return 1;
}

/**
 * @brief Displays the user's wishlist for function purposes.
 *
 * This function displays the books in the user's wishlist without clearing the screen.
 *
 * @param pathFileWishlist The path to the wishlist file.
 * @return 1 if the wishlist is displayed successfully, 0 otherwise.
 */
int viewWishlistCatalogForFunc(const char* pathFileWishlist) {
	clearScreen();
	Book* books = NULL;
	int bookCount = loadOwnedBooks(pathFileWishlist, &books, loggedUser.id);

	if (bookCount <= 0) {
		printf("No books owned.\n");
	}
	else {
		for (int i = 0; i < bookCount; i++) {
			printf("ID: %d, Title: %s, Author: %s, Genre: %s, Cost: %d\n",
				books[i].id, books[i].title, books[i].author, books[i].genre, books[i].cost);
		}
	}

	free(books);
	return 1;
}

/**
 * @brief Displays a menu for searching a book in the wishlist.
 *
 * This function prompts the user to input the title of the book they are looking for and searches it in the wishlist.
 *
 * @param pathFileWishlist The path to the wishlist file.
 * @return 1 if the search operation is completed successfully, 0 otherwise.
 */
int searchWishlistMenu(const char* pathFileWishlist) {
	clearScreen();
	printf("Enter the title of the book you're looking for: ");
	char targetTitle[100];
	fgets(targetTitle, sizeof(targetTitle), stdin);
	targetTitle[strcspn(targetTitle, "\n")] = 0; // Remove newline character

	// Load Wishlist Books
	Book* books = NULL;
	int bookCount = loadOwnedBooks(pathFileWishlist, &books, loggedUser.id);

	if (bookCount <= 0) {
		printf("Your wishlist is empty.\n");
		enterToContinue();
		return 0;
	}

	// Assuming books are sorted by title
	int resultIndex = binarySearchBookByTitle(books, 0, bookCount - 1, targetTitle);

	if (resultIndex != -1) {
		printf("Book found: ID: %d, Title: %s, Author: %s, Genre: %s, Cost: %d\n",
			books[resultIndex].id, books[resultIndex].title, books[resultIndex].author, books[resultIndex].genre, books[resultIndex].cost);
	}
	else {
		printf("Book with title '%s' not found in your wishlist.\n", targetTitle);
	}

	enterToContinue();
	free(books);
	return 1;
}

/**
 * @brief Marks a book in the wishlist as acquired and adds it to the user's book collection.
 *
 * This function prompts the user to input the ID of the book they have acquired from the wishlist and adds it to their book collection.
 *
 * @param pathFileBooks The path to the user's book collection file.
 * @param pathFileWishlist The path to the wishlist file.
 * @return 1 if the book is successfully marked as acquired and added to the collection, 0 otherwise.
 */
int markAsAcquiredMenu(const char* pathFileBooks, const char* pathFileWishlist) {
	clearScreen();
	printf("Your Wishlist:\n");

	Book* wishlistBooks = NULL;
	int wishlistCount = loadOwnedBooks(pathFileWishlist, &wishlistBooks, loggedUser.id);

	if (wishlistCount <= 0) {
		printf("Your wishlist is empty.\n");
		enterToContinue();
		return 0;
	}

	viewWishlistCatalogForFunc(pathFileWishlist);

	printf("\nEnter the ID of the book you have acquired: ");
	int acquiredBookId = getInput();

	int i;
	Book acquiredBook;
	bool found = false;
	for (i = 0; i < wishlistCount; i++) {
		if (wishlistBooks[i].id == acquiredBookId) {
			acquiredBook = wishlistBooks[i];
			found = true;
			break;
		}
	}

	if (!found) {
		printf("Book not found in your wishlist.\n");
		enterToContinue();
		return 0;
	}

	for (int j = i; j < wishlistCount - 1; j++) { wishlistBooks[j] = wishlistBooks[j + 1]; }
	wishlistCount--;

	saveBooks(pathFileWishlist, wishlistBooks, wishlistCount);

	acquiredBook.id = getNewBookId(pathFileBooks);
	acquiredBook.isBorrowed = 0;
	addBook(&acquiredBook, pathFileBooks);

	printf("Book marked as acquired and added to your book collection.\n");
	enterToContinue();
	free(wishlistBooks);
	return 1;
}

/**
 * @brief Manages the user's wishlist.
 *
 * This function provides a menu for the user to manage their wishlist, including adding, deleting, and viewing books in the wishlist.
 *
 * @param pathFileBooks The path to the user's book collection file.
 * @param pathFileWishlist The path to the wishlist file.
 * @return 0 upon successful completion of managing the wishlist.
 */
int wishList(const char* pathFileBooks, const char* pathFileWishlist) {
	int choice;

	while (1) {
		wishListMenu();
		choice = getInput();

		if (choice == -2) {
			handleInputError();
			enterToContinue();
			continue;
		}

		switch (choice) {
		case 1:
			addBookToWishlistMenu(pathFileWishlist);
			break;
		case 2:
			deleteBookFromWishlistMenu(pathFileWishlist);
			break;
		case 3:
			markAsAcquiredMenu(pathFileBooks, pathFileWishlist);
			break;
		case 4:
			viewWishlist(pathFileWishlist);
			break;
		case 5:
			searchWishlistMenu(pathFileWishlist);
			break;
		case 6:
			return 0;
		default:
			printf("Invalid choice. Please try again.\n");
			enterToContinue();
			break;
		}
	}
}

//Wishlist


//Register-Login
/**
 * @brief Registers a new user.
 *
 * This function registers a new user by adding their information to the user database file.
 *
 * @param user The user to register.
 * @param pathFileUser The path to the user database file.
 * @return 1 if the user is registered successfully, 0 otherwise.
 */
int registerUser(User user, const char* pathFileUser) {
	FILE* file = fopen(pathFileUser, "rb+");
	int userCount = 0;
	User* users = NULL;

	if (file) {

		fread(&userCount, sizeof(int), 1, file);
		if (userCount > 0) {
			users = (User*)malloc(sizeof(User) * userCount);
			fread(users, sizeof(User), userCount, file);

			for (int i = 0; i < userCount; ++i) {
				if (strcmp(users[i].email, user.email) == 0) {
					printf("User already exists.\n");
					fclose(file);
					free(users);
					enterToContinue();
					return 0;
				}
			}
		}
		rewind(file);
	}
	else {
		file = fopen(pathFileUser, "wb");
	}

	user.id = getNewUserId(users, userCount);
	userCount++;
	users = (User*)realloc(users, sizeof(User) * userCount);
	users[userCount - 1] = user;

	fwrite(&userCount, sizeof(int), 1, file);
	fwrite(users, sizeof(User), userCount, file);

	printf("User registered successfully: Welcome %s %s\n", user.name, user.surname);

	if (users != NULL) {
		free(users);
	}
	fclose(file);
	enterToContinue();
	return 1;
}

/**
 * @brief Displays a menu for user registration.
 *
 * This function prompts the user to input their name, surname, email, and password for registration.
 *
 * @param pathFileUsers The path to the user database file.
 * @return 1 if the registration process is completed successfully, 0 otherwise.
 */
int registerUserMenu(const char* pathFileUsers) {
	clearScreen();
	User newUser;

	printf("Enter Name: ");
	fgets(newUser.name, sizeof(newUser.name), stdin);
	newUser.name[strcspn(newUser.name, "\n")] = 0;

	printf("Enter Surname: ");
	fgets(newUser.surname, sizeof(newUser.surname), stdin);
	newUser.surname[strcspn(newUser.surname, "\n")] = 0;

	printf("Enter email: ");
	fgets(newUser.email, sizeof(newUser.email), stdin);
	newUser.email[strcspn(newUser.email, "\n")] = 0;

	printf("Enter password: ");
	fgets(newUser.password, sizeof(newUser.password), stdin);
	newUser.password[strcspn(newUser.password, "\n")] = 0;

	if (registerUser(newUser, pathFileUsers)) {
		return 1;
	}
	else {
		printf("Registration failed.\n");
	}

	enterToContinue();
	return 1;
}

/**
 * @brief Logs in a user.
 *
 * This function verifies the user's email and password against the user database file for login.
 *
 * @param loginUser The user attempting to log in.
 * @param pathFileUsers The path to the user database file.
 * @return 1 if the login is successful, 0 otherwise.
 */
int loginUser(User loginUser, const char* pathFileUsers) {
	FILE* file = fopen(pathFileUsers, "rb");
	if (!file) {
		printf("Failed to open user file.\n");
		return 0;
	}

	int userCount = 0;
	fread(&userCount, sizeof(int), 1, file);
	if (userCount == 0) {
		printf("No users registered.\n");
		fclose(file);
		enterToContinue();
		return 0;
	}

	User userFromFile;
	for (int i = 0; i < userCount; i++) {
		fread(&userFromFile, sizeof(User), 1, file);
		if (strcmp(userFromFile.email, loginUser.email) == 0 && strcmp(userFromFile.password, loginUser.password) == 0) {
			printf("Login successful.\n");
			fclose(file);
			enterToContinue();
			loggedUser = userFromFile;
			return 1;
		}
	}

	printf("Incorrect email or password.\n");
	fclose(file);
	enterToContinue();
	return 0;
}

/**
 * @brief Displays a menu for user login.
 *
 * This function prompts the user to input their email and password for login.
 *
 * @param pathFileUsers The path to the user database file.
 * @return 1 if the login process is completed successfully, 0 otherwise.
 */
int loginUserMenu(const char* pathFileUsers) {
	clearScreen();
	User loginUsers;

	printf("Enter email: ");
	fgets(loginUsers.email, sizeof(loginUsers.email), stdin);
	loginUsers.email[strcspn(loginUsers.email, "\n")] = 0;

	printf("Enter password: ");
	fgets(loginUsers.password, sizeof(loginUsers.password), stdin);
	loginUsers.password[strcspn(loginUsers.password, "\n")] = 0;

	return loginUser(loginUsers, pathFileUsers);
}

//Register-Login


//Menus
/**
 * @brief Handles user operations menu.
 *
 * This function displays the user operations menu and handles user input to navigate through different user operations.
 *
 * @param pathFileBooks The path to the books database file.
 * @param pathFileHistories The path to the lending histories database file.
 * @param pathFileWishlist The path to the wishlist database file.
 * @return 0 when the user chooses to exit the menu.
 */
int userOperations(const char* pathFileBooks, const char* pathFileHistories, const char* pathFileWishlist) {
	int choice;

	while (1) {
		userMenu();
		choice = getInput();

		if (choice == -2) {
			handleInputError();
			enterToContinue();
			continue;
		}

		switch (choice) {
		case 1:
			bookCataloging(pathFileBooks);
			break;
		case 2:
			loanManagement(pathFileBooks, pathFileHistories);
			break;
		case 3:
			wishList(pathFileBooks, pathFileWishlist);
			break;
		case 4:
			return 0;
		default:
			clearScreen();
			printf("Invalid choice. Please try again.\n");
			enterToContinue();
			break;
		}
	}
}

/**
 * @brief Handles the main menu of the program.
 *
 * This function displays the main menu of the program and handles user input to navigate through different options like login, registration, and exit.
 *
 * @param pathFileUsers The path to the users database file.
 * @param pathFileBooks The path to the books database file.
 * @param pathFileLendingHistories The path to the lending histories database file.
 * @param pathFileWishlist The path to the wishlist database file.
 * @return 0 when the user chooses to exit the program.
 */