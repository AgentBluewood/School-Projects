#include "Library.h"
#include <iostream>

Library::Library()
{
    numBooks = 0;
    firstBook = nullptr;
    lastBook = nullptr;
}

//Copy constructor
Library::Library( Library& other)
{
   //  implement this function
    firstBook = nullptr;
    lastBook = nullptr;
    
    LibraryBook* currentOtherNode = other.getFirstBook();
    while (currentOtherNode != nullptr) {
        addBook(currentOtherNode->book);
        currentOtherNode = currentOtherNode->next;
    }
}

int Library::getnumBooks() const
{
    return numBooks;
}

LibraryBook* Library::getFirstBook()
{
   return firstBook;
}
LibraryBook* Library::getLastBook()
{
   return lastBook;
}

// return a pointer to the n'th book in the linked list
LibraryBook* Library::getBook( const int pos )
{
  // implement this function
    int i = 0;
    LibraryBook* currentNode = nullptr;
    
    if (numBooks < pos) {
        cout << "Book at position " << pos << " not available." << endl;
        return currentNode;
    } else {
        currentNode = firstBook;
        while (i != pos) {
            currentNode = currentNode->next;
            i++;
        }
        return currentNode;
    }
}

// add a Book to the end of the linked list
void Library::addBook(Book book)
{
   // implement this function
    LibraryBook* temp = new LibraryBook;
    temp->book = book;
    
    if (firstBook == nullptr) {
        firstBook = temp;
        lastBook = temp;
    } else {
        lastBook->next = temp;
        temp->prev = lastBook;
        lastBook = temp;
    }
    
    numBooks++;
}


// Move a book to the front of the linked list
void Library::moveToFront (LibraryBook *entry)
{
   // implement this function
    if (firstBook == entry) {
        ;
    } else if (lastBook == entry) {
        entry->prev->next = nullptr;
        lastBook = entry->prev;
        firstBook->prev = entry;
        entry->next = firstBook;
        entry->prev = nullptr;
        firstBook = entry;
    } else {
        entry->prev->next = entry->next;
        entry->next->prev = entry->prev;
        firstBook->prev = entry;
        entry->next = firstBook;
        entry->prev = nullptr;
        firstBook = entry;
    }
}

// print all Books
void Library::printAllBooks() const
{
   // implement this function
    LibraryBook* currentNode = firstBook;
    
    while (currentNode != nullptr) {
        currentNode->book.printBook();
        currentNode = currentNode->next;
    }
}

// print all Books of a single Genre
void Library::printBooksOfOneGenre(string genre)
{
   // implement this function
    LibraryBook* currentNode = firstBook;
    while (currentNode != nullptr) {
        if (currentNode->book.getGenre() == genre) {
            currentNode->book.printBook();
        }
        currentNode = currentNode->next;
    }
}
