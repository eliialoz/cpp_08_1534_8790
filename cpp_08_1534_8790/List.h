// List.h
#ifndef __LIST_H
#define __LIST_H

#include<iostream>
#include"Iterators.h"


//------------------------------------------------
// Class List - Arbitrary size Lists
// Permits insertion and removal only from the front of the List
//------------------------------------------------
template <typename T>
class List {
protected:
	//--------------------------------------------
	// inner class Node a single element for the Nodeed List
	//--------------------------------------------
	class Node {
	protected:
		T   _value;
		Node* _next;
	public:
		
		// constructor
		Node(int val, Node* nxt) : _value(val), _next(nxt) {}
		Node(const Node& src) : _value(src._value), _next(src._next) {}
		// data areas
		T&   value() { return _value; } // getter only
		Node* next() const { return _next; }  // getter
		void  next(Node* nxt) { _next = nxt; }   // setter

		
	}; //end of class Node

	
public:
	//Iterator:

	class Iterator :public ForwardIterator<Node, T>
	{
	public:
		using ForwardIterator<Node, T>::p;
		using ValueType = typename ForwardIterator<Node, T>::ValueType;
		using Pointer = typename ForwardIterator<Node, T>::Pointer;
		using Reference = typename ForwardIterator<Node, T>::Reference;

		Iterator(Pointer p) : ForwardIterator<Node, T>(p) {}
		void advance() { if (p) p = p->next(); };
		Reference operator*() const { return p->value(); }
		bool operator==(const Iterator& rhs) const { return p == rhs.p; }
		bool operator!=(const Iterator& rhs) const { return p != rhs.p; }
		Iterator& operator++() { advance(); return *this; }
	};

	Iterator begin() { return  Iterator(head); }
	Iterator end() { return  Iterator(nullptr); }


	// constructors
	List() : head(nullptr) {}
	List(const List&);
	List(List&&);
	~List();

	List& operator = (const List& other);
	List& operator = (List&& lst);


	void insert(T key);
	void remove(T key);
	void add(T value);
	T  firstElement() const;
	virtual bool search(const T&);
	bool isEmpty() const;
	void removeFirst();
	void clear();

	// operations
	friend std::ostream& operator <<(std::ostream& out, const List& lst)
	{
		for (List::Iterator p = lst.begin(); p != lst.end(); p++)
			out << *p << " ";

		return out;
	}

	friend std::istream& operator >>(std::istream& in, List& lst)
	{
		int current, previous;
		Node* p;

		in >> current;
		if (lst.head != nullptr)
			lst.clear();
		lst.head = new Node(current, nullptr);
		previous = current - 1;
		for (p = lst.head, in >> current; previous < current; p = p->next(), in >> current)
		{
			previous = current;
			p->next(new Node(current, nullptr));
		}

		return in;
	}
	 
private:
	friend void makeSet(List& lst)
	{
		Node* p, * q = nullptr;

		// loop to find each element
		for (q = lst.head, p = q->next(); p != nullptr; p = q->next())
		{
			if (q->value() == p->value())
			{
				// reassign the previous node
				q->next(p->next());
				p->next(nullptr);
				// recover memory used by the removed element
				delete p;
			}
			else
				q = p;
		}
	}

	friend List merge(List& lst1, List& lst2)
	{
		List lst;
		Node* p = lst1.head, * q = lst2.head, * l;
		bool isEndP, isEndQ;
		isEndP = isEndQ = false;

		// insert the first element:
		if (p->value() < q->value())
		{
			lst.add(p->value());
			p = p->next();
		}
		else
		{
			lst.add(q->value());
			q = q->next();
		}

		//copies the values ??of list 1 && list 2  to a new list
		//by ascending order, to avoids  from the new list access to list1 or list 2
		for (l = lst.head; p != nullptr || q != nullptr; l = l->next())
			if (!isEndP && (isEndQ || p->value() < q->value()))
			{
				l->next(new List::Node(p->value(), nullptr));
				//avoid comparison of null pointer
				if (!p->next())
					isEndP = true;
				p = p->next();
			}
			else if (!isEndQ)
			{
				l->next(new List<T>::Node(q->value(), nullptr));
				//avoid comparison of null pointer
				if (!q->next())
					isEndQ = true;
				q = q->next();
			}

		return lst;
	}

protected:
	// data field
	Node* head;
};


