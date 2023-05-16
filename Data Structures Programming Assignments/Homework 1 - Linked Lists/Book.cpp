#include <iostream>
#include "Book.h"


Book::Book()
{
    Year = 0;
}

Book::Book(string title, string author, string publisher, string genre, int year) : Title(title), Author(author), Publisher(publisher), Genre(genre), Year(year)  
{}

string Book::getTitle() const
{
    return Title;
}
void Book::setTitle(const string title)
{
    Title = title;
}

string Book::getAuthor() const
{
    return Author;
}
void Book::setAuthor(const string author)
{
    Author = author;
}

string Book::getPublisher() const
{	
    return Publisher;
}
void Book::setPublisher(const string publisher)
{
    Publisher = publisher;
}


string Book::getGenre() const
{	
    return Genre;
}
void Book::setGenre(const string genre)
{
    Genre = genre;
}

int Book::getYear() const
{
    return Year;
}
void Book::setYear(const int year)
{
    Year = year;
}

void Book::printBook () const
{
    cout << "Book: " << Title << ", " << Author << ", " << Publisher << ", " << Genre << ", " << Year << endl;
}
