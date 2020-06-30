#ifndef __ITERATORS_H
#define __ITERATORS_H

template <typename T, typename R>
class ForwardIterator {
protected:
	T* p;
public:
	using ValueType = R;
	using Pointer = T*;
	using Reference = R&;
	
	ForwardIterator(Pointer p) : p(p) {}
	virtual void advance() = 0;
	Reference operator*() const { return *p; }
	bool operator==(const ForwardIterator& rhs) const { return p == rhs.p; }
	bool operator!=(const ForwardIterator& rhs) const { return p != rhs.p; }
	ForwardIterator& operator++() { advance(); return *this; }
};

template <typename T, typename R>
class BidirectionalIterator : public ForwardIterator<T, R> {
public:
	using ForwardIterator<T, R>::p;
	using ValueType = typename ForwardIterator<T, R>::ValueType;
	using Pointer = typename ForwardIterator<T, R>::Pointer;
	using Reference = typename ForwardIterator<T, R>::Reference;
	
	BidirectionalIterator(Pointer p) : ForwardIterator<T,R>(p) {}
	virtual void advance() = 0;
	virtual void advanceBack() = 0;
	Reference operator*() const { return *p; }
	bool operator==(const BidirectionalIterator& rhs) const { return p == rhs.p; }
	bool operator!=(const BidirectionalIterator& rhs) const { return p != rhs.p; }
	BidirectionalIterator& operator++() { advance(); return *this; }
	BidirectionalIterator& operator--() { advanceBack(); return *this; }
};








#endif // __ITERATORS_H

