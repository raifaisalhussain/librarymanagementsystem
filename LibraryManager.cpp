#include "LibraryManager.hpp"
#include <iostream>
#include <limits>
LibraryManager::LibraryManager(){}

// Method to Load Data from files
void LibraryManager::loadData()
{
    library.loadData();
}

// Method to get all books from file
std::vector<Book> LibraryManager::getBooks() const
{
    return library.getBooks();
}

// Method to get all users from file
std::vector<User> LibraryManager::getUsers() const
{
    return library.getUsers();
}

// Method to get all transactions from file
std::vector<Transaction> LibraryManager::getAllTransactions() const
{
    return library.getTransactions();
}

// Method to get all transactions from file
void LibraryManager::getAllTransaction()
{
    library.displayTransactions();
}

void LibraryManager::displayTransactions() const
{
    std::vector<Transaction> libraryTransactions = getAllTransactions();

    if (libraryTransactions.empty())
    {
        std::cout << "No transactions found.\n";
    }
    else
    {
        std::cout << "Displaying all transactions:\n";
        for (const auto &transaction : libraryTransactions)
        {
            transaction.displayTransaction();
        }
    }
}

// Method to start add book process
void LibraryManager::startBookAddition()
{
    std::string bookTitle, bookAuthor, bookISBN;

    std::cout << "Enter book title: ";
    std::getline(std::cin >> std::ws, bookTitle);

    std::cout << "Enter author: ";
    std::getline(std::cin, bookAuthor);

    std::cout << "Enter ISBN: ";
    std::getline(std::cin, bookISBN);

    library.addBook(Book(bookTitle, bookAuthor, bookISBN));
    std::cout << "Book added!\n";
}

// Method to start book removal process
void LibraryManager::startBookRemoval()
{
    std::string bookISBN;

    std::cout << "Enter ISBN of the book to remove: ";
    std::getline(std::cin >> std::ws, bookISBN);

    handleRemoveBook(bookISBN);
}

// Method to start book search process
void LibraryManager::startBookSearch()
{
    int choice;
    std::cout << "Search by:\n1. ISBN\n2. Title\nEnter your choice: ";
    std::cin >> choice;
    std::cin.ignore();
    if (choice == 1)
    {
        std::string bookISBN;
        std::cout << "Enter ISBN: ";
        std::getline(std::cin, bookISBN);
        handleSearchBookByISBN(bookISBN);
    }
    else if (choice == 2)
    {
        std::string bookTitle;
        std::cout << "Enter title: ";
        std::getline(std::cin, bookTitle);
        handleSearchBookByTitle(bookTitle);
    }
    else
    {
        std::cout << "Wrong Choice.\n";
    }
}

// Method to start add User process
void LibraryManager::startUserAddition()
{
    std::string userID, userName;

    std::cout << "Enter User ID: ";
    std::getline(std::cin >> std::ws, userID);

    std::cout << "Enter User Name: ";
    std::getline(std::cin, userName);

    library.addUser(User(userID, userName));
}

// Method to start user removal process
void LibraryManager::startUserRemoval()
{
    std::string userID;

    std::cout << "Enter User ID to remove: ";
    std::getline(std::cin >> std::ws, userID);

    handleRemoveUser(userID);
}

// Method to start book borrowing process
void LibraryManager::startBookBorrowing()
{
    std::string bookISBN, userID, bookDueDate;

    std::cout << "Enter ISBN of the book to borrow: ";
    std::getline(std::cin >> std::ws, bookISBN);

    std::cout << "Enter User ID: ";
    std::getline(std::cin, userID);

    std::cout << "Enter Due Date (YYYY-MM-DD): ";
    std::getline(std::cin, bookDueDate);

    handleBorrowBook(bookISBN, userID, bookDueDate);
}

// Method to start Book return process
void LibraryManager::startBookReturn()
{
    std::string bookISBN, userID;

    std::cout << "Enter ISBN of the book: ";
    std::getline(std::cin >> std::ws, bookISBN);

    std::cout << "Enter User ID: ";
    std::getline(std::cin, userID);

    handleReturnBook(bookISBN, userID);
}

