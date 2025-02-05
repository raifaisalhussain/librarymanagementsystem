#ifndef BOOK_HPP
#define BOOK_HPP

#include "LibraryItems.hpp"
#include <string>

class Book : public LibraryItems
{
private:
    std::string bookAuthor;
    std::string bookISBN;

public:
    // Constructor
    Book(const std::string &title, const std::string &author, const std::string &ISBN, bool available = true);

    // Getter methods for book attributes
    std::string getBookAuthor() const;
    std::string getBookISBN() const;

    // Override display function with base class
    void display() const override;
};

#endif