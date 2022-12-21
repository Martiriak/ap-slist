// Alessandro Pegoraro - 2022

#pragma once

#include <iterator>


/**
 * Forward iterator used in conjunction with SListArray and FixedSList, but can be used for any C-style array.
 *
 * It uses a pointer to said C-style array and the index of the iterated element, using random access to retrieve it.
 * 
 * It assumes that the last element has the index 0, and as such it actually decrements the index when incrementing the iterator.
 * This is done to accomodate SListArray and FixedSList implementation.
 *
 * Even though it doesn't use the keyword const, this is treated as a constant iterator, and as such it does not modify its values.
 * However, the DataArray argument does need a const_cast to T*, or else it won't compile if used in a const method.
 * This quirk could be fixed by making m_Data a const T*, and making its SIteratorArray child class use a different, non const, pointer to T.
 * However, this wasn't done to keep overheads to the minimum.
 *
 * @see SListArray, FixedSList
 */
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
		return ! operator==(That);
	}


	inline const T& operator* () const { return m_Data[m_DataPointed]; }
	inline const T* operator-> () const { return &(m_Data[m_DataPointed]); }


	inline ConstSIteratorArray<T>& operator++()
	{
		// Why decrement? Read the javadoc.
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



/**
 * Forward iterator used in conjunction with SListArray and FixedSList, but can be used for any C-style array.
 *
 * It uses a pointer to said C-style array and the index of the iterated element, using random access to retrieve it.
 *
 * It assumes that the last element has the index 0, and as such it actually decrements the index when incrementing the iterator.
 * This is done to accomodate SListArray and FixedSList implementation.
 *
 * It extends ConstSIterator, allowing for its values to be modified.
 * However, the DataArray argument needs a const_cast to T*, or else it won't compile if used in a const method.
 * This quirk could be fixed by making its ConstSIteratorArray parent class use another const pointer to T.
 * However, this wasn't done to keep overheads to the minimum.
 * 
 * @see SList, SNode
 */
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
