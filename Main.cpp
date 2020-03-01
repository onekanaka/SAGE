
#include "Game.h"
#include "Player1.h"
#include "Player2.h"
#include "Ball.h"
#include "ScoreBorder.h"

// START
int main()
{
    Game MyGame;

    Player1 PlayerLeft("Player1", 4, 5);
    MyGame.AddComponent(PlayerLeft);
    Player2 PlayerRight("Player2", ScreenWidth-5, 10);
    MyGame.AddComponent(PlayerRight);
    Ball MyBall("Ball");
    MyGame.AddComponent(MyBall);
    ScoreBorder PlayerScore("ScoreBorder");
    MyGame.AddComponent(PlayerScore);

    MyGame.ShowFrameRate = true;
    MyGame.StartGame();

    return 0;
}