#ifndef LIBRARY_MANAGER_HPP
#define LIBRARY_MANAGER_HPP

#include <vector>
#include <string>
#include "Library.hpp"  

class LibraryManager {
private:
    Library library;

public:
    LibraryManager();
    void loadData();
    std::vector<Book> getBooks() const;
    std::vector<User> getUsers() const;
    std::vector<Transaction> getAllTransactions() const;
    void getAllTransaction();
    void displayTransactions() const;
    void startBookAddition();
    void startBookRemoval();
    void startBookSearch();
    void startUserAddition();
    void startUserRemoval();
    void startBookBorrowing();
    void startBookReturn();
    void displayMenu();
    void start();
    void handleSearchBookByISBN(const std::string &bookISBN);
    void handleSearchBookByTitle(const std::string &bookTitle);
    void handleRemoveBook(const std::string &bookISBN);
    void handleAddBook(const std::string &bookTitle, const std::string &author, const std::string &bookISBN);
    void handleAddUser(const std::string &userID, const std::string &userName);
    void handleRemoveUser(const std::string &userID);
    void handleBorrowBook(const std::string &bookISBN, const std::string &userID, const std::string &bookDueDate);
    void handleReturnBook(const std::string &bookISBN, const std::string &userID);
    void handleDisplayBooks();
    void handleDisplayUsers();
    void saveData();
};

#endif
