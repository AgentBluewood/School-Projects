#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book {
private:
    string Title;
    string Author;
    string Publisher;
    string Genre;
    int Year;
    
public:
    Book();
    Book(string title, string author, string publisher, string genre, int year);
    
    string getTitle() const;
    void setTitle (const string title );
    
    string getAuthor() const;
    void setAuthor (const string artist);
    
    string getPublisher() const;
    void setPublisher (const string album);

    string getGenre() const;
    void setGenre (const string genre);
    
    int getYear() const;
    void setYear (const int year );
    
    void printBook() const;
};
#endif // BOOK_H
