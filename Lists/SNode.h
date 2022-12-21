// Alessandro Pegoraro - 2022

#pragma once


/**
 * Simple support struct used by SList, to implement a Forward List.
 * Could be further improved by implementing move semantics and swap.
 * 
 * @see SList
 */
template<typename T>
struct SNode final
{
	SNode<T>* Next = nullptr;
	T Data;

	SNode() = delete;
	inline SNode(SNode<T>* _Next, const T& _Data) : Next(_Next), Data(_Data) { }
	inline SNode(const SNode<T>& That) : Next(That.Next), Data(That.Data) { }

	inline SNode<T>& operator= (const SNode<T>& That)
	{
		Next = That.Next;
		Data = That.Data;
		return *this;
	}
};
