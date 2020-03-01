
#include "Player2.h"

char Player2::GetSymbol() 
{
    return PlayerSymbol;
}

Player2::Player2(std::string Id, int X, int Y)
{
    ComponentId = Id;
    SetX(X);
    SetY(Y);
}

void Player2::Update(std::vector<Component*> RenderableComponents, const int &Width, const int &Height, double &DeltaTime)
{
	if (GetAsyncKeyState(VK_UP))
    {
        int YPosition = GetY();
        --YPosition;

        if (YPosition >= 1) 
        {
            SetY(YPosition);
        }
    }
    if (GetAsyncKeyState(VK_DOWN))
    {
        int YPosition = GetY();
        ++YPosition;

        if (YPosition < Height - 1) 
        {
            SetY(YPosition);
        }
    }
}

