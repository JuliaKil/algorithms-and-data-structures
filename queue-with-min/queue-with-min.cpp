#include "pch.h"
#include <iostream>
#include <fstream>

using namespace std;

struct NodeQ {
	int data;
	NodeQ *next;
};

struct NodeD {
	int data;
	NodeD *next;
	NodeD *prev;
};

//Реализация очереди с минимумом с помощью двухсторонней очереди

class Deque {
	NodeD *first;
	NodeD *last;
public:
	Deque() {
		first = last = NULL;
	}

	void addRight(int newElement) {
		if (first == NULL) {
			first = new NodeD;
			first->next = NULL;
			first->prev = NULL;
			first->data = newElement;
			last = first;
		}
		else {
			last->next = new NodeD;
			last->next->prev = last;
			last = last->next;
			last->data = newElement;
			last->next = NULL;
		}
	}

	void deleteRight() {
		if (last == first)
			last = first = NULL;
		else {
			last = last->prev;
			last->next = NULL;
		}
	}

	void deleteLeft() {
		if (last == first)
			last = first = NULL;
		else {
			first = first->next;
			first->prev = NULL;
		}
	}

	int getlast() {
		if (last == NULL)
			return -1000000001;
		else
			return last->data;
	}

	int getfirst() {
		return first->data;
	}
};

class Queue {
	NodeQ *first;
	NodeQ *last;
	Deque deque;
public:
	Queue() {
		last = first = NULL;
		deque = Deque();
	}

	void add(int newElement) {
		if (first == NULL) { //добавляем новый элемент в очередь
			first = new NodeQ;
			first->next = NULL;
			first->data = newElement;
			last = first;
		}
		else {
			last->next = new NodeQ;
			last = last->next;
			last->data = newElement;
			last->next = NULL;
		}
		while (deque.getlast() > newElement) //добавляем новый элемент в дек, если он больше последнего эл-та дека
			deque.deleteRight();			//иначе удаляем элементы из дека до тех пор, пока последний не станет меньше нового
		deque.addRight(newElement);
	}

	void remove() {
		if (first->data == deque.getfirst()) { //если первый эл-т - минимум, то убираем его из начала дека и очереди, иначе только из очереди
			deque.deleteLeft();
		}
		first = first->next;
	}

	int getmin() {
		return deque.getfirst(); // минимум - первый элемент дека
	}

};

int main()
{
	ifstream fin;
	fin.open("in.txt");
	ofstream fout;
	fout.open("out.txt");
	Queue Q = Queue();
	int numberOfCommands, newElement;
	char command;
	fin >> numberOfCommands;
	for (int i = 0; i < numberOfCommands; i++) {
		fin >> command;
		switch (command) {
		case '+':
			fin >> newElement;
			Q.add(newElement);
			break;
		case '-':
			Q.remove();
			break;
		case '?':
			fout << Q.getmin() << endl;
			break;
		}
	}
}
