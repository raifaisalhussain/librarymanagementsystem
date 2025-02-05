#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <vector>
#include <iostream>

class User
{
private:
    std::string userID;
    std::string userName;
    std::vector<std::string> borrowedBooks;

public:
    // Constructor
    User(std::string id = "", std::string n = "");

    // Getter methods for user attributes
    std::string getUserID() const;
    std::string getName() const;

    // Book management methods borrow/return
    void borrowBook(const std::string &ISBN);
    void returnBook(const std::string &ISBN);

    // user display method
    void displayUser() const;

    // Operator overloads for file Input/Output
    friend std::ostream &operator<<(std::ostream &os, const User &user);
    friend std::istream &operator>>(std::istream &is, User &user);
};

#endif
