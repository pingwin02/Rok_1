/*#include <iostream>
#include <string>

#define SALT 10789 
#define ARRAY_SIZE 100003

using namespace std;

struct Data {
	string key;
	int value = -1;
};


int h(string word, int i) {

	unsigned int hash = SALT;

	for (int i = 0; i < word.length(); i++) {
		word[i] = word[i];
		hash += hash * word[i];
	}

	hash = (hash + i) % ARRAY_SIZE;

	return hash;
}

void hashInsert(Data* arr, string word) {
	int i = 0;
	int hash = h(word, i);
	while (arr[hash].value != -1 && arr[hash].key != word) {
		i++;
		hash = h(word, i);
		if (i >= ARRAY_SIZE) {
			cout << "ARRAY IS FULL" << endl;
			return;
		}
	}
	arr[hash].key = word;
	arr[hash].value++;
}

int hashFind(Data* arr, string word, int mode) {
	int i = 0;
	int hash = h(word, i);
	while (arr[hash].key != word) {
		if (arr[hash].value == -1) return 0;
		i++;
		hash = h(word, i);
	}
	if (mode) {//remove
		arr[hash].key = "";
		arr[hash].value = -1;
	}
	return (arr[hash].value + 1);
}

int main() {

	string command = "";

	Data* nOfWords = new Data [ARRAY_SIZE];

	while (command != "q") {
		cin >> command;

		if (command[0] == '?') {
			command.erase(command.begin());
			printf("%d\n", hashFind(nOfWords, command, 0));
		}
		else if (command[0] == '-') {
			command.erase(command.begin());
			hashFind(nOfWords, command, 1);
		}
		else if (command != "q") {
			hashInsert(nOfWords, command);
		}
	}

	delete[] nOfWords;

}*/