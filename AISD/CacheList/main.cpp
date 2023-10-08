#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)

#define PRINTALL -3

#define ADD_BEFORE -1
#define ADD_AFTER 1

#define N_OF_ITERATORS 12
#define BEGINING N_OF_ITERATORS - 2
#define ENDING N_OF_ITERATORS -1

#define COMMAND_SIZE 10

#include <cstdio>
#include <iostream>

//element of list
struct Element {
	unsigned long long int number = 0;
	//pointer to next element
	struct Element* next = nullptr;
	//pointer to previous element
	struct Element* prev = nullptr;
};

int handle_input(char* command) {

	int x;

	if (!strcmp(command, "BEG")) {
		x = BEGINING;
	}
	else if (!strcmp(command, "END")) {
		x = ENDING;
	}
	else if (!strcmp(command, "ALL")) {
		x = PRINTALL;
	}
	else {
		x = atoi(command);
	}

	return x;
}

//verify if iterator is pointing to begining, ending or to other point in the list
//x - number of iterator
int verify_iterator(Element** iterators, int x) {

	if (iterators[x] == nullptr) {
		return -1;
	}
	if (iterators[x] == iterators[BEGINING]) {
		x = BEGINING;
	}
	if (iterators[x] == iterators[ENDING]) {
		x = ENDING;
	}

	return x;
}

//add elements to list
//x - number of iterator; y - number to add; mode - add before/after
int add_element(Element* list, Element** iterators, int x, unsigned long long int y, int mode) {

	Element* temp = new Element;
	Element* cur = iterators[x];

	//check if input is correct
	if (x > N_OF_ITERATORS || x < 0) return -1;

	temp->number = y;
	temp->next = nullptr;
	temp->prev = nullptr;

	//check if list isn't created yet - fixed BEG iterator is empty
	if (iterators[BEGINING] == nullptr) {
		list->next = temp;
		iterators[BEGINING] = temp;
		iterators[ENDING] = temp;
		return 0;
	}

	x = verify_iterator(iterators, x);
	//if function return -1 end program, because iterator point to nothing
	if (x == -1) {
		return -1;
	}
	//add before the element
	if (mode == ADD_BEFORE) {
		if (x == BEGINING || cur->prev == nullptr) {
			cur = list->next;
			list->next = temp;
			temp->next = cur;
			cur->prev = temp;
			iterators[BEGINING] = temp;
		}
		else {
			cur->prev->next = temp;
			temp->prev = cur->prev;
			temp->next = cur;
			cur->prev = temp;
		}
	}
	//add after the element
	else if (mode == ADD_AFTER) {
		if (x == ENDING || cur->next == nullptr) {
			cur = iterators[ENDING];
			cur->next = temp;
			temp->prev = cur;
			iterators[ENDING] = temp;
		}
		else {
			cur->next->prev = temp;
			temp->next = cur->next;
			temp->prev = cur;
			cur->next = temp;
		}
	}

	return 1;

}

//print all numbers in the list
void print_all(Element* list) {

	Element* cur = list->next;

	if (cur != nullptr) {
		printf("%llu", cur->number);

		while (cur != nullptr && cur->next != nullptr) {
			cur = cur->next;
			printf(" %llu", cur->number);
		}

		printf("\n");
	}
}

//print number on where iterator points
//p - number of iterator
void print_element(Element** iterators, int p) {
	if (iterators[p] != nullptr)
	printf("%llu\n", iterators[p]->number);
}

//add new iterator
//x - number of iterator; y - operation BEG/END/copy other iterator
int add_iterator(Element** iterators, int x, int y)
{

    if (y > N_OF_ITERATORS - 1 || y < 0) return 0;
    
    if (y == BEGINING) {
        iterators[x] = iterators[BEGINING];
    }
    else if (y == ENDING) {
        iterators[x] = iterators[ENDING];
    }
    else if (iterators[y] != nullptr) {
        iterators[x] = iterators[y];
    }

    return 0;
}

