#include <iostream>
#include <string>
#include "DoubleLinkedList.h"

int main()
{
    DoubleLinkedList<int> test = DoubleLinkedList<int>();

    std::cout << "Add Values" << std::endl;
    test.AddBack(10);
    test.AddBack(120);
    test.AddBack(0);
    test.AddBack(90);
    test.PrintAllValues();

    std::cout << "\nSize: " << test.GetSize() << std::endl;

    std::cout << "\nRemove front" << std::endl;
    test.RemoveFront();
    test.PrintAllValues();

    std::cout << "\nSize: " << test.GetSize() << std::endl;
    
    std::cout << "\nInsert index 2" << std::endl;
    test.Add(500, 2);
    test.PrintAllValues();

    std::cout << "\nSize: " << test.GetSize() << std::endl;
    
    std::cout << "\nRemove back" << std::endl;
    test.RemoveBack();
    test.PrintAllValues();

    std::cout << "\nSize: " << test.GetSize() << std::endl;
    
    std::cout << "\nRemove index 1" << std::endl;
    test.Remove(1);
    test.PrintAllValues();

    std::cout << "\nSize: " << test.GetSize() << std::endl;

    std::cout << "\nFirst: " << test.GetFirst() << std::endl;
    std::cout << "\nLast: " << test.GetLast() << std::endl;

    /*
    std::cout << "\nCLEAR" <<  std::endl;
    test.Clear();

    std::cout << "\nIs Empty? " << test.IsEmpty() << std::endl;
    std::cout << "\nSize: " << test.GetSize() << std::endl;
   */
}
