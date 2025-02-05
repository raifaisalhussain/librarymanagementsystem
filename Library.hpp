#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <vector>
#include <string>
#include <memory>
#include "Book.hpp"
#include "User.hpp"
#include "Transaction.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

class Library
{
private:
    std::vector<std::unique_ptr<LibraryItems>> items; //unique_ptr is used to memory management
    std::vector<User> users;
    std::vector<Transaction> transactions;

public:
    //Library operation methods
    std::vector<User> getUsers() const;
    std::vector<Transaction> getTransactions() const;
    void addUser(const User &user);
    void removeUser(const std::string &userID);
    void borrowBook(const std::string &bookISBN, const std::string &userID, const std::string &dueDate);
    void returnBook(const std::string &bookISBN, const std::string &userID);
    void displayTransactions() const;
    void saveData();
    void loadData();
    std::vector<Book> getBooks() const;
    void searchBookByISBN(const std::string &bookISBN) const;
    void searchBookByTitle(const std::string &bookTitle) const;
    void addBook(const Book &book);
    void removeBook(const std::string &bookISBN);
};

#endif
