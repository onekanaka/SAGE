
#include "Game.h"


void Game::AddComponent(Component &NewComponent)
{
    Component* RenderComponent = &NewComponent;
    RenderableComponents.push_back(RenderComponent);
}

void Game::Input()
{
    // Reads Independent Game Input calls
}

double Game::GetDeltaTime() 
{
    // We could say the Delta Time is always the expected frame length in seconds 
    // But frames could take longer than the TargetSecondsPerFrame at any moment in a real game loop
    // So we try to kinda predict the future here in a simple way, using the amount of time the last frame took
    // and getting the average with the TargetSecondsPerFrame
    // for a roughly possible next frame duration
    return (TimeLastFrame + TargetSecondsPerFrame) / 2;
}

/**
 * Renders the list of Components once per frame
 * The FrameRate per second is limited at the beginning of the program
 */
void Game::ProcessFrame()
{
    // Cleans the terminal or console every frame for the next Render
    // Using "system("cls")" is a heavy load on the loop, 
    // So on every frame instead we do a direct call to the console in Renderer::SetCursorPosition
    // This lets us print the desired character at the exact desired Windows console coordinate
    // And better yet no more flickering with cls
    //system("cls");
    
    double DeltaTime = GetDeltaTime();

  	for (Component* RenderableComponent : RenderableComponents) 
	{
        // Call any component independent logic if any
        RenderableComponent->Input();
        // Update components info based on other components statuses and the screen size
        RenderableComponent->Update(RenderableComponents, ScreenWidth, ScreenHeight, DeltaTime);
    }
    
    // Draw all updated Components
    GameRenderer.Render(RenderableComponents, DeltaTime);
}

void Game::StartGame()
{
    GameRenderer.Setup();

    while (!IsGameFinished)
    {
        auto FrameTimeStart = std::chrono::system_clock::now();
        
        Input();
        ProcessFrame();

        auto FrameTimeEnd = std::chrono::system_clock::now();

        std::chrono::duration<double> ElapsedMilliseconds = FrameTimeEnd - FrameTimeStart;

        TotalGameTimePerSecond += ElapsedMilliseconds.count();

        if (TotalGameTimePerSecond >= (double)1) {
            if (ShowFrameRate) 
            {
                GameRenderer.PrintFrameData(FrameRate);
            }
            FrameRate = 0;
            TotalGameTimePerSecond = 0;
        }

        // Debugging example, keep commented
        // GameRenderer.Print(std::to_string(GetDeltaTime()), 0, ScreenHeight + 3);
        
        if (ElapsedMilliseconds.count() < TargetSecondsPerFrame) {
            // Cap Game Loop speed until it is time to go the next frame inside that second
            // Roughly 0.01666 seconds if the framerate is 60 fps
            for (;;) {
                FrameTimeEnd = std::chrono::system_clock::now();

                ElapsedMilliseconds = FrameTimeEnd - FrameTimeStart;

                if (ElapsedMilliseconds.count() >= TargetSecondsPerFrame) {
                    TotalGameTimePerSecond += ElapsedMilliseconds.count();

                    break;
                }       
            }
        }     
        TimeLastFrame = ElapsedMilliseconds.count();
        FrameRate++;        
    }
}
