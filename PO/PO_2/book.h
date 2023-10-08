#ifndef book_h

#define book_h

#include <string> 
#include <iostream>


class Book {
private:
	std::string author, title;
public:
	Book();
	Book(const std::string& author, const std::string& title);
	Book(std::string&& author, std::string&& title);
	Book(const Book& other);
	Book(Book&& other);

	std::string GetAuthor() const;
	std::string GetTitle() const;

	void SetAuthor(const std::string& author);
	void SetTitle(const std::string& title);
	void SetAuthor(std::string&& author);
	void SetTitle(std::string&& title);

	Book* operator=(const Book& right);
	Book* operator=(Book&& right);

	~Book();
};

std::ostream& operator<<(std::ostream& ostr, const Book& b);

#endif