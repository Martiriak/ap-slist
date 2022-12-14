// Alessandro Pegoraro - 2022

#pragma once

#include <cstddef>
#include "SNode.h"
#include "SIterator.h"


/**
 * Forward List, compatible with stl and its algorithms.
 * 
 * Uses a struct called SNode to store its values and link them together.
 * Uses a custom forward iterator class, called SIterator, which makes use of the linked SNodes.
 * 
 * Allocates memory on the free store, but manages it internally.
 * This means that although push and pop operations are O(1), they will request memory to the OS each time.
 * 
 * Note: just like std containers, it won't delete user allocated's memory!
 * 
 * @see SNode, SIterator
 */
template<typename T>
class SList final
{
public:

	using value_type       = T;
	using size_type        = std::size_t;
	using reference        = T&;
	using const_reference  = const T&;
	using pointer          = T*;
	using const_pointer    = const T*;
	using iterator         = SIterator<value_type>;
	using const_iterator   = ConstSIterator<value_type>;


	SList() = default;
	SList(size_type NumberOfElements);
	SList(size_type NumberOfElements, const value_type& BaseValue);
	SList(std::initializer_list<value_type> IL);
	SList(const SList<value_type>& That);
	SList(SList<value_type>&& That);
	~SList();


	SList<value_type>& operator= (SList<value_type> That); // copy-and-swap idiom.
	SList<value_type>& operator= (std::initializer_list<value_type> IL);


	inline iterator begin() noexcept { return iterator(m_FirstNode); }
	inline const_iterator cbegin() const noexcept { return const_iterator(m_FirstNode); }

	inline iterator end() noexcept { return iterator(); }
	inline const_iterator cend() const noexcept { return const_iterator(); }

	void assign(size_type NumberOfElements, const value_type& BaseValue);
	void assign(std::initializer_list<value_type> IL);
	void push_front(const value_type& Value);
	void pop_front();
	void clear();
	void swap(SList<value_type>& That) noexcept;

	inline reference front() { return m_FirstNode->Data; }
	inline const_reference front() const { return m_FirstNode->Data; }

	inline bool empty() const { return m_FirstNode == nullptr; }

private:

	SNode<value_type>* m_FirstNode = nullptr;
};




//////////////// METHODS IMPLEMENTATIONS ////////////////


template<typename T>
SList<T>::SList(size_type NumberOfElements) : SList<value_type>(NumberOfElements, value_type()) { }

template<typename T>
SList<T>::SList(size_type NumberOfElements, const value_type& BaseValue) { assign(NumberOfElements, BaseValue); }

template<typename T>
SList<T>::SList(std::initializer_list<value_type> IL) { assign(IL); }

template<typename T>
SList<T>::SList(const SList<value_type>& That)
{
	SNode<value_type>* That_CurrentNode = That.m_FirstNode;
	SNode<value_type>* This_PreviousNode = nullptr;

	SNode<value_type>* NewNode = nullptr;

	while (That_CurrentNode != nullptr)
	{
		NewNode = new SNode<value_type>(*That_CurrentNode);

		if (this->empty()) m_FirstNode = NewNode;
		else This_PreviousNode->Next = NewNode; // Compiler warning, but it never gets dereferenced when null.

		This_PreviousNode = NewNode;
		That_CurrentNode = That_CurrentNode->Next;
	}
}

template<typename T>
SList<T>::SList(SList<value_type>&& That) : m_FirstNode(std::move(That.m_FirstNode)) { }

template<typename T>
SList<T>::~SList() { clear(); }



template<typename T>
auto SList<T>::operator= (SList<value_type> That) -> SList<value_type>&
{
	clear();
	std::swap(m_FirstNode, That.m_FirstNode);
	return *this;
}

template<typename T>
auto SList<T>::operator= (std::initializer_list<value_type> IL) -> SList<value_type>&
{
	assign(IL);
	return *this;
}




template<typename T>
void SList<T>::assign(size_type NumberOfElements, const value_type& BaseValue)
{
	clear();

	while (NumberOfElements > 0)
	{
		push_front(BaseValue);
		--NumberOfElements;
	}
}

template<typename T>
void SList<T>::assign(std::initializer_list<value_type> IL)
{
	clear();

	for (const value_type& Value : IL)
	{
		push_front(Value);
	}
}


template<typename T>
void SList<T>::push_front(const value_type& Value)
{
	SNode<value_type>* NewNode = new SNode<value_type>(m_FirstNode, Value);
	m_FirstNode = NewNode;
}

template<typename T>
void SList<T>::pop_front()
{
	if (m_FirstNode != nullptr)
	{
		SNode<value_type>* SecondNode = m_FirstNode->Next;
		delete m_FirstNode;
		m_FirstNode = SecondNode;
	}
}

template<typename T>
void SList<T>::clear()
{
	while (m_FirstNode != nullptr) pop_front();
}

template<typename T>
void SList<T>::swap(SList<value_type>& That) noexcept
{
	std::swap(m_FirstNode, That.m_FirstNode);
}




namespace std
{
	template<typename T>
	void swap(SList<T>& A, SList<T>& B) noexcept
	{
		A.swap(B);
	}
}
