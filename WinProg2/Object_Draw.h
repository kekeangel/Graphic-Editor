#pragma once

class Object_Draw : public CObject
{
public:
	Object_Draw();
	virtual ~Object_Draw();
	virtual void Draw(CDC* pDC) = 0;

protected:
	
	CPoint pointStart;
	CPoint pointEnd;

	int Line_Pattern;
	int Line_Thin;

	

	COLORREF color;
	//virtual void DrawType(void);
	
};