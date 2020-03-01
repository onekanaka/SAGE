#include "Renderer.h"


int Renderer::GetScreenMatrixIndex(int x, int y) 
{ 
	return x + ScreenWidth * y; 
}

// Windows OS specific configuration
void Renderer::Setup() 
{
    // Set Cursor invisible
    CONSOLE_CURSOR_INFO CursorInfo;
    CursorInfo.dwSize = 1;
    CursorInfo.bVisible = FALSE;

    // Set Screen Size
    CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo; 

    COORD ConsoleWindowCoordinates;
    ConsoleWindowCoordinates.X = ScreenWidth;
    ConsoleWindowCoordinates.Y = ScreenHeight + 5;

    SetConsoleScreenBufferSize(ConsoleHandle, ConsoleWindowCoordinates);
	SetConsoleCursorInfo(ConsoleHandle, &CursorInfo);

	SetupScreen();
}

void Renderer::SetupScreen() 
{
	// Custom code we decide to add to the Screen from the beginning
	for (int Y = 0; Y < ScreenHeight; Y++) 
	{
		for (int X = 0; X < ScreenWidth; X++) 
		{
			if (X == 0 || X == ScreenWidth - 1 || Y == 0 || Y == ScreenHeight - 1) {
				ScreenMatrix[GetScreenMatrixIndex(X, Y)] = '*';
			}
		}
	}
}

void Renderer::SetCursorPosition(int X, int Y)
{
    std::cout.flush();
    COORD ConsoleCoordinate = { (SHORT)X, (SHORT)Y };
    SetConsoleCursorPosition(ConsoleHandle, ConsoleCoordinate);
}

void Renderer::Print(std::string Text, int X, int Y) 
{
	SetCursorPosition(X, Y);
    std::cout << Text;
}

void Renderer::PrintFrameData(int &FrameRate)
{
	Print("Frame Rate: " + std::to_string(FrameRate) + "fps", 0, ScreenHeight + 2);
}

void Renderer::Render(std::vector<Component*> RenderableComponents, double &DeltaTime) 
{
	// Clean our Screen Matrix for the new frame
	std::fill_n(ScreenMatrix, ScreenWidth * ScreenHeight, 0);

  	for (Component* RenderableComponent : RenderableComponents) 
	{
		// Here the Renderer reads the Components' main symbol position
		// and the component doesn't need to know about anything else
		// the game takes care if the Component::Update function is used
		if (RenderableComponent->GetX() >= 0 && RenderableComponent->GetX() < ScreenWidth &&
		RenderableComponent->GetY() >= 0 && RenderableComponent->GetY() < ScreenHeight) 
		{
			ScreenMatrix[GetScreenMatrixIndex(RenderableComponent->GetX(), RenderableComponent->GetY())] = RenderableComponent->GetSymbol();
		}
		// This is another way where we can write directly to the Renderer's matrix inside the Component
		// Update and Drawings can be done in one place
		// But the code can be longer and it could be more useful for just complicated ASCII drawings
		RenderableComponent->Render(ScreenMatrix, ScreenWidth, ScreenHeight);
    }

	for (int Y = 0; Y < ScreenHeight; Y++) 
	{
		for (int X = 0; X < ScreenWidth; X++) 
		{
			// If there is any screen value at the coordinate different from the previous frame, paint the new ASCII
			if (ScreenMatrix[GetScreenMatrixIndex(X, Y)] != PreviousScreenMatrix[GetScreenMatrixIndex(X, Y)]) {
				SetCursorPosition(X, Y);
				std::cout << ScreenMatrix[GetScreenMatrixIndex(X, Y)];				
			}
		}
	}

	// The actual Screen becomes the previous old screen, 
	// and in the next frame the current Screen will be updated with the new Components positions
	std::memcpy(PreviousScreenMatrix, ScreenMatrix, ScreenWidth * ScreenHeight);
	
	std::cout.flush();
}