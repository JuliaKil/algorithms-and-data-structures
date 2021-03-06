﻿#include "pch.h"
#include <iostream>
#include <fstream>

using namespace std;

struct Node {
	int data;
	Node* left;
	Node* right;
	Node(int d) {
		data = d;
		left = right = nullptr;
	}
	int balancefactor() {
		return right->height() - left->height();
	}
	int height() {
		if (this == nullptr)
			return 0;
		if (left->height() > right->height())
			return left->height() + 1;
		else
			return right->height() + 1;
	}
};

class AVL {
private:
	Node* head;
public:
	AVL() {
		head = nullptr;
	}
	void rotateright() {
		Node* fix = head->left->right;
		head->left->right = head;
		head = head->left;
		head->right->left = fix;	
	}
	void rotateleft() {
		Node* fix = head->right->left;
		head->right->left = head;
		head = head->right;
		head->left->right = fix;
	}
	void balance() {
		if (head->balancefactor() == 2) {
			if (head->right->balancefactor() < 0) {
				Node* fixhead = head;
				head = head->right;
				rotateright();
				fixhead->right = head;
				head = fixhead;
			}
			rotateleft();
		}
		if (head->balancefactor() == -2) {
			if (head->left->balancefactor() > 0) {
				Node* fixhead = head;
				head = head->left;
				rotateleft();
				fixhead->left = head;
				head = fixhead;
			}
			rotateright();
		}	
	}
	Node* findminp() {
		Node* fixhead = head;
		Node* prev = head;
		head = head->right;
		while (head->left->height() > 1)
			prev = head;
			head = head->left;
		head = fixhead;
		return prev;
	}
	int insert(int d) {
		if (head == nullptr) 
			head = new Node(d);
		else {
			Node* fixhead = head;
			while (true) {
				if (head->data > d)
					if (head->left == nullptr) {
						head->left = new Node(d);
						break;
					}
					else
						head = head->left;
				else
					if (head->right == nullptr) {
						head->right = new Node(d);
						break;
					}
					else
						head = head->right;
			}
			head = fixhead;
			balance();
		}
		return head->balancefactor();
	}
	bool search(int d) {
		if (head == nullptr)
			return false;
		Node* fixhead = head;
		while (head->height() > 1 && head->data != d) {
			if (head->data > d)
				head = head->left;
			else
				head = head->right;
		}
		if (head->data == d) {
			head = fixhead;
			return true;
		}
		else {
			head = fixhead;
			return false;
		}
	}
	int remove(int d) {
		if (head == nullptr)
			return false;
		Node* fixhead = head;
		Node* prev = nullptr;
		while (head->height() > 1 && head->data != d) {
			prev = head;
			if (head->data > d)
				head = head->left;
			else
				head = head->right;
		}
		if (head == prev->right) {
			if (head->left == nullptr && head->right == nullptr)
				prev->right = nullptr;
			else if (head->left == nullptr) {
				prev->right = head->right;
			}
			else if (head->right == nullptr) {
				prev->right = head->left;
			}
			else {
				Node* prevm = findminp();
				prev->right = prevm->left;
				prevm->left = nullptr;
				prev->right->left = head->left;
				prev->right->right = head->right;
			}
		}
		if (head == prev->left) {
			if (head->left == nullptr && head->right == nullptr)
				prev->left = nullptr;
			else if (head->left == nullptr) {
				prev->left = head->right;
			}
			else if (head->right == nullptr) {
				prev->left = head->left;
			}
			else {
				Node* prevm = findminp();
				prev->left = prevm->left;
				prevm->left = nullptr;
				prev->left->left = head->left;
				prev->left->right = head->right;
			}
		}
		head = fixhead;
		balance();
		return head->balancefactor();
	}
};

int main()
{
	ifstream fin;
	fin.open("in.txt");
	ofstream fout;
	fout.open("out.txt");
	int numberOfCommands, element;
	char command;
	fin >> numberOfCommands;
	AVL tree = AVL();
	for (int i = 0; i < numberOfCommands; i++) {
		fin >> command;
		switch (command) {
		case '+':
			fin >> element;
			fout << tree.insert(element) << endl;
			break;
		case '-':
			fin >> element;
			fout << tree.remove(element) << endl;
			break;
		case '?':
			fin >> element;
			fout << tree.search(element) << endl;
			break;
		}
	}
}