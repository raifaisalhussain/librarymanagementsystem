#include "LibraryItems.hpp"
#include <iostream>

// Destructor function called to ensures proper cleanup in polymorphic use, derived destructors are called first.
LibraryItems::~LibraryItems() {}

LibraryItems::LibraryItems(const std::string &title, bool available)
    : title(title), availability(available) {}

//Getter method for title of library item
std::string LibraryItems::getTitle() const
{
    return title;
}

//Getter method for availability of library item
bool LibraryItems::isAvailable() const
{
    return availability;
}

//Setter method for availability of library item
void LibraryItems::setAvailable(bool avail)
{
    availability = avail;
}

// Display Function to be overridden by derived classes
void LibraryItems::display() const
{
    std::cout << "Title: " << title << ", Available: " << (availability ? "Yes" : "No") << "\n";
}