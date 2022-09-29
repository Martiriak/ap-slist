// Alessandro Pegoraro - 2022

#pragma once


template<typename T>
struct SNode final
{
	SNode<T>* Next = nullptr;
	T Data;

	SNode() = delete;
	inline SNode(SNode<T>* _Next, const T& _Data) : Next(_Next), Data(_Data) { }
	inline SNode(const SNode<T>& Other) : Next(Other.Next), Data(Other.Data) { }

	inline SNode<T>& operator= (const SNode<T>& Other)
	{
		Next = Other.Next;
		Data = Other.Data;
		return *this;
	}
};
