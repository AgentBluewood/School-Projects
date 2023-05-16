#ifndef LIBRARYBOOK_H
#define LIBRARYBOOK_H

#include "Book.h"

class LibraryBook
{
public:
    Book book;
    LibraryBook *next;
    LibraryBook *prev;    

    LibraryBook()
    {
        next = nullptr;
        prev = nullptr;
    }
};

#endif // LIBRARYBOOK
