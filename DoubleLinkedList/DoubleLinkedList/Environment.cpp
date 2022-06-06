#include "Environment.h"
#include "Timer.h"



std::vector<Object*> Environment::objects = std::vector<Object*>();
int Environment::lifetimeObjectCount = 0;


Environment::Environment()
{

}

Environment::~Environment()
{
}

void Environment::Start()
{
    InitWindow(1200, 800, "Double Linked List");

    Timer timer = Timer();
    float DeltaTime = 0;

    
    addNumInput = new UIInputBox(GetScreenWidth() - 100, GetScreenHeight() - 100, 100, 50, 0x000000FF, 0xAAFFFFFF, 0x00FFFFFF, new UIText(0, 0, "0", 16, 0xFFFFFFFF), 100, true);
    addNumInput->intMax = 99999;
    addNumInput->intMin = 0;
    new UIText(GetScreenWidth() - 150, GetScreenHeight() - 145, "Value:", 16, 0x000000FF);

    indexInput = new UIInputBox(GetScreenWidth() - 100, GetScreenHeight() - 200, 100, 50, 0x000000FF, 0xAAFFFFFF, 0x00FFFFFF, new UIText(0, 0, "0", 16, 0xFFFFFFFF), 100, true);
    indexInput->intMax = 0;
    indexInput->intMin = 0;
    new UIText(GetScreenWidth() - 150, GetScreenHeight() - 245, "Index:", 16, 0x000000FF);

    UIButton* addBackButton = new UIButton(GetScreenWidth() - 300, GetScreenHeight() - 100, 200, 50, 0x888888FF, 0x00FF00FF, new UIText(0, 0, "Add to back", 16, 0xFFFFFFFF));
    addBackButton->AssignCallMethod(std::bind(&Environment::AddBackListElement, this)); 
    
    UIButton* removeBackButton = new UIButton(GetScreenWidth() - 550, GetScreenHeight() - 100, 200, 50, 0x888888FF, 0xFF0000FF, new UIText(0, 0, "Remove from back", 16, 0xFFFFFFFF));
    removeBackButton->AssignCallMethod(std::bind(&Environment::RemoveBackListElement, this));
    
    UIButton* removeAtButton = new UIButton(GetScreenWidth() - 300, GetScreenHeight() - 200, 200, 50, 0x888888FF, 0x88FF88FF, new UIText(0, 0, "Insert at index", 16, 0xFFFFFFFF));
    removeAtButton->AssignCallMethod(std::bind(&Environment::AddAtListElement, this));
    
    UIButton* addAtButton = new UIButton(GetScreenWidth() - 550, GetScreenHeight() - 200, 200, 50, 0x888888FF, 0xFF8888FF, new UIText(0, 0, "Remove at index", 16, 0xFFFFFFFF));
    addAtButton->AssignCallMethod(std::bind(&Environment::RemoveAtListElement, this));
    
    UIButton* sortButton = new UIButton(GetScreenWidth() - 100, GetScreenHeight() - 30, 100, 50, 0x888888FF, 0x8888FFFF, new UIText(0, 0, "Sort", 16, 0xFFFFFFFF));
    sortButton->AssignCallMethod(std::bind(&Environment::SortElements, this));

    

    while (!WindowShouldClose()) {
        DeltaTime = timer.RecordNewTime();

        Update(DeltaTime);

        Draw(DeltaTime);

    }

    delete addNumInput;
    delete indexInput;
    delete addBackButton;
    delete removeBackButton;


}

void Environment::Update(float DeltaTime)
{
    indexInput->intMax = fmaxf(doubleLinkedList.GetSize()-1, 0);
    indexInput->currentText = std::to_string( (int)fminf( std::stoi(indexInput->currentText), indexInput->intMax) );


    for (int i = 0; i < objects.size(); i++) {
        objects[i]->Update(DeltaTime);
    }
    
}

void Environment::Draw(float DeltaTime)
{
    BeginDrawing();

    ClearBackground(WHITE);

    //DrawFPS(0, 0);

    for (int i = 0; i < objects.size(); i++) {
        objects[i]->Draw();
    }

    std::string empty = doubleLinkedList.IsEmpty() ? "True" : "False";
    std::string size = std::to_string(doubleLinkedList.GetSize());

    DrawText(("Empty? " + empty).c_str(), GetScreenWidth() - 650, GetScreenHeight() - 50, 16, BLACK);
    DrawText(("Size: " + size).c_str(), GetScreenWidth() - 650, GetScreenHeight() - 30, 16, BLACK);

    std::string first = std::to_string(doubleLinkedList.GetFirst());
    std::string last = std::to_string(doubleLinkedList.GetLast());

    DrawText(("First: " + first).c_str(), GetScreenWidth() - 400, GetScreenHeight() - 50, 16, BLACK);
    DrawText(("Last: " + last).c_str(), GetScreenWidth() - 400, GetScreenHeight() - 30, 16, BLACK);


    // Write the visuals for the double linked list
    float dist = GetScreenWidth() / 10;
    for (int i = 0; i < doubleLinkedList.GetSize(); i++) {
        int x = i % 9;
        int y = i / 9;

        // Draw box for element
        DrawRectangleLinesEx({ dist + (dist * x) - 25, dist + (dist * y) - 65, 105, 105 }, 5, indexInput->currentText == std::to_string(i) ? GetColor(0x00FF00FF) : BLACK);
 
        if (i == 0) {
            // If is front element
            DrawText("Front", dist, dist-40, 16, GetColor(0xFF00FFFF));

            // If is also end element
            if (i == doubleLinkedList.GetSize() - 1) {
                DrawText("End", dist + (dist * x), dist + (dist * y) - 60, 16, GetColor(0xFF00FFFF));
            }

        }
        // If is end element
        else if (i == doubleLinkedList.GetSize() - 1) {
            DrawText("End", dist + (dist * x), dist + (dist * y) - 40, 16, GetColor(0xFF00FFFF));
        }

        // Draw index number and value of element
        DrawText(("Index: " + std::to_string(i)).c_str(), dist + (dist * x), dist + (dist * y) - 20, 16, BLACK);
        DrawText(std::to_string(doubleLinkedList.GetValue(i)).c_str(), dist+(dist*x), dist+ (dist*y), 16, BLACK);
    }

    EndDrawing();
}


void Environment::AddBackListElement()
{
    doubleLinkedList.AddBack(std::stoi(addNumInput->currentText));
}

void Environment::RemoveBackListElement()
{
    doubleLinkedList.RemoveBack();
}

void Environment::AddAtListElement()
{
    doubleLinkedList.Add(std::stoi(addNumInput->currentText), std::stoi(indexInput->currentText));
}

void Environment::RemoveAtListElement()
{
    doubleLinkedList.Remove(std::stoi(indexInput->currentText));
}

void Environment::SortElements()
{
    doubleLinkedList.SortAsInt();
}
