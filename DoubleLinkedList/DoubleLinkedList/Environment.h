#pragma once
#include "UIInputBox.h"
#include "DoubleLinkedList.h"
#include "UIPanel.h"
#include "UIButton.h"
class Environment
{
public:
	Environment();
	~Environment();

	void Start();

	void Update(float DeltaTime);
	void Draw(float DeltaTime);
	
	void AddBackListElement();
	void RemoveBackListElement();

	void AddAtListElement();
	void RemoveAtListElement();

	void SortElements();

	DoubleLinkedList<int> doubleLinkedList = DoubleLinkedList<int>();;

	UIInputBox* addNumInput;
	UIInputBox* indexInput;


	void ResetGameObjects();
	

	static std::vector<Object*> objects;

	static int lifetimeObjectCount;
	static int AddObjectToGame(Object* obj) {
		objects.push_back(obj);
		lifetimeObjectCount++;
		// Return count for object id
		return lifetimeObjectCount;
	}
};

