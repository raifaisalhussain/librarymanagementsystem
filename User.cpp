#include "User.hpp"
#include <algorithm>

// Constructor
User::User(std::string id, std::string n) : userID(id), userName(n) {}

// Getters methods for user attributes
std::string User::getUserID() const { return userID; }
std::string User::getName() const { return userName; }

// Borrow book
void User::borrowBook(const std::string &ISBN)
{
    borrowedBooks.push_back(ISBN);
}

// Return book
void User::returnBook(const std::string &ISBN)
{
    borrowedBooks.erase(std::remove(borrowedBooks.begin(), borrowedBooks.end(), ISBN), borrowedBooks.end());
}

// Display user
void User::displayUser() const
{
    std::cout << "User ID: " << userID << ", Name: " << userName << "\nBorrowed Books: ";
    for (const auto &book : borrowedBooks)
        std::cout << book << " ";
    std::cout << std::endl;
}

// Overloaded output operator
std::ostream &operator<<(std::ostream &os, const User &user)
{
    os << user.userID << "," << user.userName;
    return os;
}

// Overloaded input operator
std::istream &operator>>(std::istream &is, User &user)
{
    std::getline(is, user.userID, ',');
    std::getline(is, user.userName);
    return is;
}
