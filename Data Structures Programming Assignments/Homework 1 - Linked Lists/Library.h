#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "LibraryBook.h"

using namespace std;

class Library
{
private:
        LibraryBook* firstBook;
        LibraryBook* lastBook;
        int numBooks;
        
public:
	Library();
        Library( Library& other);

        int getnumBooks() const;
        LibraryBook *getBook( const int pos );
        LibraryBook *getFirstBook ();
        LibraryBook *getLastBook();
          
        // add a Book to the library
	     void addBook(Book book);

        // Move a book to the front
        void moveToFront (LibraryBook *entry);

        // print all Books
        void printAllBooks() const;

        // print all Books of a single Genre
        void printBooksOfOneGenre(string genre);
        
};
#endif // LIBRARY_H
