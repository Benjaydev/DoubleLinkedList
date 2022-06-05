#include <iostream>
#include <string>
#include "DoubleLinkedList.h"

#include "Environment.h"

int main()
{
	Environment* e = new Environment();
	e->Start();

	delete e;
	return 0;
}
