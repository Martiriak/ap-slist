// Alessandro Pegoraro - 2022

#pragma once

#include <cstddef>
#include "SNode.h"
#include <iostream>


template<typename T>
class SList final
{
public:

	using value_type = T;
	using size_type = std::size_t;
	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = value_type*;
	using const_pointer = const value_type*;


	SList() = default;
	SList(size_type NumberOfElements);
	SList(size_type NumberOfElements, const value_type& InBaseValue);
	SList(const SList<value_type>& Other);
	SList(SList<value_type>&& Other);
	~SList();



	void push_front(const value_type& InValue);
	void pop_front();
	void clear();
	void swap(SList<value_type>& OutOther);

	reference front();
	const_reference front() const;

	// Debug purpouses, will be removed when iterators will be available.
	void Print();

	inline bool empty() const { return m_FirstNode == nullptr; }

private:

	SNode<value_type>* m_FirstNode = nullptr;
};




//////////////// METHODS IMPLEMENTATIONS


template<typename T>
SList<T>::SList(size_type NumberOfElements)
{
	while (NumberOfElements > 0)
	{
		push_front(value_type());
		--NumberOfElements;
	}
}

template<typename T>
SList<T>::SList(size_type NumberOfElements, const value_type& InBaseValue)
{
	while (NumberOfElements > 0)
	{
		push_front(InBaseValue);
		--NumberOfElements;
	}
}

template<typename T>
SList<T>::SList(const SList<value_type>& Other)
{
	SNode<value_type>* That_CurrentNode = Other.m_FirstNode;
	SNode<value_type>* This_PreviousNode = nullptr;

	while (That_CurrentNode != nullptr)
	{
		SNode<value_type>* NewNode = new SNode<value_type>(*That_CurrentNode);

		if (this->empty()) m_FirstNode = NewNode;
		else This_PreviousNode->Next = NewNode;

		This_PreviousNode = NewNode;
		That_CurrentNode = That_CurrentNode->Next;
	}
}

template<typename T>
SList<T>::SList(SList<value_type>&& Other)
{
	m_FirstNode = Other.m_FirstNode;
	Other.m_FirstNode = nullptr;
}

template<typename T>
SList<T>::~SList()
{
	clear();
}





template<typename T>
void SList<T>::push_front(const value_type& InValue)
{
	SNode<value_type>* NewNode = new SNode<value_type>(m_FirstNode, InValue);
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
void SList<T>::swap(SList<value_type>& OutOther)
{
	// TODO
}


template<typename T>
SList<T>::reference SList<T>::front() { return m_FirstNode->Data; }

template<typename T>
SList<T>::const_reference SList<T>::front() const { return m_FirstNode->Data; }



























template<typename T>
void SList<T>::Print()
{
	int Count = 0;
	SNode<value_type>* CurrentNode = m_FirstNode;

	while (CurrentNode != nullptr)
	{
		++Count;
		std::cout << CurrentNode->Data << " ";
		CurrentNode = CurrentNode->Next;
	}

	std::cout << "Numero di Elementi: " << Count << "\n";
}
