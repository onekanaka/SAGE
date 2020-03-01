
#include "ScoreBorder.h"


ScoreBorder::ScoreBorder(std::string Id)
{
    ComponentId = Id;
}

void ScoreBorder::Render(char* Matrix, const int &Width, const int &Height)
{
    for (int X = 0; X < Width; X++) 
    {
        for (int Y = 0; Y < Height; Y++)
		{
            std::string SpaceMe = "PRESS SPACE";
            if (IsPressSpace && X == (Width / 2) - (SpaceMe.size() / 2)  && Y == Height - 2) {
                for (int Size= 0; Size < SpaceMe.size(); Size++) {
                    Matrix[(X + Size) + Width * Y] = SpaceMe[Size];
                }
            }

			if (Y == 0 || Y == Height - 1) {
				Matrix[X + Width * Y] = '*';
			}

            if (X == (Width / 4) && Y == 1) {
                std::string Score1 = " " + std::to_string(Player1Score) + " ";
                for (int Size= 0; Size < Score1.size(); Size++) {
                    Matrix[(X + Size) + Width * Y] = Score1[Size];
                }
            }
            
            if (X == (Width / 4) * 3 && Y == 1) {
                std::string Score2 = " " + std::to_string(Player2Score) + " ";
                for (int Size= 0; Size < Score2.size(); Size++) {
                    Matrix[(X + Size) + Width * Y] = Score2[Size];
                }
            }
		}
	}
}