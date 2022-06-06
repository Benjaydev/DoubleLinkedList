#pragma once
#include <iostream>

// List element class
// Non-pointer templated
template<typename T>
struct ListElement {
	public:
		ListElement(T v, ListElement* prev, ListElement* nxt);

		T value;
		ListElement* next;
		ListElement* previous;
};

// Pointer templated
template<typename T>
struct ListElement<T*> {
	public:
		ListElement(T* v, ListElement* prev, ListElement* nxt);
		~ListElement();

		T* value;
		ListElement* next;
		ListElement* previous;
};

template<typename T>
inline ListElement<T>::ListElement(T v, ListElement* prev, ListElement* nxt)
{
	value = v;
	previous = prev;
	next = nxt;
}

template<typename T>
inline ListElement<T*>::ListElement(T* v, ListElement* prev, ListElement* nxt)
{
	value = v;
	previous = prev;
	next = nxt;
}

template<typename T>
inline ListElement<T*>::~ListElement()
{
	if (value != nullptr) {
		delete value;
		value = nullptr;
	}
}

// Double linked list class

template<typename T>
class DoubleLinkedList
{
public:

	DoubleLinkedList();
	~DoubleLinkedList();


	void Add(T value, int index);
	void AddFront(T value);
	void AddBack(T value);

	void Remove(int index);
	void RemoveFront();
	void RemoveBack();

	void SortAsInt();

	DoubleLinkedList<T> Copy();



	bool IsEmpty() { return size == 0; }
	int GetSize() { return size; }
	T GetFirst() { return Front != nullptr ? Front->value : NULL;  }
	T GetLast() { return End != nullptr ? End->value : NULL; }

	T GetValue(int index);

	void PrintAllValues();

	void Clear();

private:
	ListElement<T>* Front;
	ListElement<T>* End;

	int size = 0;
};

template<typename T>
inline DoubleLinkedList<T>::DoubleLinkedList()
{
}

template<typename T>
inline DoubleLinkedList<T>::~DoubleLinkedList()
{
	Clear();
}


template<typename T>
inline DoubleLinkedList<T> DoubleLinkedList<T>::Copy()
{
	DoubleLinkedList<T> copy = DoubleLinkedList<T>();


	return ;
}


template<typename T>
inline void DoubleLinkedList<T>::Add(T value, int index)
{
	// If index trying to be inserted is the past the last element
	if (index >= size) {
		AddBack(value);
		return;
	}
	// If index trying to be inserted is the first element
	if (index <= 0) {
		AddFront(value);
		return;
	}

	
	// Begin from start element
	ListElement<T>* found = Front;

	// Loop until element is found
	for (int i = 0; i < index; i++) {
		found = found->next;
	}

	
	// Insert new in between 
	//			[new]
	//			  V
	// [Index-1] <-> [Found]

	// Create the new element with the previous set to the old index's previous and next set to that old index
	// [Index-1] <- [new] -> [Found]
	ListElement<T>* elmt = new ListElement<T>(value, found->previous, found);


	// Set the old index's previous value's next element to the new element
	//  [Index-1] -> [new]
	elmt->previous->next = elmt;

	
	// Replace the index's previous value with the new value
	//  [new] <- [Found]
	found->previous = elmt;

	// Result
	// [Index-1] <-> [new] <-> [Found]


	found = nullptr;
	// Increase size
	size++;
	
}

template<typename T>
inline void DoubleLinkedList<T>::AddFront(T value)
{
	// Create new element with next value set to the current front value
	ListElement<T>* elmt = new ListElement<T>(value, nullptr, Front);

	// If no elements are present
	if (size == 0) {
		End = elmt;
	}
	else {
		// Set the old front element's previous value to the new element
		Front->previous = elmt;
	}

	
	// Set the front value to the newly created element	
	Front = elmt;

	// Increase size
	size++;
}

template<typename T>
inline void DoubleLinkedList<T>::AddBack(T value)
{
	// Create new element with previous value set to the current end value
	ListElement<T>* elmt = new ListElement<T>(value, End, nullptr);

	// If no elements are present
	if (size == 0) {
		Front = elmt;
	}
	else {
		// Set the old last element's next value to the new element
		End->next = elmt;
	}

	// Set the end value to the newly created element
	End = elmt;

	// Increase size
	size++;
}

