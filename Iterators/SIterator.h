// Alessandro Pegoraro - 2022

#pragma once

#include "SNode.h"
#include <iterator>


/**
 * Forward iterator used in conjunction with SList.
 * 
 * It iterates through SNodes, using their already existing link.
 * end() iterators do not point to any SNode.
 * 
 * Even though it doesn't use the keyword const, this is treated as a constant iterator, and as such it does not modify its values.
 *
 * @see SList, SNode
 */
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

	// Non-canonical implementation of operator!=, given its brevity it isn't a concern.
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



/**
 * Forward iterator used in conjunction with SList.
 *
 * It iterates through SNodes, using their already existing link.
 * end() iterators do not point to any SNode.
 *
 * It extends ConstSIterator, allowing for its values to be modified.
 *
 * @see SList, SNode
 */
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
