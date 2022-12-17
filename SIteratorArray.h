// Alessandro Pegoraro - 2022

#pragma once

#include <iterator>
#include <cstddef>


template<typename T>
class ConstSIteratorArray : public std::iterator<std::forward_iterator_tag, T>
{
protected:

	using Index = long long int; // Not unsigned, because we need -1 as a valid index for an invalid iterator.
	using DataArray = T*;

public:

	ConstSIteratorArray() = default;

	inline ConstSIteratorArray(DataArray Data, Index DataPointed)
		: m_Data(Data), m_DataPointed(DataPointed) { }

	inline ConstSIteratorArray(const ConstSIteratorArray<T>& That)
		: m_Data(That.m_Data), m_DataPointed(That.m_DataPointed) { }

	~ConstSIteratorArray() = default;


	inline ConstSIteratorArray<T>& operator= (const ConstSIteratorArray<T>& That)
	{
		m_Data = That.m_Data;
		m_DataPointed = That.m_DataPointed;
		return *this;
	}

	inline bool operator== (const ConstSIteratorArray<T>& That) const
	{
		return (m_Data == That.m_Data) &&
			   (m_DataPointed == That.m_DataPointed);
	}

	inline bool operator!= (const ConstSIteratorArray<T>& That) const
	{
		return (m_Data != That.m_Data) ||
			   (m_DataPointed != That.m_DataPointed);
	}


	inline const T& operator* () const { return m_Data[m_DataPointed]; }
	inline const T* operator-> () const { return &(m_Data[m_DataPointed]); }


	inline ConstSIteratorArray<T>& operator++()
	{
		// Why decrement? Because the last element is the first on the array.
		--m_DataPointed;
		return *this;
	}

	inline ConstSIteratorArray<T> operator++(int)
	{
		ConstSIteratorArray<T> OldIter(*this);
		operator++();
		return OldIter;
	}


protected:

	DataArray m_Data = nullptr;
	Index m_DataPointed = 0;
};


template<typename T>
class SIteratorArray : public ConstSIteratorArray<T>
{
	using ConstSIteratorArray<T>::m_Data;
	using ConstSIteratorArray<T>::m_DataPointed;
	using ConstSIteratorArray<T>::DataArray;
	using ConstSIteratorArray<T>::Index;

public:

	inline SIteratorArray() : ConstSIteratorArray<T>() { }
	inline SIteratorArray(DataArray Data, Index DataPointed) : ConstSIteratorArray<T>(Data, DataPointed) { }
	inline SIteratorArray(const ConstSIteratorArray<T>& That) : ConstSIteratorArray<T>(That) { }
	~SIteratorArray() = default;


	inline T& operator* () { return m_Data[m_DataPointed]; }
	inline T* operator-> () { return &(m_Data[m_DataPointed]); }
};
