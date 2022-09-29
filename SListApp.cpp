// Alessandro Pegoraro - 2022

#include <iostream>
#include "SList.h"


int main()
{
    SList<int> ForwardList;

    ForwardList.Print();
    std::cout << "Is empty? " << (ForwardList.IsEmpty() ? "Yep\n\n" : "Nope\n\n");


    ForwardList.PushFront(5);
    ForwardList.PushFront(6);
    ForwardList.PushFront(7);

    ForwardList.Print();
    std::cout << "Is empty? " << (ForwardList.IsEmpty() ? "Yep\n\n" : "Nope\n\n");

    ForwardList.PopFront();
    ForwardList.Print();
    ForwardList.PushFront(1);
    ForwardList.Print();

    std::cout << "\n";

    ForwardList.Clear();
    ForwardList.Print();

    std::cout << "\n";

    ForwardList.PopFront();
    ForwardList.Clear();
    std::cout << "Is empty? " << (ForwardList.IsEmpty() ? "Yep\n\n" : "Nope\n\n");
}