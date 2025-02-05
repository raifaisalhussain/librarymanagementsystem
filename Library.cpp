#include "Library.hpp"

// Method to get users of library system
std::vector<User> Library::getUsers() const
{
    return users;
}

// Method to get transactions of library system
std::vector<Transaction> Library::getTransactions() const
{
    return transactions;
}

// Method to add a user in system
void Library::addUser(const User &user)
{
    for (const auto &existingUser : users)
    {
        if (existingUser.getUserID() == user.getUserID())
        {
            std::cerr << "User already exists.\n";
            return;
        }
    }
    users.push_back(user);
    std::cout << "User added: " << user.getName() << "\n";
}

// Method to remove a user using userID from system
void Library::removeUser(const std::string &userID)
{
    auto it = std::remove_if(users.begin(), users.end(),
                             [&userID](const User &user)
                             { return user.getUserID() == userID; });
    if (it != users.end())
    {
        users.erase(it, users.end());
        std::cout << userID << " removed successfully.\n";
    }
    else
    {
        std::cerr << "No user having ID \"" << userID << "\" found in system.\n";
    }
}

// Method to Borrow a book from system
void Library::borrowBook(const std::string &bookISBN, const std::string &userID, const std::string &bookDueDate)
{
    for (auto &item : items)
    {
        if (Book *book = dynamic_cast<Book *>(item.get()); book && book->getBookISBN() == bookISBN && book->isAvailable())
        {
            book->setAvailable(false);
            for (auto &user : users)
            {
                if (user.getUserID() == userID)
                {
                    user.borrowBook(bookISBN);
                    transactions.emplace_back(userID, bookISBN, bookDueDate);
                    std::cout << "Book borrowed successfully.\n";
                    return;
                }
            }
            std::cerr << "User not found.\n";
            return;
        }
    }
    std::cerr << "Book not available or not found.\n";
    return;
}

// Method to return a book to system
void Library::returnBook(const std::string &bookISBN, const std::string &userID)
{
    for (auto &item : items)
    {
        if (Book *book = dynamic_cast<Book *>(item.get()); book && book->getBookISBN() == bookISBN && !book->isAvailable())
        {
            book->setAvailable(true);
            for (auto &user : users)
            {
                if (user.getUserID() == userID)
                {
                    user.returnBook(bookISBN);
                    transactions.emplace_back(userID, bookISBN, "");
                    std::cout << "Book returned successfully.\n";
                    return;
                }
            }
            std::cerr << "User not found.\n";
            return;
        }
    }
    std::cerr << "Book not borrowed or not found.\n";
}

// Method to Display transactions of system
void Library::displayTransactions() const
{
    if (transactions.empty())
    {
        std::cout << "No transactions found.\n";
    }
    else
    {
        for (const auto &transaction : transactions)
        {
            transaction.displayTransaction();
        }
    }
}

// Method to save data to files
void Library::saveData()
{
    // Save books in file
    std::ofstream bookFile("books.txt");
    if (bookFile.is_open())
    {
        for (const auto &item : items)
        {
            if (Book *book = dynamic_cast<Book *>(item.get()))
            {
                bookFile << book->getTitle() << "," << book->getBookAuthor() << "," << book->getBookISBN() << "," << book->isAvailable() << "\n";
            }
        }
        bookFile.close();
    }
    else
    {
        std::cerr << "Failed to open books file for writing.\n";
    }

    // Save users in file
    std::ofstream userFile("users.txt");
    if (userFile.is_open())
    {
        for (const auto &user : users)
        {
            userFile << user.getUserID() << "," << user.getName() << "\n";
        }
        userFile.close();
    }
    else
    {
        std::cerr << "Failed to open user file for writing.\n";
    }

    // Save transactions in file
    std::ofstream transactionFile("transactions.txt");
    if (transactionFile.is_open())
    {
        for (const auto &transaction : transactions)
        {
            transactionFile << transaction << "\n";
        }
        transactionFile.close();
    }
    else
    {
        std::cerr << "Failed to open transactions file for writing.\n";
    }
    std::cout << "Data saved successfully.\n";

}

// Method to load data from files
void Library::loadData()
{
    // Load books from the file
    std::ifstream bookFile("books.txt");
    if (bookFile.is_open())
    {
        std::string line;
        while (std::getline(bookFile, line))
        {
            std::istringstream stream(line);
            std::string bookTitle, bookAuthor, bookISBN;
            bool available;
            std::getline(stream, bookTitle, ',');
            std::getline(stream, bookAuthor, ',');
            std::getline(stream, bookISBN, ',');
            stream >> available;
            items.push_back(std::make_unique<Book>(bookTitle, bookAuthor, bookISBN, available));
        }
        bookFile.close();
    }
    else
    {
        std::cerr << "Failed to open books file for reading.\n";
    }

    // Load users from the file
    std::ifstream userFile("users.txt");
    if (userFile.is_open())
    {
        std::string line;
        while (std::getline(userFile, line))
        {
            std::istringstream stream(line);
            std::string userID, userName;
            std::getline(stream, userID, ',');
            std::getline(stream, userName, ',');
            users.emplace_back(userID, userName);
        }
        userFile.close();
    }
    else
    {
        std::cerr << "Failed to open users file for reading.\n";
    }

    // Load transactions from the file
    std::ifstream transactionFile("transactions.txt");
    if (transactionFile.is_open())
    {
        std::string line;
        while (std::getline(transactionFile, line))
        {
            std::istringstream stream(line);
            Transaction transaction;
            stream >> transaction;
            transactions.push_back(transaction);
        }
        transactionFile.close();
    }
    else
    {
        std::cerr << "Failed to open transactions file for reading.\n";
    }
    std::cout << "Data loaded successfully.\n";
}

// Method to get all books of system
std::vector<Book> Library::getBooks() const
{
    std::vector<Book> books;
    for (const auto &item : items)
    {
        if (Book *book = dynamic_cast<Book *>(item.get()))
        {
            books.push_back(*book);
        }
    }
    return books;
}

// Method to search a book by ISBN
void Library::searchBookByISBN(const std::string &ISBN) const
{
    bool found = false;
    for (const auto &item : items)
    {
        if (Book *book = dynamic_cast<Book *>(item.get()); book && book->getBookISBN() == ISBN)
        {
            book->display();
            found = true;
        }
    }
    if (!found)
    {
        std::cout << "No book found against ISBN: " << ISBN << "\n";
    }
}

// Method to search for a book by title
void Library::searchBookByTitle(const std::string &title) const
{
    bool found = false;
    for (const auto &item : items)
    {
        if (Book *book = dynamic_cast<Book *>(item.get()); book && book->getTitle() == title)
        {
            book->display();
            found = true;
        }
    }
    if (!found)
    {
        std::cout << "No book found with title: " << title << "\n";
    }
}

// Add a book in system
void Library::addBook(const Book &book)
{
    items.push_back(std::make_unique<Book>(book));
}

// Method to remove a book by ISBN
void Library::removeBook(const std::string &bookISBN)
{
    auto it = std::remove_if(items.begin(), items.end(),
                             [&bookISBN](const std::unique_ptr<LibraryItems> &item)
                             {
                                 if (Book *book = dynamic_cast<Book *>(item.get()))
                                 {
                                     return book->getBookISBN() == bookISBN;
                                 }
                                 return false;
                             });
    if (it != items.end())
    {
        items.erase(it, items.end());
        std::cout << "Book with ISBN \"" << bookISBN << "\" removed.\n";
    }
    else
    {
        std::cerr << "No book having ISBN \"" << bookISBN << "\" found.\n";
    }
}
