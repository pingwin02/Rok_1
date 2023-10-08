#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif


#include <string>
#include <iostream>

#define ALPHABET_SIZE 26

using namespace std;

struct TrieNode {
	TrieNode* child[ALPHABET_SIZE];
	string translation = "-";
};

int getId(char a) {
	return a - 'a';
}

TrieNode* getNewNode() {
	TrieNode* newNode = new TrieNode;

	for (int i = 0; i < ALPHABET_SIZE; i++) {
		newNode->child[i] = nullptr;
	}

	return newNode;
}

void insertNode(TrieNode*& root, string& word, string& translation) {
	TrieNode* cur = root;

	for (int i = 0; i < word.length(); i++) {
		int id = getId(word[i]);

		if (cur->child[id] == nullptr) {
			cur->child[id] = getNewNode();
		}

		cur = cur->child[id];
	}

	cur->translation = translation;
}

string searchNode(TrieNode*& root, string& key) {
	TrieNode* cur = root;

	for (int i = 0; i < key.length(); i++) {
		int id = getId(key[i]);

		if (cur->child[id] == nullptr) {
			return "-";
		}

		cur = cur->child[id];
	}

	return cur->translation;
}

void print(TrieNode*& root) {
	if (root->translation != "-") {
		cout << root->translation << endl;
	}
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (root->child[i] != nullptr) {
			print(root->child[i]);
		}
	}
}

void searchBeg(TrieNode*& root, string& key) {
	TrieNode* cur = root;

	for (int i = 0; i < key.length(); i++) {
		int id = getId(key[i]);
		if (cur->child[id] != nullptr) {
			cur = cur->child[id];
		}
		else {
			cout << "-" << endl;
			return;
		}
	}

	print(cur);

}

void deleteTrie(TrieNode*& root) {
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (root->child[i] != nullptr) {
			deleteTrie(root->child[i]);
			root->child[i] = nullptr;
		}
	}

	delete root;
}


int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	TrieNode* root = getNewNode();

	string command, word, translation;

	while (feof(stdin) == 0 && command != "q") {
		cin >> command >> word;

		if (command == "+") {
			cin >> translation;
			insertNode(root, word, translation);
		}
		else if (command == "?") {
			cout << searchNode(root, word) << endl;
		}
		else if (command == "*") {
			searchBeg(root, word);
		}
	}

	deleteTrie(root);

	return 0;

}