template<typename T>
inline void DoubleLinkedList<T>::Remove(int index)
{
	// If index trying to be removed is the last element
	if (index >= size - 1) {
		RemoveBack();
		return;
	}
	// If index trying to be removed is the first element
	if (index <= 0) {
		RemoveFront();
		return;
	}

	// Begin from start element
	ListElement<T>* found = Front;

	// Loop until element is found
	for (int i = 0; i < index; i++) {
		found = found->next;
	}

	// Set the element before this to have the element after this as it's next value
	found->previous->next = found->next;
	// Set the element after this to have the element before this as it's previous value
	found->next->previous = found->previous;

	// Delete the element
	delete found;
	found = nullptr;

	// Decrease size
	size--;
}

template<typename T>
inline void DoubleLinkedList<T>::RemoveFront()
{
	if (size == 0) {
		return;
	}
	if (size == 1) {
		delete Front;
		Front = nullptr;
		End = nullptr;
		size--;
		return;
	}

	// Set new first element to the second element 
	Front = Front->next;

	// From the second element, delete the previous (Which was the old first element)
	delete Front->previous;
	Front->previous = nullptr;

	// Decrease size
	size--;
}

template<typename T>
inline void DoubleLinkedList<T>::RemoveBack()
{
	if (size == 0) {
		return;
	}
	if (size == 1) {
		delete End;
		End = nullptr;
		Front = nullptr;
		size--;
		return;
	}
	// Set new first element to the second element 
	End = End->previous;

	// From the second to last element, delete the next (Which was the old last element)
	delete End->next;
	End->next = nullptr;
	

	// Decrease size
	size--;
}

template<typename T>
inline void DoubleLinkedList<T>::SortAsInt()
{
	if (size <= 1) {
		return;
	}


	DoubleLinkedList<T> copy = DoubleLinkedList<T>();
	ListElement<T>* currentElement = Front;
	copy.AddFront(Front->value);

	for (int i = 0; i < size-1; i++) {
		// Keep track of number currently being checked
		currentElement = currentElement->next;


		ListElement<T>* copyCurrentElement = copy.Front;
		int copySize = copy.GetSize();

		// Loop through each value currently in copy until the value can be placed
		for (int j = 0; j < copySize; j++) {

			// If next element is nullptr, it is at the end
			if (copyCurrentElement->next == nullptr) {

				// Is front element
				if (copyCurrentElement->previous == nullptr) {
					// Should add infront of number
					if (currentElement->value <= copyCurrentElement->value) {
						copy.AddFront(currentElement->value);
						break;
					}
				}
				
				// Else add to back
				copy.AddBack(currentElement->value);
				break;;
			}

			// If value is less than the current copy number
			if (currentElement->value <= copyCurrentElement->value) {
				copy.Add(currentElement->value, j);
				break;
			}
			// Move onto next element in copy to check
			copyCurrentElement = copyCurrentElement->next;
		}
		copyCurrentElement = nullptr;
		

	}
	currentElement = nullptr;

	Clear();

	currentElement = copy.Front;
	AddBack(currentElement->value);
	for (int i = 0; i < copy.GetSize()-1; i++) {
		currentElement = currentElement->next;
		AddBack(currentElement->value);
	}
}



template<typename T>
inline T DoubleLinkedList<T>::GetValue(int index)
{

	// Begin from start element
	ListElement<T>* found = Front;

	// Loop until element is found
	for (int i = 0; i < index; i++) {
		found = found->next;
	}

	T val = found->value;
	found = nullptr;

	return val;
}

template<typename T>
inline void DoubleLinkedList<T>::PrintAllValues()
{
	ListElement<T>* current = Front;
	for (int i = 0; i < size; i++) {
		std::cout << current->value << std::endl;
		current = current->next;
	}
	current = nullptr;
}

template<typename T>
inline void DoubleLinkedList<T>::Clear()
{
	ListElement<T>* current = Front;
	ListElement<T>* nextElmt = Front;
	for (int i = 0; i < size; i++) {
		// Store next element for later
		nextElmt = current->next;

		// Delete current
		delete current;
		current = nullptr;

		// Set current to stored next
		current = nextElmt;
	}
	size = 0;
	current = nullptr;
	nextElmt = nullptr;
}


