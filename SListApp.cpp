// Alessandro Pegoraro - 2022

#include <iostream>
#include "SList.h"


template<typename T>
void PrintList(SList<T>& InList)
{
	int count = 0;
	for (auto it = InList.begin(); it != InList.end(); ++it)
	{
		++count;
		std::cout << *it << " ";
	}

	std::cout << "Number Of Elements: " << count << "\n";
}


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


int main()
{
	TestPushPopAndClear();
	TestConstructors();
}