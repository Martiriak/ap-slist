// Alessandro Pegoraro - 2022

#pragma once

#include <cstddef>
#include <vector>
#include "SIteratorArray.h"


/**
 * Forward List, compatible with stl and its algorithms.
 *
 * Uses a std vector as its underlying container, where the element with the highest index is the first on the list.
 * This was done to improve cache friendliness and to keep push and pop operations efficient, although with an amortized cost given by the occasional vector resizes.
 * 
 * Uses a custom forward iterator class, called SIteratorArray, which makes use of the underlaying container's linearity.
 *
 * Note: just like std containers, it won't delete user allocated's memory!
 *
 * @see SIteratorArray
 */
template<typename T>
class SListArray final
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


	SListArray() = default;
	SListArray(size_type NumberOfElements);
	SListArray(size_type NumberOfElements, const value_type& BaseValue);
	SListArray(std::initializer_list<value_type> IL);
	SListArray(const SListArray<value_type>& That);
	SListArray(SListArray<value_type>&& That);
	~SListArray();


	SListArray<value_type>& operator= (SListArray<value_type> That); // copy-and-swap idiom.
	SListArray<value_type>& operator= (std::initializer_list<value_type> IL);


	// cbegin() and cend() employ a const_cast in order to initialize the const_iterator.
	// This is safe, because the const_iterator does not modify its value.
	// For more information, see ConstSIteratorArray.

	inline iterator begin() noexcept { return iterator(m_Data.data(), m_Data.size() - 1); }
	inline const_iterator cbegin() const noexcept { return const_iterator(const_cast<value_type*>(m_Data.data()), m_Data.size() - 1); }

	inline iterator end() noexcept { return iterator(m_Data.data(), -1); }
	inline const_iterator cend() const noexcept { return const_iterator(const_cast<value_type*>(m_Data.data()), -1); }


	void assign(size_type NumberOfElements, const value_type& BaseValue);
	void assign(std::initializer_list<value_type> IL);
	void push_front(const value_type& Value);
	void pop_front(); 
	void clear();
	void swap(SListArray<value_type>& That) noexcept;

	inline reference front() { return m_Data.back(); }
	inline const_reference front() const { return m_Data.back(); }

	inline bool empty() const { return m_Data.size() == 0; }

private:

	std::vector<value_type> m_Data;
};




//////////////// METHODS IMPLEMENTATIONS ////////////////


template<typename T>
SListArray<T>::SListArray(size_type NumberOfElements) : SListArray<value_type>(NumberOfElements, value_type()) { }

template<typename T>
SListArray<T>::SListArray(size_type NumberOfElements, const value_type& BaseValue) { assign(NumberOfElements, BaseValue); }

template<typename T>
SListArray<T>::SListArray(std::initializer_list<value_type> IL) { assign(IL); }

template<typename T>
SListArray<T>::SListArray(const SListArray<value_type>& That)
{
	m_Data.reserve(That.m_Data.size());

	for (const value_type& Value : That.m_Data)
	{
		push_front(Value);
	}
}

template<typename T>
SListArray<T>::SListArray(SListArray<value_type>&& That) : m_Data(std::move(That.m_Data)) { }

template<typename T>
SListArray<T>::~SListArray() { clear(); }



template<typename T>
auto SListArray<T>::operator=(SListArray<value_type> That) -> SListArray<value_type>&
{
	std::swap(m_Data, That.m_Data);
	return *this;
}

template<typename T>
auto SListArray<T>::operator=(std::initializer_list<value_type> IL) -> SListArray<value_type>&
{
	assign(IL);
	return *this;
}




template<typename T>
void SListArray<T>::assign(size_type NumberOfElements, const value_type& BaseValue)
{
	clear();

	m_Data.reserve(NumberOfElements);

	while (NumberOfElements > 0)
	{
		push_front(BaseValue);
		--NumberOfElements;
	}
}

template<typename T>
void SListArray<T>::assign(std::initializer_list<value_type> IL)
{
	clear();

	m_Data.reserve(IL.size());

	for (const value_type& Value : IL)
	{
		push_front(Value);
	}
}

template<typename T>
void SListArray<T>::push_front(const value_type& Value)
{
	m_Data.push_back(Value);
}

template<typename T>
void SListArray<T>::pop_front()
{
	m_Data.pop_back();
}

template<typename T>
void SListArray<T>::clear()
{
	m_Data.clear();
}

template<typename T>
void SListArray<T>::swap(SListArray<value_type>& That) noexcept
{
	std::swap(m_Data, That.m_Data);
}




namespace std
{
	template<typename T>
	void swap(SListArray<T>& A, SListArray<T>& B) noexcept
	{
		A.swap(B);
	}
}
