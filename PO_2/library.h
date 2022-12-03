#ifndef library_h

#define library_h

#include "book.h"

#include <initializer_list> 

class Library {
	Book* array;
	std::size_t size;
public:
	Library();
	Library(std::size_t size);
	Library(std::initializer_list<Book> list);
	Library(const Library& orig);
	Library(Library&& orig);
	Library& operator=(const Library& right);
	Library& operator=(Library&& right);
	Book& operator[](std::size_t index);
	const Book& operator[](std::size_t index) const;
	std::size_t GetSize() const; 
	~Library();
};

std::ostream& operator<<(std::ostream& ostr, const Library& lib);

#endif