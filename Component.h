
#ifndef COMPONENT_H
#define COMPONENT_H
#include <iostream>
#include <vector>  

class Component
{
public:
	virtual void Input() {
		
	}

	virtual void Render(char* Matrix, const int &Width, const int &Height) {
		
	}

	virtual void Update(std::vector<Component*> RenderableComponents, const int &Width, const int &Height, double &DeltaTime) {
		
	}

	virtual char GetSymbol() {
		return ' ';
	}

	virtual void SetX(int X) {
		OldComponentX = ComponentX;
		ComponentX = X;
	}

	virtual void SetY(int Y) {
		OldComponentY = ComponentY;
		ComponentY = Y;
	}

	virtual int GetX() {
		return ComponentX;
	}

	virtual int GetY() {
		return ComponentY;
	}

	virtual int GetOldX() {
		return OldComponentX;
	}

	virtual int GetOldY() {
		return OldComponentY;
	}

public:
	std::string ComponentId = " ";

protected:
	int ComponentX = 0;
	int ComponentY = 0;
	int OldComponentX = 0;
	int OldComponentY = 0;
	
};

#endif

