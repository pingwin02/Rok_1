#include "library.h"

Library::Library() {
	std::cout << "\nKonstruktor bezparametrowy Library " << this << std::endl;
	array = nullptr;
	size = 0;
}

Library::Library(std::size_t size) 
	: size{ size }, array{ new Book[size] } {
	std::cout << "\nKonstruktor Library(" << size << ")" << std::endl;
}

Library::Library(std::initializer_list<Book> list)
	: size(list.size()), array{new Book[list.size()] } {
	std::size_t i = 0;
	for (Book b : list)
	{
		array[i] = b;
		i++;
	}
}

Library::Library(const Library& orig)
	: size(orig.size), array{new Book[orig.size]} {

	std::cout << "\nKonstruktor kopiujacy Library\n";
	for (std::size_t i = 0; i < size; i++)
		array[i] = orig.array[i];

}

Library::Library(Library&& orig) {

	std::cout << "\nKonstruktor przenoszacy Library\n";
	array = orig.array;
	size = orig.size;
	orig.array = nullptr;
	orig.size = 0;
}

Library& Library::operator=(const Library& right) {

	std::cout << "\nkopiujacy operator przypisania Library\n";
	Library temp = right;
	std::swap(array, temp.array);
	std::swap(size, temp.size);
	return *this;
}

Library& Library::operator=(Library&& right) {
	
	std::cout << "\nprzenoszacy operator przypisania Library\n";
	std::swap(array, right.array);
	std::swap(size, right.size);
	return *this;
}

Book& Library::operator[](std::size_t index) {
	return array[index];
}

const Book& Library::operator[](std::size_t index) const {
	return array[index];
}

std::size_t Library::GetSize() const {
	return size;
}

Library::~Library() {
	if (array != nullptr) {
		std::cout << "\ndestruktor Library " << array << std::endl;
		delete[] array;
	}
}

std::ostream& operator<<(std::ostream& ostr, const Library& lib) {
	ostr << "Library{";
	for (std::size_t i = 0; i < lib.GetSize(); i++)
	{
		if (i > 0)
			ostr << ',';
		ostr << lib[i];
	}
	ostr << '}';
	return ostr;
}
