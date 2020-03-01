
#include "Ball.h"

char Ball::GetSymbol() 
{
    return PlayerSymbol;
}

Ball::Ball(std::string Id)
{
    ComponentId = Id;
    SetX(OriginX);
    SetY(OriginY);
}

void Ball::Update(std::vector<Component*> RenderableComponents, const int &Width, const int &Height, double &DeltaTime)
{
    // Instead of letting the game move the ball "FrameRate" screen units per second, 
    // we tell the game to move the ball only 20 screen units per second with our delta time
    // so the ball speed is not tied to the framerate anymore, it is tied now to real life time
    // There could be some flickering for the ball, but it is due to the limitation of rendering the game in such small resolution
    double DeltaX = (VelocityX * 20 * DeltaTime);
    double DeltaY = (VelocityY * 20 * DeltaTime);

    PosX = DeltaX + PosX;  
    PosY = DeltaY + PosY;

    if (PosX <= 0) 
    {
        // POINTS TO PLAYER 2
        Player2Scored = true;
        IncreaseScore = true;
        PosX = OriginX;
        PosY = OriginY;
        VelocityX = 0;
        VelocityY = 0;
    }

    if (PosX >= Width - 1) 
    { 
        // POINTS TO PLAYER 1
        Player1Scored = true;
        IncreaseScore = true;
        PosX = OriginX;
        PosY = OriginY;
        VelocityX = 0;
        VelocityY = 0;
    }

    if (PosY <= 0 || PosY >= Height - 1) 
    {
        VelocityY = VelocityY * DirectionChange;
        PosY = VelocityY + PosY;
    }

    for (Component* RenderableComponent : RenderableComponents) 
    {
        if (RenderableComponent->ComponentId == "Player1" || RenderableComponent->ComponentId == "Player2") {
            if ((int)PosX == RenderableComponent->GetX() && (int)PosY == RenderableComponent->GetY()) 
            {
                VelocityX = VelocityX * DirectionChange;
                PosX = VelocityX + PosX;
            }
        }
        if (RenderableComponent->ComponentId == "ScoreBorder") {
            if (Player1Scored)
            {
                if (IncreaseScore) {
                    ((ScoreBorder*)RenderableComponent)->IsPressSpace = true;
                    ((ScoreBorder*)RenderableComponent)->Player1Score++;
                    IncreaseScore = false;
                }
            } 

            if (Player2Scored)
            {
                if (IncreaseScore) {
                    ((ScoreBorder*)RenderableComponent)->IsPressSpace = true;
                    ((ScoreBorder*)RenderableComponent)->Player2Score++;
                    IncreaseScore = false;
                }
            }

            if (!Player2Scored && !Player1Scored) {
                ((ScoreBorder*)RenderableComponent)->IsPressSpace = false;
            }
        }
    }

    if (GetAsyncKeyState(VK_SPACE) && (Player1Scored || Player2Scored)) 
    {
        if (Player1Scored == true) {
            VelocityX = -1;
        }
        if (Player2Scored == true) {
            VelocityX = 1;
        }
        VelocityY = 1;
        Player1Scored = false;
        Player2Scored = false;
    }

    SetX(PosX);
    SetY(PosY);
}

