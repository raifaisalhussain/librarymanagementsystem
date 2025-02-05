#ifndef LIBRARY_ITEMS_HPP
#define LIBRARY_ITEMS_HPP

#include <string>

class LibraryItems
{
protected:
    std::string title;
    bool availability;

public:
    LibraryItems(const std::string &title, bool available = true);

    // Virtual destructor 
    virtual ~LibraryItems();

    // Getter methods
    std::string getTitle() const;
    bool isAvailable() const;

    // Setter method
    void setAvailable(bool avail);

    // Virtual display function
    virtual void display() const;
};

#endif