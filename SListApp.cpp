// Alessandro Pegoraro - 2022

#include <iostream>
#include <algorithm>
#include <forward_list>
#include "SList.h"
#include "SListArray.h"
#include "FixedSList.h"
#include "FixedListTests.h"


template< template<typename _> class ListType, typename T>
void PrintList(const ListType<T>& List)
{
	int count = 0;

	for (auto It = List.cbegin(); It != List.cend(); ++It)
	{
		++count;
		std::cout << *It << " ";
	}

	std::cout << "Number Of Elements: " << count << "\n";
}

template< template<typename _> class ListType>
ListType<int> ReturnListOfIntegers() { return ListType<int>(1, 8); }



template< template<typename _> class ListType >
void TestPushPopClearAndFront()
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

	std::cout << "\nFront: " << ForwardList.front() << ", now clearing.\n";

	ForwardList.clear();
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
	//ListType<float> ListFloat(1, 3.14f);
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

	A = ReturnListOfIntegers<ListType>();
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





void TestFindIf()
{
	std::forward_list<int> StdList  = { 4, 8, 15, 16, 23, 42 };
	SList<int> NodeList             = { 42, 23, 16, 15, 8, 4 };
	SListArray<int> VectorList      = { 42, 23, 16, 15, 8, 4 };
	FixedSList<int, 20> FixedList   = { 42, 23, 16, 15, 8, 4 };

	auto IsGreaterThan20 = [](int Value) { return Value > 20; };

	std::cout << "Value found in StdList: ";
	std::cout << *(std::find_if(StdList.cbegin(), StdList.cend(), IsGreaterThan20));
	std::cout << '\n';

	std::cout << "Value found in NodeList: ";
	std::cout << *(std::find_if(NodeList.cbegin(), NodeList.cend(), IsGreaterThan20));
	std::cout << '\n';

	std::cout << "Value found in VectorList: ";
	std::cout << *(std::find_if(VectorList.cbegin(), VectorList.cend(), IsGreaterThan20));
	std::cout << '\n';

	std::cout << "Value found in FixedList: ";
	std::cout << *(std::find_if(FixedList.cbegin(), FixedList.cend(), IsGreaterThan20));
	std::cout << '\n';
}

void TestCount()
{
	std::forward_list<int> StdList  = { 4, 8, 4, 16, 4, 42 };
	SList<int> NodeList             = { 42, 4, 16, 4, 8, 4 };
	SListArray<int> VectorList      = { 42, 4, 16, 4, 8, 4 };
	FixedSList<int, 20> FixedList   = { 42, 4, 16, 4, 8, 4 };

	std::cout << "There are ";
	std::cout << std::count(StdList.cbegin(), StdList.cend(), 4);
	std::cout << " 4s in StdList.\n";

	std::cout << "There are ";
	std::cout << std::count(NodeList.cbegin(), NodeList.cend(), 4);
	std::cout << " 4s in NodeList.\n";

	std::cout << "There are ";
	std::cout << std::count(VectorList.cbegin(), VectorList.cend(), 4);
	std::cout << " 4s in VectorList.\n";

	std::cout << "There are ";
	std::cout << std::count(FixedList.cbegin(), FixedList.cend(), 4);
	std::cout << " 4s in FixedList.\n";
}

void TestForEachAndForRange()
{
	std::forward_list<int> StdList  = { 4, 8, 15, 16, 23, 42 };
	SList<int> NodeList             = { 42, 23, 16, 15, 8, 4 };
	SListArray<int> VectorList      = { 42, 23, 16, 15, 8, 4 };
	FixedSList<int, 20> FixedList   = { 42, 23, 16, 15, 8, 4 };

	auto IncrementEachBy5 = [](int& Value) { Value += 5; };

	std::for_each(StdList.begin(), StdList.end(), IncrementEachBy5);
	std::for_each(NodeList.begin(), NodeList.end(), IncrementEachBy5);
	std::for_each(VectorList.begin(), VectorList.end(), IncrementEachBy5);
	std::for_each(FixedList.begin(), FixedList.end(), IncrementEachBy5);

	std::cout << "Printing values of StdList...\n";
	for (int Value : StdList)
	{
		std::cout << Value << ' ';
	}
	std::cout << "\n";

	std::cout << "Printing values of NodeList...\n";
	for (int Value : NodeList)
	{
		std::cout << Value << ' ';
	}
	std::cout << "\n";

	std::cout << "Printing values of VectorList...\n";
	for (int Value : VectorList)
	{
		std::cout << Value << ' ';
	}
	std::cout << "\n";

	std::cout << "Printing values of FixedList...\n";
	for (int Value : FixedList)
	{
		std::cout << Value << ' ';
	}
	std::cout << "\n";
}