// Display Menu of Library System
void LibraryManager::displayMenu()
{
    std::cout << "\nLibrary Management System\n";
    std::cout << "1. Add Book\n";
    std::cout << "2. Remove Book\n";
    std::cout << "3. Search Book\n";
    std::cout << "4. Add User\n";
    std::cout << "5. Remove User\n";
    std::cout << "6. Borrow Book\n";
    std::cout << "7. Return Book\n";
    std::cout << "8. Display Books\n";
    std::cout << "9. Display Users\n";
    std::cout << "10. Display Transactions\n";
    std::cout << "11. Load Data\n";
    std::cout << "12. Save Data\n";
    std::cout << "13. Exit\n";
    std::cout << "Enter your choice: ";
}

void LibraryManager::start()
{
    int choice;
    while (true)
    {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice)
        {
        case 1:
            startBookAddition();
            break;
        case 2:
            startBookRemoval();
            break;
        case 3:
            startBookSearch();
            break;
        case 4:
            startUserAddition();
            break;
        case 5:
            startUserRemoval();
            break;
        case 6:
            startBookBorrowing();
            break;
        case 7:
            startBookReturn();
            break;
        case 8:
            handleDisplayBooks();
            break;
        case 9:
            handleDisplayUsers();
            break;
        case 10:
            displayTransactions();
            break;
        case 11:
            library.loadData();
            break;
        case 12:
            library.saveData();
            break;
        case 13:
            std::cout << "Exiting...\n";
            return;
        default:
            std::cout << "Enter valid option shown in List.\n";
        }
    }
}

// Method to handle book search by ISBN
void LibraryManager::handleSearchBookByISBN(const std::string &bookISBN)
{
    library.searchBookByISBN(bookISBN);
}

// Method to handle book search by Title
void LibraryManager::handleSearchBookByTitle(const std::string &bookTitle)
{
    library.searchBookByTitle(bookTitle);
}

// Method to handle book removal
void LibraryManager::handleRemoveBook(const std::string &bookISBN)
{
    library.removeBook(bookISBN);
}

// Method to handle book addition in system
void LibraryManager::handleAddBook(const std::string &bookTitle, const std::string &bookAuthor, const std::string &bookISBN)
{
    library.addBook(Book(bookTitle, bookAuthor, bookISBN));
    std::cout << "Book added successfully: " << bookTitle << " by " << bookAuthor << "\n";
}

// Method to handle user addition in system
void LibraryManager::handleAddUser(const std::string &userID, const std::string &userName)
{
    library.addUser(User(userID, userName));
}

// Method to handle user removal from system
void LibraryManager::handleRemoveUser(const std::string &userID)
{
    library.removeUser(userID);
}

// Method to handle book borrowing
void LibraryManager::handleBorrowBook(const std::string &bookISBN, const std::string &userID, const std::string &bookDueDate)
{
    library.borrowBook(bookISBN, userID, bookDueDate);
}

// Method to handle book return
void LibraryManager::handleReturnBook(const std::string &bookISBN, const std::string &userID)
{
    library.returnBook(bookISBN, userID);
}

// Method to handle all books display
void LibraryManager::handleDisplayBooks()
{
    for (const auto &book : library.getBooks())
    {
        std::cout << "Title: " << book.getTitle()
                  << ", Author: " << book.getBookAuthor()
                  << ", ISBN: " << book.getBookISBN()
                  << ", Available: " << (book.isAvailable() ? "Yes" : "No") << "\n";
    }
}

// Method to handle all users display
void LibraryManager::handleDisplayUsers()
{
    for (const auto &user : library.getUsers())
    {
        std::cout << "User ID: " << user.getUserID()
                  << ", Name: " << user.getName() << "\n";
    }
}

// Method to handle data saving in files
void LibraryManager::saveData()
{
    library.saveData();
}
