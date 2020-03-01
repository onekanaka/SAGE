#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <chrono> 
#include <ctime>   
#include <vector>  

#include "Renderer.h"


class Game 
{
	
public:	
	virtual void StartGame();
	virtual void AddComponent(Component &NewComponent);
		
protected:
	virtual void Input();
	virtual void ProcessFrame();
	
private:
	// We use a dynamic vector that accomodates as many Components as we need
	// std::map is considerably slower 
	// and std::set is only better if std::vector is already sorted in the first place
	// For possible real improvement, consider using HArray, 
	// a third-party data structure library that claims to be the "most optimized Trie structure in the World !"
	std::vector<Component*> RenderableComponents = {};
	double GetDeltaTime();

public:
	bool ShowFrameRate = false;
	Renderer GameRenderer;

protected:
	bool IsGameFinished = false;
	const int TargetFrameRate = 60;
    const double TargetSecondsPerFrame = 1 / (double)TargetFrameRate;
    int FrameRate = 0;
    double TotalGameTimePerSecond = 0;
	double TimeLastFrame = 0;
};

#endif


