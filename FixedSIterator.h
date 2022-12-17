// Alessandro Pegoraro - 2022

#pragma once

#include <iterator>
#include <cstddef>


template<typename T>
class ConstFixedSIterator : public std::iterator<std::forward_iterator_tag, T>
{
protected:

	using Index = std::size_t;
	using DataArray = T*;

public:

	ConstFixedSIterator() = default;

	inline ConstFixedSIterator(DataArray Data, Index DataPointed)
		: m_Data(Data), m_DataPointed(DataPointed) { }

	inline ConstFixedSIterator(const ConstFixedSIterator<T>& That)
		: m_Data(That.m_Data), m_DataPointed(That.m_DataPointed) { }

	~ConstFixedSIterator() = default;


	inline ConstFixedSIterator<T>& operator= (const ConstFixedSIterator<T>& That)
	{
		m_Data = That.m_Data;
		m_DataPointed = That.m_DataPointed;
		return *this;
	}

	inline bool operator== (const ConstFixedSIterator<T>& That) const
	{
		return (m_Data == That.m_Data) &&
			(m_DataPointed == That.m_DataPointed);
	}

	inline bool operator!= (const ConstFixedSIterator<T>& That) const
	{
		return (m_Data != That.m_Data) ||
			(m_DataPointed != That.m_DataPointed);
	}


	inline const T& operator* () const { return m_Data[m_DataPointed]; }
	inline const T* operator-> () const { return &(m_Data[m_DataPointed]); }


	inline ConstFixedSIterator<T>& operator++()
	{
		++m_DataPointed;
		return *this;
	}

	inline ConstFixedSIterator<T> operator++(int)
	{
		ConstFixedSIterator<T> OldIter(*this);
		operator++();
		return OldIter;
	}


protected:

	DataArray m_Data = nullptr;
	Index m_DataPointed = 0;
};


template<typename T>
class FixedSIterator : public ConstFixedSIterator<T>
{
	using ConstFixedSIterator<T>::m_Data;
	using ConstFixedSIterator<T>::m_DataPointed;
	using ConstFixedSIterator<T>::DataArray;
	using ConstFixedSIterator<T>::Index;

public:

	inline FixedSIterator() : ConstFixedSIterator<T>() { }
	inline FixedSIterator(DataArray Data, Index DataPointed) : ConstFixedSIterator<T>(Data, DataPointed) { }
	inline FixedSIterator(const ConstFixedSIterator<T>& That) : ConstFixedSIterator<T>(That) { }
	~FixedSIterator() = default;


	inline T& operator* () { return m_Data[m_DataPointed]; }
	inline T* operator-> () { return &(m_Data[m_DataPointed]); }
};
