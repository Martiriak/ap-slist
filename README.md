# Overview
This repository contains 3 distinct implementations of a [Singly Linked List](https://en.wikipedia.org/wiki/Linked_list#Singly_linked_list), each of them written in C++ and compatible with the [STL](https://en.wikipedia.org/wiki/Standard_Template_Library).

Their interfaces were written using the [`std::forward_list`](https://cplusplus.com/reference/forward_list/forward_list/) container as a reference, with the same naming conventions of STL's containers, and providing [iterator](https://en.cppreference.com/w/cpp/iterator) support and standard [algorithm](https://en.cppreference.com/w/cpp/algorithm) functions compatibility.

`C++11` specifications were used to develop these classes.

## General Implementation Details
Where possible, [canonical operators implementations](https://en.cppreference.com/w/cpp/language/operators#Canonical_implementations) was performed, and various operations use other simpler functions, to increase safety and reduce code duplication.

For the same reason, the [copy-and-swap](https://en.cppreference.com/w/cpp/language/operators#Assignment_operator) idiom was adopted for the assignment operator.

## Project Structure
The project has 3 folders:
- `\Lists`: contains the header files of the 3 different lists, along with other utility header files.
- `\Iterators`: contains the header files of the 2 custom iterators.
- `\Tests`: contains `SListApp.cpp`, a file with a `main()` function executing a series of tests on the 3 list types, as well as a `FixedListTests` header and compilation unit files defining those tests for the `FixedSList`[^1] class.

[^1]: Due to `FixedSList` having a different "template structure" from the other 2 list types, a suit of unit tests specific for them was necessary.

# SList
This list uses single-linked nodes as its means of data storage, implementing them with a custom struct called `SNode`.

`SNode` is a lightweight wrapper around a templated datatype, adding only a pointer to the next node of the list.

`SList` employs a custom forward iterator type, called `SIterator`, which makes use of the linked `SNodes`.

### Complexity
`SList` follows [`std::forward_list`](https://cplusplus.com/reference/forward_list/forward_list/) operations' complexity.

In particular, for the `push_front()` and `pop_front()` operations, although they both have O(1) complexities, there is an overhead given by the memory manager, since each `SNode` is allocated on the free store.

# SListArray
This list uses a [`std::vector`](https://cplusplus.com/reference/vector/vector/) as its means of data storage, storing the most recently added data with the higher index. This was done to prevent shifts of all the elements of the vector, only manipulating its back.

In practice, the `SListArray` acts as a wrapper of `std::vector`, using its *back()* operations.

`SListArray` employs a custom forward iterator type, called `SIteratorArray`, which makes use of underlaying container's linearity.

### Complexity
`SListArray` relies on `std::vector` operations, and as such have its same complexity.

The difference between `SListArray` and `SList` complexities is that the former has better cache friendliness thanks to its iterators, but suffers from occasionals slowdowns due to `std::vectors` memory reallocations.

# FixedSList
This list uses a *C-style stack-allocated array* as its means of data storage, storing the most recently added data with the higher index. This was done to prevent shifts of all the elements of the array, only manipulating its back.

In practice, the index of the currently last element of the array is stored as a separate data member, and `FixedSList` operations employ it.

`FixedSList` employs a custom forward iterator type, called `SIteratorArray,` which makes use of underlaying container's linearity.

### Complexity
`FixedSList` follows [`std::forward_list`](https://cplusplus.com/reference/forward_list/forward_list/) operations' complexity.
The only exception is the `clear()` method, which has O(1) complexity achieved thanks to the nature of the stack-allocated array.

The difference between `FixedSList` and `SListArray` complexities is that the former does not allocate anything on the stack, making it more efficent, but it suffers from having its size fixed and known at compile time.

# Iterators Implementations
Each Iterator was implemented using 2 classes:
- A `ConstIterator`, deriving from [`std::iterator`](https://cplusplus.com/reference/iterator/iterator/) with the [`std::forward_iterator_tag`](https://cplusplus.com/reference/iterator/ForwardIterator/), which although it doesn't register its members as *const*, it doesn't grant non const access to them and can be used only as a input iterator.
- A `Iterator`, which derives from `ConstIterator` and espands it with non const methods giving access to the pointed data.