//move iterator
//x - number of iterator; command - operation
int move_iterator(Element** iterators, int x, char command) {

	if (iterators[x] == nullptr) {
		return 0;
	}

	switch (command) {
		//move forward
	case '+': {
		if (iterators[x] == iterators[ENDING]) break;
		if (iterators[x]->next != nullptr)
		iterators[x] = iterators[x]->next; 
		break;
	}
		//move backward
	case '-': {
		if (iterators[x] == iterators[BEGINING]) break;
		if (iterators[x]->prev != nullptr)
		iterators[x] = iterators[x]->prev; 
		break; 
	}
	}

	return 0;
}
//remove an element from the list
//x - number of iterator
int remove_element(Element* list, Element** iterators, int x) {

	Element* cur = iterators[x];
	Element* moved_iterator = nullptr;

	int pos = verify_iterator(iterators, x);
	//if iterator points to nothing end program
	if (pos == -1) {
		return -1;
	}
	//create temp iterator to other element (next/previous) while removing element
	if (cur != iterators[ENDING] && cur->next != nullptr)
		moved_iterator = cur->next;
	else if (cur->prev != nullptr) {
		moved_iterator = cur->prev;
	}
	//save changes to all iterators pointing to this element
	if (x != BEGINING && x != ENDING) {
		for (int i = 0; i < N_OF_ITERATORS - 2; i++) {
			if (iterators[i] == cur) {
				iterators[i] = moved_iterator;
			}
		}
	}
	//if deleted element is at begining/ending change fixed iterator
	if (pos == BEGINING && cur->next != nullptr) {
		cur = cur->next;
		delete cur->prev;
		list->next = cur;
		cur->prev = nullptr;
		iterators[BEGINING] = cur;
	}
	else if (pos == ENDING && cur->prev != nullptr) {
		cur = cur->prev;
		delete cur->next;
		cur->next = nullptr;
		iterators[ENDING] = cur;
	}
	//if all list cleared -> the element is the last one on the list -> clear all list and iterators
	else if (cur->prev == nullptr) {
		list->next = nullptr;
		for (int i = 0; i < N_OF_ITERATORS; i++) {
			iterators[i] = nullptr;
		}
		delete cur;
	}
	else {
		if (cur->prev->next != nullptr && cur->next != nullptr)
		cur->prev->next = cur->next;
		if (cur->next != nullptr && cur->next->prev != nullptr)
		cur->next->prev = cur->prev;
		delete cur;
	}

	return 0;
	

}
//remove all list at the end of the program to prevent memory leaks
void remove_all(Element* list) {

	while (list->next != nullptr) {
		Element* cur = list->next;
		list->next = list->next->next;
		delete cur;
	}
}

int main() {

	Element list;
	char command[COMMAND_SIZE] = {};
	int x = 0, y = 0, p = 0;
	unsigned long long int number = 0;
	//array of iterators - last 2 are fixed to BEGINING and ENDING of the list
	Element* iterators[N_OF_ITERATORS] = {};

	while (1) {
		scanf("%9s", command);
		if (feof(stdin) != 0)
		{
			break;
		}
		else if (!strcmp(command,"I")) {
			int temp;
			scanf("%d", &temp);
			continue;
		}
		else if (!strcmp(command, "i")) {
			scanf("%d", &x);
			scanf("%9s", command);
			y = handle_input(command);
			add_iterator(iterators, x, y);
		}
		else if (!strcmp(command, "+") || !strcmp(command, "-")) {
			scanf("%d", &x);
			move_iterator(iterators, x, *command);
		}
		else if (!strcmp(command,".A")) {
			scanf("%9s", command);
			x = handle_input(command);
			scanf("%llu", &number);
			add_element(&list, iterators, x, number, ADD_BEFORE);
		}
		else if (!strcmp(command, "A.")) {
			scanf("%9s", command);
			x = handle_input(command);
			scanf("%llu", &number);
			add_element(&list, iterators, x, number, ADD_AFTER);
		}
		else if (!strcmp(command,"P")) {
			scanf("%9s", command);
			p = handle_input(command);
			if (p == PRINTALL) {
				print_all(&list);
				continue;
			}
			print_element(iterators, p);
		}
		else if (!strcmp(command, "R")) {
			scanf("%9s", command);
			x = handle_input(command);
			remove_element(&list, iterators, x);
		}

	}

	remove_all(&list);

	return 0;
}