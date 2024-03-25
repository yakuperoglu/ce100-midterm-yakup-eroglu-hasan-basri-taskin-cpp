#ifndef TRY_H
#define TRY_H

#include <iostream>
/**
 * @brief Structure representing a user.
 *
 * This structure contains information about a user, including their ID, name, surname, email, and password.
 */
typedef struct {
	int id;
	char name[100];
	char surname[100];
	char email[100];
	char password[100];
} User;
/**
 * @brief Structure representing a book.
 *
 * This structure contains information about a book, including its ID, title, author, genre,
 * owner information, borrowing status, and cost.
 */
typedef struct {
	int id;
	char title[100];
	char author[100];
	char genre[100];
	User owner;
	int isBorrowed;
	int cost;
} Book;
/**
 * @brief Structure representing the history of loaned books.
 *
 * This structure contains information about a loaned book, including its ID, name, owner ID and name,
 * debtor's user ID and name, approval status, and return status.
 */
typedef struct {
	int bookId;
	char bookName[100];
	int bookOwnerId;
	char bookOwnerName[200];
	int debtorUserId;
	char debtorUserName[200];
	int isApproved;
	int hasGivenBack;

} LoanedHistory;




//TOOLS
/**
 * @brief Clears the console screen.
 *
 * This function clears the contents of the console screen.
 */
void clearScreen();

int enterToContinue();

int handleInputError();

int getInput();

//TOOLS


//PRINTMENU

int printMainMenu();

int userMenu();

int bookCatalogingMenu();

int loanManagementMenu();

int wishListMenu();

//PRINTMENU

//IDK

int getNewUserId(User users[], int userCount);

int getNewBookId(const char* pathFileBooks);

int getNewWishlistId(const char* pathFileWishlist);

int saveBooks(const char* path, Book* books, int count);

//IDK


//LOAD

int loadOwnedBooks(const char* pathFileBooks, Book** books, int userId);

int loadUsers(const char* pathFileUsers, User** users);

int loadBooks(const char* path, Book** books);

int loadBooksForUser(const char* pathFileBooks, int userId, Book** filteredBooks);

int loadLoanedHistories(const char* pathFileHistories, LoanedHistory** histories);

int saveLoanedHistories(const char* pathFileHistories, LoanedHistory* histories, int count);

//LOAD


//ALGORITHMS

void swap(Book* a, Book* b);

int partition(Book arr[], int low, int high);

int randomPartition(Book arr[], int low, int high);

int randomizedQuickSortBookIds(Book arr[], int low, int high);

double findLCS(const char* s1, const char* s2);

void heapify(User users[], int n, int i);

void buildMaxHeap(User users[], int n);

int binarySearchBookByTitle(Book books[], int low, int high, const char* targetTitle);

int MatrixChainOrder(int p[], int n);

int mainMatrix(const char* pathFileBooks);

int callMainMatrix(const char* pathFileBooks);

int min(int a, int b);

int minCostArrangingBooks(const char* pathToBooksFile);

//ALGORITHMS


//BookCataloging

int bookCataloging(const char* pathFileBooks);

int addBook(const Book* newBook, const char* pathFileBooks);

bool deleteBook(int bookId, const char* pathFileBooks, Book* books, int bookCount);

bool updateBook(Book* books, int bookCount, int bookId, const char* title, const char* author, const char* genre, int cost, const char* pathFileBooks);

int viewCatalog(const char* filePathBooks);

int viewCatalogForFunc(const char* filePathBooks);

int addBookMenu(const char* pathFileBooks);

bool deleteBookMenu(const char* pathFileBooks);

bool updateBookMenu(const char* pathFileBooks);

int selectBooksByPriceMenu(const char* pathFileBooks);

int calculateBookCosts(const char* pathFileBooks);

int calculateBookCostsMenu(const char* pathFileBooks);

int minCostArrangingBooks(const char* pathToBooksFile);
//BookCataloging


//LoanManagement

int loanManagement(const char* pathFileBooks, const char* pathFileHistories);

int borrowBook(int bookId, const char* pathFileBooks, const char* pathFileHistories);

int giveBackBook(int bookId, const char* pathFileBooks, const char* pathFileHistories);

int borrowBookMenu(const char* pathFileBooks, const char* pathFileHistories);

int giveBackBookMenu(const char* pathFileBooks, const char* pathFileHistories);

int viewBorrowedBooks(const char* pathFileHistories);

int viewGivenBooks(const char* pathFileHistories);

int writeBorrowedBooksToConsole(const char* pathFileHistories);

int writeGivenBooksToConsole(const char* pathFileHistories);

int suggestBooksToBorrow(const char* pathFileBooks);

//LoanManagement


//Wishlist

bool deleteBookToWishlist(int bookId, const char* pathFileWishlist, Book* books, int bookCount);

int addBookToWishlist(const Book* newBook, const char* pathFileWishlist);

int addBookToWishlistMenu(const char* pathFileWishlist);

bool deleteBookFromWishlistMenu(const char* pathFileWishlist);

int viewWishlist(const char* pathFileWishlist);

int viewWishlistCatalogForFunc(const char* pathFileWishlist);

int searchWishlistMenu(const char* pathFileWishlist);

int markAsAcquiredMenu(const char* pathFileBooks, const char* pathFileWishlist);

int wishList(const char* pathFileBooks, const char* pathFileWishlist);

//Wishlist


//Register-Login

int registerUser(User user, const char* pathFileUser);

int registerUserMenu(const char* pathFileUsers);

int loginUser(User loginUser, const char* pathFileUsers);

int loginUserMenu(const char* pathFileUsers);

//Register-Login


//Menus

int userOperations(const char* pathFileBooks, const char* pathFileHistories, const char* pathFileWishlist);

int mainMenu(const char* pathFileUsers, const char* pathFileBooks, const char* pathFileLendingHistories, const char* pathFileWishlist);

//Menus

#endif