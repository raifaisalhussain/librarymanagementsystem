#include "Transaction.hpp"

Transaction::Transaction(std::string userID, std::string bookISBN, std::string bookDueDate)
    : userID(userID), bookISBN(bookISBN), dueDate(bookDueDate) {}

//Method to display transaction
void Transaction::displayTransaction() const
{
    std::cout << "User ID: " << userID << ", Book ISBN: " << bookISBN
              << ", Due Date: " << dueDate << std::endl;
}

std::ostream &operator<<(std::ostream &os, const Transaction &transaction)
{
    os << transaction.userID << "," << transaction.bookISBN << "," << transaction.dueDate;
    return os;
}

std::istream &operator>>(std::istream &is, Transaction &transaction)
{
    std::getline(is, transaction.userID, ',');
    std::getline(is, transaction.bookISBN, ',');
    std::getline(is, transaction.dueDate);
    return is;
}