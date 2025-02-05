Library Management System

Overview

The Library Management System is a client-server application designed to manage books, users, and transactions efficiently. It enables users to add, remove, and search for books, manage library users, borrow and return books, and track transactions. The system is implemented using C++ with UDP sockets for network communication and multithreading to support concurrent client connections.

Features

•	Book Management: Add, remove, and search for books by title or ISBN.

•	User Management: Register new users and remove users from the system.

•	Borrow & Return Books: Users can borrow books and return them with proper transaction logging.

•	Transaction Logging: Tracks all borrow and return operations for accountability.

•	UDP-based Networking: Client-server communication using UDP sockets.

•	Multithreading: Handles multiple client requests concurrently using a thread pool.

•	Serialization: Saves and loads books, users, and transactions to/from files for data persistence.

•	Validation: Ensures ISBNs are numeric and have a length between 10 and 13 characters.

Technologies Used

•	C++17

•	Winsock2 API (Windows Sockets)

•	Multithreading (std::thread & std::mutex)

•	File Handling & Serialization

•	UDP Networking

•	STL Containers (std::vector, std::string, etc.)

•	Object-Oriented Programming (Inheritance & Polymorphism)


Installation & Compilation

Prerequisites

•	Windows (using MinGW compiler) or Linux (g++ installed)

•	Make (optional for automated builds)

•	A C++17-compatible compiler

How to Use
1.	Run the Server: Start the server first so that clients can connect.
2.	Run the Client: Open a client instance and connect to the server.
3.	Select an Operation:

o	Add Book: Provide title, author, and ISBN.

o	Remove Book: Enter ISBN to remove a book.

o	Search Book: Search by ISBN or title.

o	Add User: Register a new library user.

o	Remove User: Remove a user by ID.

o	Borrow Book: Provide ISBN and User ID.

o	Return Book: Enter ISBN and User ID.

o	Display Transactions: View all borrowing records.

o	Save & Load Data: Persist data between sessions.

Configuration

If you need to change the server IP in the client:

1.	Open Client.cpp
   
3.	Modify the server IP in the constructor
   
5.	Recompile and run.

UML Diagrams
Class Diagram

![class_diagram](https://github.com/user-attachments/assets/85406615-01ac-4213-94a9-3477fe0c8e87)

Use Case Diagram

![use case_diagram](https://github.com/user-attachments/assets/76792241-a88d-4e7e-9429-034c8ae2b016)

Challenges & Solutions

Ensuring Reliable UDP Communication
   
•	Problem: UDP is a connectionless protocol and doesn't guarantee message delivery.

•	Solution: Implemented a retry mechanism for lost packets and acknowledgments to confirm received messages.

Handling Concurrent Requests
   
•	Problem: The server needed to support multiple clients simultaneously.

•	Solution: Used multithreading with a thread pool to handle client requests concurrently.

Input Validation Issues

•	Problem: Initial implementation resulted in missing first characters from user inputs.

•	Solution: Used std::getline() with std::ws to sanitize and validate inputs.

Data Persistence
   
•	Problem: Books and transactions were lost after server shutdown.

•	Solution: Implemented serialization to store and retrieve books, users, and transactions from files.

Future Enhancements

•	Implement a GUI using Qt or a web-based frontend.

•	Secure Authentication for users and librarians.

•	Support for Book Reservations before borrowing.

•	Logging System to track server requests and responses.

•	Real-time Notifications for overdue books.

Contributors

Faisal Hussain

________________________________________
This README provides all necessary details for setting up, compiling, and running the Library Management System

