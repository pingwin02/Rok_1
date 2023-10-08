#include "book.h"

Book::Book() {
	std::cout << "\nKonstruktor bezparametrowy Book " << this << std::endl;
}
Book::Book(const std::string& author, const std::string& title) {
	std::cout << "\nKonstruktor book l-ref(" << author << ", " << title << ")\n";
	this->author = author;
	this->title = title;
}
Book::Book(std::string&& author, std::string&& title) {
	std::cout << "\nKonstruktor book r-ref(" << author << ", " << title << ")\n";
	this->author = author;
	this->title = title;
}
Book::Book(const Book& other)
	: author(other.author), title(other.title) {
	std::cout << "\nKonstruktor book - kopiujacy\n";
}
Book::Book(Book&& other) {
	std::cout << "\nKonstruktor book - przenoszacy\n";
	this->author = other.author;
	this->title = other.title;
	other.author = "";
	other.title = "";
}
std::string Book::GetAuthor() const {
	return this->author;
}
std::string Book::GetTitle() const {
	return this->title;
}
void Book::SetAuthor(const std::string& author) {
	this->author = author;
}
void Book::SetTitle(const std::string& title) {
	this->title = title;
}
void Book::SetAuthor(std::string&& author) {
	this->author = author;
}
void Book::SetTitle(std::string&& title) {
	this->title = title;
}
Book* Book::operator=(const Book& right) {
	std::cout << "\nkopiujacy operator przypisania book\n";
	this->author = right.author;
	this->title = right.title;

	return this;
}
Book* Book::operator=(Book&& right) {
	std::cout << "\nprzenoszacy operator przypisania book\n";
	std::swap(this->author, right.author);
	std::swap(this->title, right.title);
	return this;
}
Book::~Book() {
	std::cout << "\ndestruktor Book " << this << std::endl;
}

std::ostream& operator<<(std::ostream& ostr, const Book& b) {
	ostr << "Book{" << b.GetAuthor() << ", " << b.GetTitle() << "}";
	return ostr;
}