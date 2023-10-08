#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

#include "header.h"

int main() {
    char operation = 0;
    int mode = 1;

    DateAndNameVector v;

    while (operation != 'q') {
        scanf("%c", &operation);
        if (feof(stdin) != 0) {
            break;
        }
        switch (operation) {
        case '+': {
            int n;
            scanf("%d ", &n);
            while (n--) {
                v.addToVector(mode);
            }
            break;
        }
        case '-': {
            int m;
            scanf(" %d", &m);
            while (m--) {
                v.pop_front();
                heapify(v.getnumberList(), 1, v.getCount(), mode);
            }
            printf("\n");
            break;
        }
        case 'p': {
            for (int i = 0; i < v.getCount(); i++) {
                print(v[i]);
            }
            printf("\n");
            break;
        }
        case 'r': {
            if (mode == 1) {
                mode = -1;
            }
            else {
                mode = 1;
            }
            buildHeap(v.getnumberList(), v.getCount(), mode);
            break;
        }
        }
    }
    return 0;

}

DateAndName* add_element(DateAndName* list, DateAndName* prelast, char value) {

    DateAndName* x = new DateAndName;

    x->letter = value;
    x->next = nullptr;

    if (prelast != nullptr && prelast->next != nullptr) {
        prelast->next->next = x;
        prelast = prelast->next;
    }
    else {
        list->next = x;
        prelast = list;
    }

    return prelast;
}

void remove_all(DateAndName* list) {

    while (list->next != nullptr) {
        DateAndName* cur = list->next;
        list->next = list->next->next;
        delete cur;
    }

    delete list;
}

//1-wieksze -1-mniejsze 0-rowne
//mode 1 - alfabetycznie mode -1 - chronologicznie
int compare(DateAndName* left, DateAndName* right, int mode) {

    DateAndName* lefttemp = left->next;
    DateAndName* righttemp = right->next;

    if (mode == 1) {
        if (lefttemp->letter > righttemp->letter) {
            return 1;
        }
        if (lefttemp->letter == righttemp->letter) {
            while (lefttemp->next != nullptr && righttemp->next != nullptr) {
                if (lefttemp->letter > righttemp->letter) {
                    return 1;
                }
                if (lefttemp->letter < righttemp->letter) {
                    return -1;
                }
                else if (lefttemp->letter == righttemp->letter) {
                    lefttemp = lefttemp->next;
                    righttemp = righttemp->next;
                }
            }
            if (left->length > right->length) {
                return 1;
            }
            else if (left->length < right->length) {
                return -1;
            }
            return 0;
        }
        return -1;
    }

    if (mode == -1) {
        if (left->year > right->year) {
            return 1;
        }
        else if (left->year == right->year && left->month > right->month) {
            return 1;
        }
        else if (left->year == right->year && left->month == right->month && left->day > right->day) {
            return 1;
        }
        else if (left->year == right->year && left->month == right->month && left->day == right->day) {
            return 0;
        }
        return -1;
    }

    return 2;

}

DateAndName* copy(DateAndName* other) {

    DateAndName* newDateAndName = new DateAndName;
    DateAndName* cur1 = other->next;
    DateAndName* cur2 = newDateAndName;

    while (cur1 != nullptr) {
        DateAndName* addedLetter = new DateAndName;
        cur2->next = addedLetter;
        addedLetter->letter = cur1->letter;
        cur1 = cur1->next;
        cur2 = cur2->next;
    }
    newDateAndName->year = other->year;
    newDateAndName->month = other->month;
    newDateAndName->day = other->day;
    newDateAndName->length = other->length;

    return newDateAndName;
}

void print(const DateAndName* d) {
    if (d->day < 10) {
        printf("0%d-", d->day);
    }
    else {
        printf("%d-", d->day);
    }
    if (d->month < 10) {
        printf("0%d-", d->month);
    }
    else {
        printf("%d-", d->month);
    }
    if (d->year < 10) {
        printf("000%d ", d->year);
    }
    else if (d->year < 100) {
        printf("00%d ", d->year);
    }
    else if (d->year < 1000) {
        printf("0%d ", d->year);
    }
    else {
        printf("%d ", d->year);
    }
    DateAndName* cur = d->next;
    for (int j = 0; j < d->length; j++) {
        printf("%c", cur->letter);
        cur = cur->next;
    }
    printf("\n");
}

DateAndNameVector::DateAndNameVector() : size(1), count(0), list(new DateAndName* [size]) {}

int DateAndNameVector::getCount() const {
    return count;
}
DateAndName*& DateAndNameVector::operator[](const int index) {
    return list[index];
}
DateAndName** DateAndNameVector::getnumberList() const {
    return list;
}
void DateAndNameVector::reallocate(int newSize) {
    size = newSize;
    DateAndName** tempList = new DateAndName * [newSize];
    for (int i = 0; i < size; i++) {
        if (i < count) {
            tempList[i] = copy(list[i]);
            remove_all(list[i]);
        }
    }
    delete[] list;
    list = tempList;

}
void DateAndNameVector::addToVector(int mode) {
    DateAndName* prelast = nullptr;
    DateAndName* number = new DateAndName;
    int day, month, year;
    scanf("%d-%d-%d ", &day, &month, &year);
    number->day = day;
    number->month = month;
    number->year = year;
    int nameLength = 0;
    char a = 0;
    while (1) {
        scanf("%c", &a);
        if (a == '\n') {
            break;
        }
        prelast = add_element(number, prelast, a);
        nameLength++;
    }
    number->length = nameLength;
    push_back(number);
    heapInsert(list, number, count, mode);
}
void DateAndNameVector::push_back(DateAndName* number) {
    if (count == size) {
        reallocate(2 * size);
    }
    list[count] = number;
    count++;

}
void DateAndNameVector::pop_front() {
    if (count != 0) {
        print(list[0]);
        remove_all(list[0]);
        list[0] = list[count - 1];
        count--;
        if (count == 0) {
            resetVector();
        }
        else if (4 * count <= size)
            reallocate(size / 2);
    }
}

void DateAndNameVector::resetVector() {
    for (int i = 0; i < size; i++) {
        if (i < count)
            remove_all(list[i]);
    }
    delete[] list;

    size = 1;
    count = 0;
    list = new DateAndName * [size];
}

DateAndNameVector::~DateAndNameVector() {
    for (int i = 0; i < size; i++) {
        if (i < count)
            remove_all(list[i]);
    }
    delete[] list;
}


void heapify(DateAndName** tab, int i, int n, int mode) {

    int l = i * 2;
    int r = i * 2 + 1;

    DateAndName* temp;

    int maxps = i;

    if (l <= n && compare(tab[l - 1], tab[i - 1], mode) == -1) {
        maxps = l;
    }
    if (r <= n && compare(tab[r - 1], tab[maxps - 1], mode) == -1) {
        maxps = r;
    }
    if (maxps != i) {
        temp = tab[i - 1];
        tab[i - 1] = tab[maxps - 1];
        tab[maxps - 1] = temp;
        heapify(tab, maxps, n, mode);
    }

}

void buildHeap(DateAndName** tab, int n, int mode) {

    for (int i = n / 2; i > 0; i--) {
        heapify(tab, i, n, mode);
    }
}

void heapInsert(DateAndName** tab, DateAndName* newElement, int n, int mode) {
    int i = n;
    while (i > 1 && compare(tab[i / 2 - 1], newElement, mode) == 1) {
        tab[i - 1] = tab[i / 2 - 1];
        i = i / 2;
    }
    tab[i - 1] = newElement;
}