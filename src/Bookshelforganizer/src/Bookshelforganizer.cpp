#include "../header/bookshelforganizer.h"
#include <stdexcept>

using namespace Coruh::Bookshelforganizer;

double Bookshelforganizer::add(double a, double b) {
    return a + b;
}

double Bookshelforganizer::subtract(double a, double b) {
    return a - b;
}

double Bookshelforganizer::multiply(double a, double b) {
    return a * b;
}

double Bookshelforganizer::divide(double a, double b) {
    if (b == 0) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }
    return a / b;
}