// Alessandro Pegoraro - 2022

#include <iostream>
#include "SList.h"


template<typename T>
void PrintList(const SList<T>& InList)
{
	int count = 0;
	for (auto it = InList.cbegin(); it != InList.cend(); ++it)
	{
		++count;
		std::cout << *it << " ";
	}

	std::cout << "Number Of Elements: " << count << "\n";
}

SList<int> ReturnListOfIntegers() { return SList<int>(1, 8); }



void TestPushPopAndClear()
{
	SList<int> ForwardList;

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


void TestConstructors()
{
	SList<int> FirstForwardList(6);
	PrintList(FirstForwardList); std::cout << "\n";

	SList<float> SecondForwardList(5, 3.f);
	PrintList(SecondForwardList); std::cout << "\n";

	SList<float> ThirdForwardList(SecondForwardList);
	PrintList(ThirdForwardList); std::cout << "\n";
}


void TestSwap()
{
	SList<int> ListA(3, 2);
	SList<int> ListB; ListB.push_front(6); ListB.push_front(3);

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


void TestAssignment()
{
	SList<int> A(5, 2);
	PrintList(A);

	A.assign(2, 7);
	std::cout << "\nPrinting after assign(2, 7)...\n";
	PrintList(A);

	SList<int> B(3, 4);
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
void TestInitializationList()
{
	SList<float> A = { 1.f, 8.f, 8.96f, 2.364f, 3.14f };
	PrintList(A);

	SList<int> B;
	PrintList(B = { 3, 6, 5 });

	A.assign({5.65f, 3.85f});
	PrintList(A);
}



int main()
{
	//TestPushPopAndClear();
	//TestConstructors();
	//TestSwap();
	//TestAssignment();
	TestInitializationList();
}