void TestCopy()
{
	std::forward_list<int> StdList  = { 4, 8, 15, 16, 23, 42 };
	SList<int> NodeList             = { 0, 0, 0, 0, 7, 3 };
	SListArray<int> VectorList      = { -1, -1, -1, -1, 6, 2 };
	FixedSList<int, 20> FixedList   = { -2, -2, -2, -2, 5, 1 };

	// Expected end results:
	// StdList     = 4, 8, 15, 16, 23, 42
	// NodeList    = 3, 8, 15, 16, 23, 0
	// VectorList  = 2, 8, 15, 16, 23, -1
	// FixedList   = 1, 8, 15, 16, 23, -2

	// Begin starts at index 1, End at index 4.

	auto StdBegin = StdList.begin(); ++StdBegin;
	auto StdEnd = StdList.begin(); for (int i = 0; i < 5; ++i) ++StdEnd;

	auto NodeBegin = NodeList.begin(); ++NodeBegin;
	auto NodeEnd = NodeList.begin(); for (int i = 0; i < 5; ++i) ++NodeEnd;

	auto VectorBegin = VectorList.begin(); ++VectorBegin;
	auto VectorEnd = VectorList.begin(); for (int i = 0; i < 5; ++i) ++VectorEnd;

	auto FixedBegin = FixedList.begin(); ++FixedBegin;
	auto FixedEnd = FixedList.begin(); for (int i = 0; i < 5; ++i) ++FixedEnd;


	std::copy(StdBegin, StdEnd, NodeBegin);
	std::copy(NodeBegin, NodeEnd, VectorBegin);
	std::copy(VectorBegin, VectorEnd, FixedBegin);
	std::copy(FixedBegin, FixedEnd, StdBegin); // This one shouldn't modify StdList.


	std::cout << "Printing values of StdList...\n";
	for (int Value : StdList)
	{
		std::cout << Value << ' ';
	}
	std::cout << "\n";

	std::cout << "Printing values of NodeList...\n";
	for (int Value : NodeList)
	{
		std::cout << Value << ' ';
	}
	std::cout << "\n";

	std::cout << "Printing values of VectorList...\n";
	for (int Value : VectorList)
	{
		std::cout << Value << ' ';
	}
	std::cout << "\n";

	std::cout << "Printing values of FixedList...\n";
	for (int Value : FixedList)
	{
		std::cout << Value << ' ';
	}
	std::cout << "\n";
}


int main()
{
	TestPushPopClearAndFront<SList>();
	TestConstructors<SList>();
	TestSwap<SList>();
	TestAssignment<SList>();
	TestInitializationList<SList>();

	std::cout << "\n\n=====================================================================\n\n";

	TestPushPopClearAndFront<SListArray>();
	TestConstructors<SListArray>();
	TestSwap<SListArray>();
	TestAssignment<SListArray>();
	TestInitializationList<SListArray>();

	std::cout << "\n\n=====================================================================\n\n";

	FixedTests::TestPushPopClearAndFront();
	FixedTests::TestConstructors();
	FixedTests::TestSwap();
	FixedTests::TestAssignment();
	FixedTests::TestInitializationList();

	std::cout << "\n\n=====================================================================\n\n";

	TestFindIf();
	TestCount();
	TestForEachAndForRange();
	TestCopy();
}
