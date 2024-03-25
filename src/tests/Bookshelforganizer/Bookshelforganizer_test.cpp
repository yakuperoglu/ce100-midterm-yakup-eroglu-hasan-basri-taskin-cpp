//#define ENABLE_BOOKSHELFORGANIZER_TEST  // Uncomment this line to enable the Bookshelforganizer tests

#include "gtest/gtest.h"
#include "../../bookshelforganizer/header/bookshelforganizer.h"  // Adjust this include path based on your project structure

using namespace Coruh::Bookshelforganizer;

class BookshelforganizerTest : public ::testing::Test {
protected:
	void SetUp() override {
		// Setup test data
	}

	void TearDown() override {
		// Clean up test data
	}
};

TEST_F(BookshelforganizerTest, TestAdd) {
	double result = Bookshelforganizer::add(5.0, 3.0);
	EXPECT_DOUBLE_EQ(result, 8.0);
}

TEST_F(BookshelforganizerTest, TestSubtract) {
	double result = Bookshelforganizer::subtract(5.0, 3.0);
	EXPECT_DOUBLE_EQ(result, 2.0);
}

TEST_F(BookshelforganizerTest, TestMultiply) {
	double result = Bookshelforganizer::multiply(5.0, 3.0);
	EXPECT_DOUBLE_EQ(result, 15.0);
}

TEST_F(BookshelforganizerTest, TestDivide) {
	double result = Bookshelforganizer::divide(6.0, 3.0);
	EXPECT_DOUBLE_EQ(result, 2.0);
}

TEST_F(BookshelforganizerTest, TestDivideByZero) {
	EXPECT_THROW(Bookshelforganizer::divide(5.0, 0.0), std::invalid_argument);
}

/**
 * @brief The main function of the test program.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line argument strings.
 * @return int The exit status of the program.
 */
int main(int argc, char** argv) {
#ifdef ENABLE_BOOKSHELFORGANIZER_TEST
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
#else
	return 0;
#endif
}