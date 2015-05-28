#pragma once

class Object_Draw
{
public:
	Object_Draw();
	virtual ~Object_Draw();
	virtual void Draw(CDC* pDC) = 0;

	COLORREF color;
	//virtual void DrawType(void);
	
};

