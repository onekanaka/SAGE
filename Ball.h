#ifndef BALL_H
#define BALL_H
#ifdef _WIN32 
#include <windows.h>
#endif

#include "Component.h"  
#include "ScoreBorder.h"


class Ball : public Component
{
public:
	Ball(std::string Id);
	void Update(std::vector<Component*> RenderableComponents, const int &Width, const int &Height, double &DeltaTime) override;
	char GetSymbol() override;
	bool Player1Scored = false;
	bool Player2Scored = false;

protected:
	char PlayerSymbol = 'O';
	int DirectionChange = -1;
	int VelocityX = 1;
	int VelocityY = 1;
	int OriginX = 29;
	int OriginY = 7;
	double PosX = OriginX;
	double PosY = OriginY;
	bool IncreaseScore = false;
	

};

#endif
