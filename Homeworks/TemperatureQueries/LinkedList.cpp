# include <iostream>
# include <string>
# include <sstream>
# include "LinkedList.h"
# include "Node.h"

using std::string, std::ostream;

LinkedList::LinkedList() : head(nullptr), tail(nullptr) {

}

LinkedList::~LinkedList() {
	Node* current = head;
	while (current) {
		Node* next = current->next;
		delete current;
		current = next;
	}
}

LinkedList::LinkedList(const LinkedList& source) : head(source.head), tail(source.tail) {

}

LinkedList& LinkedList::operator=(const LinkedList& source) {
	this->head = source.head;
	this->tail = source.tail;
	return *this;
}

void LinkedList::insert(string location, int year, int month, double temperature) {
	Node* newNode = new Node(location, year, month, temperature);
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
	}
	else if ((*newNode) < (*head)) {
		newNode->next = head;
		head = newNode;
	}
	else if (head == tail) {
		if ((*newNode) < (*head)) {
			head = newNode;
			newNode->next = tail;
		}
		else {
			tail = newNode;
			head->next = tail;
		}
	}
	else {
		Node* currNode = head->next;
		Node* prevNode = head;
		while (currNode) {
			if ((*newNode) < (*currNode)) {
				prevNode->next = newNode;
				newNode->next = currNode;
				break;
			}
			else if (currNode == tail) {
				tail = newNode;
				currNode->next = tail;
				break;
			}
			prevNode = currNode;
			currNode = currNode->next;
		}
	}
}

void LinkedList::clear() {
	delete this;
}

Node* LinkedList::getHead() const {
	return head;
}

string LinkedList::print() const {
	string outputString;
	Node* currentNode = head;

	while (currentNode) {
		std::ostringstream oss;
		outputString += currentNode->data.id + " " + std::to_string(currentNode->data.year) + " " + std::to_string(currentNode->data.month) + " ";
		oss << currentNode->data.temperature;	
		outputString += oss.str() + "\n";	
		currentNode = currentNode->next;
	}

	return outputString;
}

ostream& operator<<(ostream& os, const LinkedList& ll) {
	os << ll.print();
	return os;
}
