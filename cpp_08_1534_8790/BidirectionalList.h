#pragma once

#include <iostream>
#include "List.h"
#include "Iterators.h"

//------------------------------------------------
// Class BidirectionalList - Arbitrary size Lists
//------------------------------------------------
template <typename T>
class BidirectionalList : public List<T>
{
	using typename List<T>::Node;

protected:
	//--------------------------------------------
	// inner class Node a single element for the Nodeed List
	//--------------------------------------------
	class BidirectionalNode : public List<T>::Node
	{
		BidirectionalNode* _prev;
	public:
		// constructor
		BidirectionalNode(int val, BidirectionalNode* nxt, BidirectionalNode* prv) : Node::Node(val, nxt), _prev(prv) {}
		BidirectionalNode(const BidirectionalNode& src) : Node::Node(src), _prev(src._prev) {}
		// data areas
		BidirectionalNode* prev() const { return _prev; }  // getter _prev
		void  prev(BidirectionalNode* prv) { _prev = prv; }   // setter
	};

	using List<T>::head;
	BidirectionalNode* tail;

public:
	class Iterator : public BidirectionalIterator<BidirectionalNode, T>
	{
	public: 
		using BidirectionalIterator<BidirectionalNode, T>::p;
		using ValueType = typename BidirectionalIterator<BidirectionalNode, T>::ValueType;
		using Pointer = typename BidirectionalIterator<BidirectionalNode, T>::Pointer;
		using Reference = typename BidirectionalIterator<BidirectionalNode, T>::Reference;

		Iterator(Pointer p) : BidirectionalIterator<BidirectionalNode, T>(p) {}
		void advanceBack() { if (p) p = p->prev(); }
		void advance() { if (p) p = (BidirectionalNode*)p->next(); }
		Reference operator*() const { return p->value(); }
		bool operator==(const Iterator& rhs) const { return p == rhs.p; }
		bool operator!=(const Iterator& rhs) const { return p != rhs.p; }
		Iterator& operator++() { advance(); return *this; }
		Iterator& operator--() { advanceBack(); return *this; }
	};

	using List<T>::begin;
	using List<T>::end;
	/*Iterator begin() { return  Iterator(head); }
	Iterator end() { return  Iterator(nullptr); }*/
	Iterator rbegin() { return  Iterator(nullptr); }
	Iterator rend() { return  Iterator(tail); }

	// constructors
	BidirectionalList() : List<T>::List(), tail(nullptr) {}
	BidirectionalList(const BidirectionalList&);
	BidirectionalList(BidirectionalList&&);
	~BidirectionalList();

	BidirectionalList& operator = (const BidirectionalList& other);
	BidirectionalList& operator = (BidirectionalList&& other);

	void add(T);
	void addToEnd(int val);
	void removeFirst();
	void clear();
	using List<T>::isEmpty;
	using List<T>::search;

};

template<typename T>
BidirectionalList<T>::BidirectionalList(const BidirectionalList& other)
{
	BidirectionalNode* src, * trg;
	if (other.head == nullptr)
		BidirectionalList();
	else {
		head = new BidirectionalNode(other.head->value(), nullptr, nullptr);
		if (head == nullptr)
			throw "failed in memory allocation";

		src = other.head;
		trg = head;
		while (src->next() != nullptr)
		{
			trg->next(new BidirectionalNode(src->next()->value(), nullptr, trg));
			if (trg->next() == nullptr)
				throw "failed in memory allocation";
			src = src->next();
			trg = trg->next();
		}
		tail = trg;
	}
}

template<typename T>
BidirectionalList<T>::BidirectionalList(BidirectionalList&& other) : List<T>::List((List<T>)other), tail(other.tail)
{
	// Avoid destructing it in the temporary object
	other.tail = nullptr;
}

template<typename T>
BidirectionalList<T>::~BidirectionalList()
{
	clear();
}

template<typename T>
BidirectionalList<T>& BidirectionalList<T>::operator=(const BidirectionalList& other)
{
	if (this != &other)
	{
		BidirectionalNode* src, * trg;
		if (other.head == nullptr)
			BidirectionalList();
		else {
			head = new BidirectionalNode(other.head->value(), nullptr, nullptr);
			if (head == nullptr)
				throw "failed in memory allocation";

			src = other.head;
			trg = head;
			while (src->next() != nullptr) {
				trg->next(new BidirectionalNode(src->next()->value(), nullptr, trg));
				if (trg->next() == nullptr)
					throw "failed in memory allocation";
				src = src->next();
				trg = trg->next();
			}

			tail = trg;
		}
	}
	return *this;
}

template<typename T>
BidirectionalList<T>& BidirectionalList<T>::operator=(BidirectionalList&& other)
{
	if (this != &other)
	{
		// Overrides the contents of the target 
		clear();
		// Keep the temp list is permanent
		head = other.head;
		tail = other.tail;
		// Avoid destructing it in the temporary object
		other.head = nullptr;
		other.tail = nullptr;
	}
		return *this;
}

template<typename T>
void BidirectionalList<T>::add(T val)
{
	if (!isEmpty())
	{
		// update the prev field to point to the new Node
		((BidirectionalNode*)head)->prev(new BidirectionalNode(val, ((BidirectionalNode*)head), nullptr));

		if (((BidirectionalNode*)head)->prev() == nullptr)
			throw "failed in memory allocation";

		//Add a new value to the front of a Nodeed List
		head = ((BidirectionalNode*)head)->prev();
	}
	else
	{
		head = new BidirectionalNode(val, nullptr, nullptr);
		tail = ((BidirectionalNode*)head);
	}
}

template<typename T>
void BidirectionalList<T>::addToEnd(int val)
{
	if (isEmpty())
		add(val);
	else
	{
		tail->next(new BidirectionalNode(val, nullptr,tail));
		tail = (BidirectionalNode*)tail->next();
	}
}

template<typename T>
void BidirectionalList<T>::removeFirst()
{
	// make sure there is a first element
	if (isEmpty())
		throw "the List is empty, no Elements to remove";
	// save pointer to the removed node
	BidirectionalNode* p = ((BidirectionalNode*)head);
	// reassign the first node:
	head = p->next();
	((BidirectionalNode*)head)->prev(nullptr);
	// avoid dangling pointer
	p->next(nullptr);
	// recover memory used by the first element
	delete p;

	if (isEmpty())
		// avoid dangling pointer
		tail = nullptr;
}

template<typename T>
void BidirectionalList<T>::clear()
{
	// empty all elements from the List
	BidirectionalNode* next;
	for (BidirectionalNode* p = ((BidirectionalNode*)head); p != nullptr; p = next) {
		// delete the element pointed to by p
		next = (BidirectionalNode*)p->next();
		p->next(nullptr);
		p->prev(nullptr);
		delete p;
	}
	// mark that the List contains no elements 
	head = nullptr;
	tail = nullptr;
}
