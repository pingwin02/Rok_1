#pragma once

struct DateAndName {
    int day = 0;
    int month = 0;
    int year = 0;
    int length = 0;
    char letter = 'X';
    DateAndName* next = nullptr;
};
DateAndName* add_element(DateAndName* list, DateAndName* prelast, char value);
void remove_all(DateAndName* list);
int compare(DateAndName* left, DateAndName* right, int mode);
DateAndName* copy(DateAndName* other);
void print(const DateAndName* d);
class DateAndNameVector {
private:
    int size;
    int count;
    DateAndName** list;
public:
    DateAndNameVector();
    int getCount() const;
    DateAndName*& operator[](const int index);
    DateAndName** getnumberList() const;
    void reallocate(int newSize);
    void addToVector(int mode);
    void push_back(DateAndName* number);
    void pop_front();
    void resetVector();
    ~DateAndNameVector();
};
void heapify(DateAndName** tab, int i, int n, int mode);
void buildHeap(DateAndName** tab, int n, int mode);
void heapInsert(DateAndName** tab, DateAndName* newElement, int n, int mode);