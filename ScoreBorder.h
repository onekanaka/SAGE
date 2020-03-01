#ifndef SCOREBORDER_H
#define SCOREBORDER_H
#include <string> 
#include "Component.h"  


class ScoreBorder : public Component
{
public:
	ScoreBorder(std::string Id);
	void Render(char* Matrix, const int &Width, const int &Height) override;

public:
	int Player1Score = 0;
	int Player2Score = 0;
	bool IsPressSpace = false;

};

#endif