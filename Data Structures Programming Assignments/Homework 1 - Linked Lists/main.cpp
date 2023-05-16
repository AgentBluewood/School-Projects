#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

#include "Book.h"
#include "Library.h"

using namespace std;

void readBooksFromFile (string filename, Library &library)
{
    ifstream input(filename);
    if (input.is_open())  {
        string title, author, publisher, genre;
        int year;
        while (input >> title >> author >> publisher >> genre >> year ) {
            Book newBook(title, author, publisher, genre, year);
            library.addBook(newBook);
        }
    }
    else {
        cout << "Error! File not found." << endl;
    }
}


int main ( int argc, char **argv)
{
    string filename = "books.txt";    
    Library library;
    readBooksFromFile ( filename, library);
    int whatToDo = 0;

    if ( argc > 1 ) {
        whatToDo = std::atoi(argv[1]);
    }
    if ( whatToDo == 0 ) {
        cout << "Number of books in library is : " << library.getnumBooks() << endl;
    }
    else if ( whatToDo == 1 ) {
        LibraryBook *oneBook = library.getBook(4);
        cout << "Book no. 4 is ";
        oneBook->book.printBook();
    }
    else if ( whatToDo == 2 ) {
        library.printBooksOfOneGenre("Novel");
    }
    else if ( whatToDo == 3 ) {
        library.printAllBooks();
    }
    else if ( whatToDo == 4 ) {
        LibraryBook *oneBook = library.getBook(4);
        library.moveToFront(oneBook);
        library.printAllBooks();
    }
    else if ( whatToDo == 5 ) {
        Library secondLibrary(library);
        secondLibrary.printAllBooks();
    }
    else {
        cout << "Please provide an argument between 0 and 5\n";
    }
}
