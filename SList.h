// Alessandro Pegoraro - 2022

#pragma once

#include <cstddef>
#include "SNode.h"
#include "SIterator.h"


template<typename T>
class SList final
{
public:

	using value_type = T;
	using size_type = std::size_t;
	using reference = T&;
	using const_reference = const T&;
	using pointer = T*;
	using const_pointer = const T*;
	using iterator = SIterator<value_type>;
	using const_iterator = ConstSIterator<value_type>;


	SList() = default;
	SList(size_type NumberOfElements);
	SList(size_type NumberOfElements, const value_type& InBaseValue);
	SList(const SList<value_type>& Other);
	SList(SList<value_type>&& Other);
	~SList();

	inline iterator begin() noexcept { return iterator(m_FirstNode); }
	inline const_iterator cbegin() const noexcept { return const_iterator(m_FirstNode); }

	inline iterator end() noexcept { return iterator(); }
	inline const_iterator cend() const noexcept { return const_iterator(); }

	void push_front(const value_type& InValue);
	void pop_front();
	void clear();
	void swap(SList<value_type>& OutOther) noexcept;

	inline reference front() { return m_FirstNode->Data; }
	inline const_reference front() const { return m_FirstNode->Data; }

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

	SNode<value_type>* NewNode = nullptr;

	while (That_CurrentNode != nullptr)
	{
		NewNode = new SNode<value_type>(*That_CurrentNode);

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
void SList<T>::swap(SList<value_type>& OutOther) noexcept
{
	SNode<value_type>* Tmp = OutOther.m_FirstNode;
	OutOther.m_FirstNode = this->m_FirstNode;
	this->m_FirstNode = Tmp;
}




namespace std
{
	template<typename T>
	void swap(SList<T>& A, SList<T>& B) noexcept
	{
		A.swap(B);
	}
}
