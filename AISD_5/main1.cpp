#include <iostream>
#include <string>

#define SALT 10789 
#define ARRAY_SIZE 10007

using namespace std;

struct Data {
	string key;
	int value = 1;
	Data* next = nullptr;
};


unsigned int h(string word) {

	unsigned int hash = SALT;

	for (unsigned int i = 0; i < word.length(); i++) {
		hash += SALT * word[i];
	}

	hash %= ARRAY_SIZE;

	return hash;
}

void addNode(Data*& head, string& word) {

	if (head == nullptr) {
		Data* newNode = new Data;
		newNode->key = word;
		head = newNode;
	}
	else {
		Data* cur = head;
		while (cur->key != word) {
			if (cur->next == nullptr) {
				Data* newNode = new Data;
				newNode->key = word;
				cur->next = newNode;
				return;
			}
			cur = cur->next;
		}
		cur->value++;
	}


}

void removeNode(Data*& head, string& word) {

	if (head != nullptr) {
		if (head->key == word) {
			Data* temp = head->next;
			delete head;
			head = temp;
		}
		else {
			Data* cur = head;
			while (cur->next != nullptr) {
				if (cur->next->key == word) {
					Data* temp = cur->next->next;
					delete cur->next;
					cur->next = temp;
					return;
				}
				cur = cur->next;
			}
		}
	}
}

int findNode(Data* head, string& word) {

	if (head != nullptr) {
		Data* cur = head;
		if (head->key == word) {
			return head->value;
		}
		else {
			while (cur->key != word) {
				if (cur->next == nullptr) {
					return 0;
				}
				cur = cur->next;
			}
			return cur->value;
		}
	}

	return 0;
}

void hashInsert(Data** arr, string word) {

	addNode(arr[h(word)],word);
}

void removeList(Data*& head) {
	if (head != nullptr) {
		Data* cur = head;
		while (head->next != nullptr) {
			cur = head->next;
			head->next = head->next->next;
			delete cur;
		}
		delete head;
		head = nullptr;
	}
}

void removeHashArray(Data** arr) {
	for (int i = 0; i < ARRAY_SIZE; i++) {
		removeList(arr[i]);
	}
	delete[] arr;
}

int main() {
	string command = "";

	Data** nOfWords = new Data*[ARRAY_SIZE];

	for (int i = 0; i < ARRAY_SIZE; i++) {
		nOfWords[i] = nullptr;
	}

	while (command != "q") {
		cin >> command;

		if (command[0] == '?') {
			command.erase(command.begin());
			printf("%d\n", findNode(nOfWords[h(command)], command));
		}
		else if (command[0] == '-') {
			command.erase(command.begin());
			removeNode(nOfWords[h(command)], command);
		}
		else if (command != "q") {
			hashInsert(nOfWords, command);
		}
	}

	removeHashArray(nOfWords);

	return 0;

}