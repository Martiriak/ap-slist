// Alessandro Pegoraro - 2022

#include <iostream>
#include "SList.h"


void TestPushPopAndClear()
{
	SList<int> ForwardList;

	ForwardList.Print();
	std::cout << "Is empty? " << (ForwardList.empty() ? "Yep\n\n" : "Nope\n\n");

	ForwardList.push_front(5);
	ForwardList.push_front(6);
	ForwardList.push_front(7);

	ForwardList.Print();
	std::cout << "Is empty? " << (ForwardList.empty() ? "Yep\n\n" : "Nope\n\n");

	ForwardList.pop_front();
	ForwardList.Print();
	ForwardList.push_front(1);
	ForwardList.Print();

	std::cout << "\n";
}

void TestConstructors()
{
	SList<int> FirstForwardList(6);
	FirstForwardList.Print(); std::cout << "\n";

	SList<float> SecondForwardList(5, 3.f);
	SecondForwardList.Print(); std::cout << "\n";

	SList<float> ThirdForwardList(SecondForwardList);
	ThirdForwardList.Print(); std::cout << "\n";
}


int main()
{
	TestPushPopAndClear();
	TestConstructors();
}