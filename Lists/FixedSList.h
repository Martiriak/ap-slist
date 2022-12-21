// Alessandro Pegoraro - 2022

#pragma once

#include <cstddef>
#include "SIteratorArray.h"


/**
 * Forward List, compatible with stl and its algorithms.
 *
 * Uses a C-style array as its underlying container, where the element with the highest index is the first on the list.
 * This was done to improve cache friendliness, avoid dynamic allocations and to keep push and pop operations efficient, although giving a compile-time cap on its capacity.
 *
 * Uses a custom forward iterator class, called SIteratorArray, which makes use of the underlaying container's linearity.
 *
 * Note: just like std containers, it won't delete user allocated's memory!
 *
 * @see SIteratorArray
 */
template<typename T, std::size_t Capacity = 1000>
class FixedSList final
{
public:

	using value_type       = T;
	using size_type        = std::size_t;
	using reference        = T&;
	using const_reference  = const T&;
	using pointer          = T*;
	using const_pointer    = const T*;
	using iterator         = SIteratorArray<value_type>;
	using const_iterator   = ConstSIteratorArray<value_type>;


	FixedSList() = default;
	FixedSList(size_type NumberOfElements);
	FixedSList(size_type NumberOfElements, const value_type& BaseValue);
	FixedSList(std::initializer_list<value_type> IL);
	FixedSList(const FixedSList<value_type, Capacity>& That);
	// There isn't a move constructor, because there aren't dynamic allocations.
	~FixedSList();


	FixedSList<value_type, Capacity>& operator= (const FixedSList<value_type, Capacity>& That);
	FixedSList<value_type, Capacity>& operator= (std::initializer_list<value_type> IL);


	// cbegin() and cend() employ a const_cast in order to initialize the const_iterator.
	// This is safe, because the const_iterator does not modify its value.
	// For more information, see ConstSIteratorArray.

	inline iterator begin() noexcept { return iterator(m_Data, m_LastElementIndex); }
	inline const_iterator cbegin() const noexcept { return const_iterator(const_cast<value_type*>(m_Data), m_LastElementIndex); }

	inline iterator end() noexcept { return iterator(m_Data, -1); }
	inline const_iterator cend() const noexcept { return const_iterator(const_cast<value_type*>(m_Data), -1); }


	void assign(size_type NumberOfElements, const value_type& BaseValue);
	void assign(std::initializer_list<value_type> IL);
	void push_front(const value_type& Value);
	void pop_front();
	void clear();
	void swap(FixedSList<value_type, Capacity>& That) noexcept;

	inline reference front() { return m_Data[m_LastElementIndex]; }
	inline const_reference front() const { return m_Data[m_LastElementIndex]; }

	inline bool empty() const { return m_LastElementIndex < 0; }

private:

	using index_type = long long int;

	value_type m_Data[Capacity]; // C26495, ignore this warning, this doesn't need to be initialized.
	index_type m_LastElementIndex = -1;
};




//////////////// METHODS IMPLEMENTATIONS ////////////////



template<typename T, std::size_t Capacity /*= 1000*/>
FixedSList<T, Capacity>::FixedSList(size_type NumberOfElements)
	: FixedSList<value_type, Capacity>(NumberOfElements, value_type()) { }

template<typename T, std::size_t Capacity /*= 1000*/>
FixedSList<T, Capacity>::FixedSList(size_type NumberOfElements, const value_type& BaseValue) { assign(NumberOfElements, BaseValue); }

template<typename T, std::size_t Capacity /*= 1000*/>
FixedSList<T, Capacity>::FixedSList(std::initializer_list<value_type> IL) { assign(IL); }

template<typename T, std::size_t Capacity /*= 1000*/>
FixedSList<T, Capacity>::FixedSList(const FixedSList<value_type, Capacity>& That)
{
	while (m_LastElementIndex != That.m_LastElementIndex)
	{
		push_front(That.m_Data[m_LastElementIndex + 1]);
	}
}

template<typename T, std::size_t Capacity>
FixedSList<T, Capacity>::~FixedSList() { clear(); }



template<typename T, std::size_t Capacity /*= 1000*/>
auto FixedSList<T, Capacity>::operator=(const FixedSList<value_type, Capacity>& That) -> FixedSList<value_type, Capacity>&
{
	clear();

	while (m_LastElementIndex != That.m_LastElementIndex)
	{
		push_front(That.m_Data[m_LastElementIndex + 1]);
	}

	return *this;
}

template<typename T, std::size_t Capacity /*= 1000*/>
auto FixedSList<T, Capacity>::operator=(std::initializer_list<value_type> IL) -> FixedSList<value_type, Capacity>&
{
	assign(IL);
	return *this;
}




template<typename T, std::size_t Capacity /*= 1000*/>
void FixedSList<T, Capacity>::assign(size_type NumberOfElements, const value_type& BaseValue)
{
	clear();

	while (NumberOfElements > 0)
	{
		push_front(BaseValue);
		--NumberOfElements;
	}
}

template<typename T, std::size_t Capacity /*= 1000*/>
void FixedSList<T, Capacity>::assign(std::initializer_list<value_type> IL)
{
	clear();

	for (const value_type& Value : IL)
	{
		push_front(Value);
	}
}

template<typename T, std::size_t Capacity /*= 1000*/>
void FixedSList<T, Capacity>::push_front(const value_type& Value)
{
	if (m_LastElementIndex == Capacity - 1) return;

	m_Data[++m_LastElementIndex] = Value;
}

template<typename T, std::size_t Capacity /*= 1000*/>
void FixedSList<T, Capacity>::pop_front()
{
	--m_LastElementIndex;
	if (m_LastElementIndex < 0) m_LastElementIndex = -1;
}

template<typename T, std::size_t Capacity /*= 1000*/>
void FixedSList<T, Capacity>::clear()
{
	m_LastElementIndex = -1;
}

template<typename T, std::size_t Capacity /*= 1000*/>
void FixedSList<T, Capacity>::swap(FixedSList<value_type, Capacity>& That) noexcept
{
	FixedSList<value_type, Capacity> TmpList = That;
	That = *this;
	*this = TmpList;
}




namespace std
{
	template<typename T, std::size_t Capacity /*= 1000*/>
	void swap(FixedSList<T, Capacity>& A, FixedSList<T, Capacity>& B) noexcept
	{
		A.swap(B);
	}
}