template <typename T>
List<T>::List(const List& other) {
	Node* src, * trg;
	if (other.head == nullptr)
		head = nullptr;
	else {
		head = new Node(other.head->value(), nullptr);
		if (head == nullptr)
			throw "failed in memory allocation";

		src = other.head;
		trg = head;
		while (src->next() != nullptr) {
			trg->next(new Node(src->next()->value(), nullptr));
			if (trg->next() == nullptr)
				throw "failed in memory allocation";
			src = src->next();
			trg = trg->next();
		}
	}
}

template <typename T>
List<T>::List(List&& other) : head(other.head)/* <- Keep the temp list is permanent*/ {
	// Avoid destructing it in the temporary object
	other.head = nullptr;
}

template <typename T>
List<T>::~List() {
	clear();
}

template <typename T>
List<T>& List<T>::operator=(const List& other)
{
	Node* src, * trg;
	if (other.head == nullptr)
		head = nullptr;
	else {
		head = new Node(other.head->value(), nullptr);
		if (head == nullptr)
			throw "failed in memory allocation";

		src = other.head;
		trg = head;
		while (src->next() != nullptr) {
			trg->next(new Node(src->next()->value(), nullptr));
			if (trg->next() == nullptr)
				throw "failed in memory allocation";
			src = src->next();
			trg = trg->next();
		}
	}
	return *this;
}

template <typename T>
List<T>& List<T>::operator=(List&& other)
{
	// Overrides the contents of the target 
	this->clear();
	// Keep the temp list is permanent
	head = other.head;
	// Avoid destructing it in the temporary object
	other.head = nullptr;

	return *this;
}

template <typename T>
void List<T>::clear() {
	// empty all elements from the List
	Node* next;
	for (Node* p = head; p != nullptr; p = next) {
		// delete the element pointed to by p
		next = p->next();
		p->next(nullptr);
		delete p;
	}
	// mark that the List contains no elements 
	head = nullptr;
}

template <typename T>
bool List<T>::isEmpty() const {
	// test to see if the List is empty
	// List is empty if the head pointer is null
	return head == nullptr;
}

template <typename T>
void List<T>::insert(T key)
{
	Node* q, * p;
	if (!search(key))
		if (isEmpty())
			add(key);
		else
		{
			q = p = head;

			for (p = head; p != nullptr && p->value() < key; p = p->next())
				q = p;

			if (p == q)
				add(key);
			else
			{
				p = new Node(key, q->next());
				q->next(p);
			}
		}
	else
		throw "the number already exsist.";
}

template <typename T>
void List<T>::remove(T key)
{
	Node* p, * q = nullptr;

	if (!search(key))
		throw "value not found\n";

	// loop to find each element
	for (p = head; key != p->value(); p = p->next())
		q = p;

	if (p == head)
		removeFirst();
	else
	{
		// reassign the previous node
		q->next(p->next());
		p->next(nullptr);
		// recover memory used by the removed element
		delete p;
	}
}

template <typename T>
void List<T>::add(T val) {
	//Add a new value to the front of a Nodeed List
	head = new Node(val, head);
	if (head == nullptr)
		throw "failed in memory allocation";
}

template <typename T>
T List<T>::firstElement() const {
	// return first value in List
	if (isEmpty())
		throw "the List is empty, no first Element";
	return head->value();
}

template <typename T>
bool List<T>::search(const T& val) {
	// loop to test each element
	for (auto it = begin(); it != end(); ++it)
		if (val == *it)
			return true;
	// not found
	return false;
}

template <typename T>
void List<T>::removeFirst() {
	// make sure there is a first element
	if (isEmpty())
		throw "the List is empty, no Elements to remove";
	// save pointer to the removed node
	Node* p = head;
	// reassign the first node
	head = p->next();
	p->next(nullptr);
	// recover memory used by the first element
	delete p;
}

#endif //__LIST_H