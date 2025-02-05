#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>
#include <iostream>

class Transaction
{
private:
    std::string userID;
    std::string bookISBN;
    std::string dueDate;

public:
    // Constructor
    Transaction(std::string userID = "", std::string bookISBN = "", std::string bookDueDate = "");

    // Display method for transactions
    void displayTransaction() const;

    //Methods for stream operators for file Input/Output
    friend std::ostream &operator<<(std::ostream &os, const Transaction &transaction);
    friend std::istream &operator>>(std::istream &is, Transaction &transaction);
};

#endif