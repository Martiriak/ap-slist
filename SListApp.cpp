// Alessandro Pegoraro - 2022

#include <iostream>
#include "SList.h"


template<typename T>
void PrintList(const SList<T>& InList)
{
	int count = 0;
	for (auto It = InList.cbegin(); It != InList.cend(); ++It)
	{
		++count;
		std::cout << *It << " ";
	}

	std::cout << "Number Of Elements: " << count << "\n";
}

SList<int> ReturnListOfIntegers() { return SList<int>(1, 8); }



template< template<typename _> class ListType >
void TestPushPopAndClear()
{
	ListType<int> ForwardList;

	PrintList(ForwardList);
	std::cout << "Is empty? " << (ForwardList.empty() ? "Yep\n\n" : "Nope\n\n");

	ForwardList.push_front(5);
	ForwardList.push_front(6);
	ForwardList.push_front(7);

	PrintList(ForwardList);
	std::cout << "Is empty? " << (ForwardList.empty() ? "Yep\n\n" : "Nope\n\n");

	ForwardList.pop_front();
	PrintList(ForwardList);
	ForwardList.push_front(1);
	PrintList(ForwardList);

	std::cout << "\n";
}


template< template<typename _> class ListType >
void TestConstructors()
{
	ListType<int> FirstForwardList(6);
	PrintList(FirstForwardList); std::cout << "\n";

	ListType<float> SecondForwardList(5, 3.f);
	PrintList(SecondForwardList); std::cout << "\n";

	ListType<float> ThirdForwardList(SecondForwardList);
	PrintList(ThirdForwardList); std::cout << "\n";
}


template< template<typename _> class ListType >
void TestSwap()
{
	ListType<int> ListA(3, 2);
	ListType<int> ListB; ListB.push_front(6); ListB.push_front(3);

	ListA.swap(ListB);

	std::cout << "Printing List A...\n";
	PrintList(ListA);
	std::cout << "\nPrinting List B...\n";
	PrintList(ListB);

	std::swap(ListB, ListA);

	std::cout << "\nAgain, Printing List A...\n";
	PrintList(ListA);
	std::cout << "\nPrinting List B...\n";
	PrintList(ListB);

	// Should give an error, and it does!
	//ListB.swap(ListFloat);
}


template< template<typename _> class ListType >
void TestAssignment()
{
	ListType<int> A(5, 2);
	PrintList(A);

	A.assign(2, 7);
	std::cout << "\nPrinting after assign(2, 7)...\n";
	PrintList(A);

	ListType<int> B(3, 4);
	std::cout << "\n\nList B...\n";
	PrintList(B);

	B = A;
	std::cout << "\nB = A\n";
	PrintList(B);

	A = ReturnListOfIntegers();
	std::cout << "\nA = some temp\n";
	PrintList(A);
}


// About Initializer List: C++11 doesn't have reversed iterators for those,
// meaning the front of the forward list will be the last element declared in the
// initializer list. I'm not particularly fond of this, but it's not the end of the world either.
template< template<typename _> class ListType >
void TestInitializationList()
{
	ListType<float> A = { 1.f, 8.f, 8.96f, 2.364f, 3.14f };
	PrintList(A);

	ListType<int> B;
	PrintList(B = { 3, 6, 5 });

	A.assign({5.65f, 3.85f});
	PrintList(A);
}



int main()
{
	TestPushPopAndClear<SList>();
	TestConstructors<SList>();
	TestSwap<SList>();
	TestAssignment<SList>();
	TestInitializationList<SList>();
}