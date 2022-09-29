// Alessandro Pegoraro - 2022

#pragma once
#include "SNode.h"
#include <iostream>


template<typename T>
class SList final
{
	//struct SNode<T>;

public:

	/*SList();
	SList(int NumberOfElements);
	~SList();*/

	void PushFront(const T& InValue);
	void PopFront();
	void Clear();

	void Print();

	inline bool IsEmpty() const { return m_FirstNode == nullptr; }

private:

	SNode<T>* m_FirstNode = nullptr;
};

template<typename T>
void SList<T>::PushFront(const T& InValue)
{
	SNode<T>* NewNode = new SNode<T>(m_FirstNode, InValue);
	m_FirstNode = NewNode;
}

template<typename T>
void SList<T>::PopFront()
{
	if (m_FirstNode != nullptr)
	{
		SNode<T>* SecondNode = m_FirstNode->Next;
		delete m_FirstNode;
		m_FirstNode = SecondNode;
	}
}

template<typename T>
void SList<T>::Clear()
{
	while (m_FirstNode != nullptr) PopFront();
}

template<typename T>
void SList<T>::Print()
{
	int Count = 0;
	SNode<T>* CurrentNode = m_FirstNode;

	while (CurrentNode != nullptr)
	{
		++Count;
		std::cout << CurrentNode->Data << " ";
		CurrentNode = CurrentNode->Next;
	}

	std::cout << "Numero di Elementi: " << Count << "\n";
}
