#ifndef LLC_H
#define LLC_H

#include <string>
#include <iostream>
using namespace std;

template <typename T>
struct Node {
	T data;
	Node<T> *next;
	Node(){this->next = NULL;}
	Node(T val) {this->data = val; this->next = NULL;}
};

template <typename T>
class LLC {

public:

LLC() {
	this->_head = new Node<T>();
	this->_tail = new Node<T>();
	this->_head->next = this->_tail;
}

LLC(const LLC &obj) {
	this->cp(obj);
}

~LLC() {
	Node<T> *a = this->_head;
	Node<T> *b = this->_head->next;
	int i = 0;
	while (b) {
		delete a;
		a = b;
		b = b->next;
		i++;
	}
	delete a;
}

bool contains(const T &obj) {
	Node<T> *temp = this->_head->next;
	while (temp != this->_tail) {
		if (temp->data == obj)
			return true;
		temp = temp->next;
	}
	return false;
}

bool insert(const T &obj) {
	Node<T> *temp = this->_head;
	while (temp->next != this->_tail) {
		temp = temp->next;
	}
	Node<T> *n = new Node<T>(obj);
	n->next = this->_tail;
	temp->next = n;
	this->num++;
	return true;
}

void remove(const T &obj) {
	Node<T> *temp = this->_head;
	while (temp->next != this->_tail) {
		if (obj == temp->next->data) {
			Node<T> *n = temp->next;
			temp->next = temp->next->next;
			delete n;
			this->num--;
		}
		else {
			temp = temp->next;
		}
	}
}

void shuffle() {
	Node<T> *nodes [this->num];
	Node<T> *temp = this->_head->next;
	int i = 0;
	while (temp != this->_tail) {
		nodes[i] = temp;
		temp = temp->next;
		i++;
	}
	for (i = 0; i < this->num-1; i++) {
		int j = rand()%this->num;
		temp = nodes[i];
		nodes[i] = nodes[j];
		nodes[j] = temp;
	}
	for (i = 0; i < this->num-1; i++) {
		nodes[i]->next = nodes[i+1];
	}
	this->_head->next = nodes[0];
	nodes[this->num-1]->next = this->_tail;
	temp = this->_head;
}

LLC<T> operator+(const LLC<T> &obj) {
	LLC<T> retObj = LLC<T>(*this);
	Node<T> *temp = retObj._head;
	while (temp->next != retObj._tail) {
		temp = temp->next;
	}
	Node<T> *n = obj._head->next;
	while (n != obj._tail) {
		temp->next = new Node<T>(n->data);
		temp = temp->next;
		n = n->next;
	}
	temp->next = retObj._tail;
	retObj.num += obj.num;
	temp = retObj._head;
	return retObj;
}

void operator+=(int p) {
	p %= this->num;
	if (p == 0) {return;}
	Node<T> *temp = this->_head;
	Node<T> *h = this->_head->next;
	int i = 0;
	while (temp->next != this->_tail) {
		if (i == p) {
			Node<T> *n = temp->next;
			temp->next = this->_tail;
			this->_head->next = n;
			temp = n;
			i++;
		}
		else {
			temp = temp->next;
			i++;
		}
	}
	cout << temp->data << endl;
	temp->next = h;
}

LLC<T>& operator=(const LLC<T> &obj) {
	this->~LLC<T>();
	this->cp(obj);
	return *this;
}

void join(LLC<T> *obj) {
	if (obj->num == 0 or this->_head == obj->_head) {return;}
	Node<T> *temp = this->_head;
	while (temp->next != this->_tail) {
		temp = temp->next;
	}
	temp->next = obj->_head->next;
	temp = temp->next;
	while (temp->next != obj->_tail) {
		temp = temp->next;
	}
	temp->next = this->_tail;
	obj->_head->next = obj->_tail;
	this->num += obj->num;
	obj->num = 0;
}

void head(int n) const{
	if (this->num == 0 or n == 0) {
		cout << "[]" << endl;
		return;
	}
	Node<T> *temp = this->_head->next;
	cout << "[" << temp->data;
	temp = temp->next;
	n--;
	while (n > 0 and temp != this->_tail) {
		cout << ", " << temp->data;
		temp = temp->next;
		n--;		
	}
	cout << "]" << endl;
}


T tail() const{
	Node<T> *temp = this->_head->next;
	if (temp == this->_tail) {
		cout << endl;
		return NULL;
	}
	while (temp->next != this->_tail) {
		temp = temp->next;
	}
	cout << temp->data << endl;
	return temp->data;
}

LLC<T> pop(int n) {
	if (n > this->num or n == 0) {
		return LLC<T>();
	}
	LLC<T> retObj = LLC<T>();
	Node<T> *temp = this->_head;
	retObj._head->next = temp->next;
	int i = 0;
	while (i < n) {
		temp = temp->next;
		i++;
	}
	this->_head->next = temp->next;
	temp->next = retObj._tail;
	this->num -= n;
	retObj.num = n;
	return retObj;
}

LLC<T> pop() {
	if (this->num == 0) {
		return LLC<T>();
	}
	LLC<T> retObj = LLC<T>();
	Node<T> *temp = this->_head->next;
	retObj._head->next = temp;
	this->_head->next = temp->next;
	temp->next = retObj._tail;
	this->num--;
	retObj.num = 1;
	return retObj;
}


friend ostream& operator<<(ostream &os, const LLC<T> &obj) {
	obj.head(obj.num);
	return os;
}

int len() {
	return this->num;
}

void cp(const LLC<T> &obj) {
	Node<T> *curr = new Node<T>();
	this->_head = curr;
	Node<T> *temp = obj._head->next;
	while (temp != NULL) {
		Node<T> *n = new Node<T>(temp->data);
		curr->next = n;
		curr = curr->next;
		temp = temp->next;
	}
	this->_tail = curr;
	this->num = obj.num;	
}
Node<T> *_head = NULL;
Node<T> *_tail = NULL;
int num = 0;
};
#endif
