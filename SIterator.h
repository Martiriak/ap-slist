// Alessandro Pegoraro - 2022

#pragma once

#include "SNode.h"
#include <iterator>


template<typename T>
class ConstSIterator : public std::iterator<std::forward_iterator_tag, SNode<T>>
{
public:

	ConstSIterator() = default;
	inline ConstSIterator(SNode<T>* Node) : m_NodePointed(Node) { }
	inline ConstSIterator(const ConstSIterator<T>& That) : m_NodePointed(That.m_NodePointed) { }
	~ConstSIterator() = default;

	inline ConstSIterator<T>& operator= (const ConstSIterator<T>& That)
	{
		m_NodePointed = That.m_NodePointed;
		return *this;
	}

	inline bool operator== (const ConstSIterator<T>& That) const
	{
		return m_NodePointed == That.m_NodePointed;
	}

	inline bool operator!= (const ConstSIterator<T>& That) const
	{
		return m_NodePointed != That.m_NodePointed;
	}


	inline const T& operator* () const { return m_NodePointed->Data; }
	inline const T* operator-> () const { return &(m_NodePointed->Data); }


	inline ConstSIterator<T>& operator++()
	{
		m_NodePointed = m_NodePointed->Next;
		return *this;
	}

	inline ConstSIterator<T> operator++(int)
	{
		ConstSIterator<T> OldIter(*this);
		operator++();
		return OldIter;
	}


protected:

	SNode<T>* m_NodePointed = nullptr;
};


template<typename T>
class SIterator : public ConstSIterator<T>
{
	using ConstSIterator<T>::m_NodePointed;

public:

	inline SIterator() : ConstSIterator<T>() { }
	inline SIterator(SNode<T>* Node) : ConstSIterator<T>(Node) { }
	inline SIterator(const ConstSIterator<T>& That) : ConstSIterator<T>(That) { }
	~SIterator() = default;


	inline T& operator* () { return m_NodePointed->Data; }
	inline T* operator-> () { return &(m_NodePointed->Data); }
};
