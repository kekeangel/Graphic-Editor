#pragma once


enum Bold{
	NON, ONE, TWO, THREE, FOUR, FIVE, SIX
};

class Object_Draw
{
public:
	Object_Draw();
	virtual ~Object_Draw();

	virtual void Draw(CDC* pDC) = 0;

	virtual BOOL getselectPoint(CPoint top, CPoint bottom) = 0;

	COLORREF color;
	Bold bold;
	
};

