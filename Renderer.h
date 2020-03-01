#ifndef RENDERER_H
#define RENDERER_H
#include <iostream> 
#include <string> 
#include <cstring> 
#include <vector>  
#ifdef _WIN32 
#include <windows.h>
#endif
#include "Component.h"  


class Renderer
{
public:
	void Setup();
	void Render(std::vector<Component*> RenderableComponents, double &DeltaTime); 
	void PrintFrameData(int &FrameRate);
	void Print(std::string Text, int X, int Y);

private:
	int GetScreenMatrixIndex(int x, int y);
	void SetCursorPosition(int x, int y);
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	void SetupScreen();

};

static const int ScreenWidth = 60;
static const int ScreenHeight = 15;

// We use a 1D array for faster reading and writing than a matrix[][]
static char ScreenMatrix [ScreenWidth * ScreenHeight]; 
// Previous state of the rendered screen, so we can modify only the coordinates that are different between states
static char PreviousScreenMatrix [ScreenWidth * ScreenHeight]; 

#endif
