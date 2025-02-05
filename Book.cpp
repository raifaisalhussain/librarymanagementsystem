#include "Book.hpp"
#include <iostream>

Book::Book(const std::string &title, const std::string &author, const std::string &ISBN, bool available)
    : LibraryItems(title, available), bookAuthor(author), bookISBN(ISBN) {}

//getter method for book Author
std::string Book::getBookAuthor() const
{
    return bookAuthor;
}

//getter method for book ISBN
std::string Book::getBookISBN() const
{
    return bookISBN;
}

// Display function of Books overridden to base class display function
void Book::display() const
{
    std::cout << "Title: " << title << ", Author: " << bookAuthor
              << ", ISBN: " << bookISBN
              << ", Available: " << (availability ? "Yes" : "No") << "\n";
}