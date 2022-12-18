// Alessandro Pegoraro - 2022

#include "FixedListTests.h"
#include "FixedSList.h"
#include <iostream>


namespace
{
	template<typename T>
	void PrintList(const FixedSList<T>& List)
	{
		int count = 0;

		for (auto It = List.cbegin(); It != List.cend(); ++It)
		{
			++count;
			std::cout << *It << " ";
		}

		std::cout << "Number Of Elements: " << count << "\n";
	}

	FixedSList<int> ReturnListOfIntegers() { return FixedSList<int>(1, 8); }
}


namespace FixedTests
{
	void TestPushPopAndClear()
	{
		FixedSList<int> ForwardList;

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

		ForwardList.clear();
		PrintList(ForwardList);

		std::cout << "\n";
	}

	void TestConstructors()
	{
		FixedSList<int> FirstForwardList(6);
		PrintList(FirstForwardList); std::cout << "\n";

		FixedSList<float> SecondForwardList(5, 3.f);
		PrintList(SecondForwardList); std::cout << "\n";

		FixedSList<float> ThirdForwardList(SecondForwardList);
		PrintList(ThirdForwardList); std::cout << "\n";
	}

	void TestSwap()
	{
		FixedSList<int> ListA(3, 2);
		FixedSList<int> ListB; ListB.push_front(6); ListB.push_front(3);

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
		//FixedSList<float> ListFloat(1, 3.14f);
		//ListB.swap(ListFloat);
	}

	void TestAssignment()
	{
		FixedSList<int> A(5, 2);
		PrintList(A);

		A.assign(2, 7);
		std::cout << "\nPrinting after assign(2, 7)...\n";
		PrintList(A);

		FixedSList<int> B(3, 4);
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
		FixedSList<float> A = { 1.f, 8.f, 8.96f, 2.364f, 3.14f };
		PrintList(A);

		FixedSList<int> B;
		PrintList(B = { 3, 6, 5 });

		A.assign({ 5.65f, 3.85f });
		PrintList(A);
	}
}
