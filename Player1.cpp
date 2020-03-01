
#include "Player1.h"

char Player1::GetSymbol() 
{
    return PlayerSymbol;
}

Player1::Player1(std::string Id, int X, int Y)
{
    ComponentId = Id;
    SetX(X);
    SetY(Y);
}

void Player1::Update(std::vector<Component*> RenderableComponents, const int &Width, const int &Height, double &DeltaTime)
{
    if (GetAsyncKeyState(0x57)) //W
    {
       int YPosition = GetY();
        --YPosition;

        if (YPosition >= 1) 
        {
            SetY(YPosition);
        }
    }
    if (GetAsyncKeyState(0x53)) //S
    {
        int YPosition = GetY();
        ++YPosition;

        if (YPosition < Height - 1) 
        {
            SetY(YPosition);
        }
    }


}

