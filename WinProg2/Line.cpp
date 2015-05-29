#include "stdafx.h"
#include "Line.h"

Line::Line()
{

}
Line::~Line()
{

}
void Line::Set(int left, int top, int right, int bottom)
{
	pointStart.x = left;
	pointStart.y = top;
	pointEnd.x = right;
	pointEnd.y = bottom;
}

void Line::draw(CDC* cdc)
{
	CPen pen(Line_Pattern, Line_Thin, color);
	cdc->SelectObject(&pen);
	cdc->MoveTo(pointStart);
	cdc->LineTo(pointEnd);
}