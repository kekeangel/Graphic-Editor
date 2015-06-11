#pragma once

enum Bold{
	NON, ONE, TWO, THREE, FOUR, FIVE, SIX
};

enum Select{
	LINE, POLYLINE, TEXT, RECTANGLE, ELLIPSE, FREELINE, EMPTY, SELECT
};

enum Command{
	NONE, MOVE, DEL, FILLCOLOR, RESIZE, LINECOLOR, SETBOLD, SETTYPE, BRUSH
};

struct style{
	COLORREF font_color;
	LOGFONT lf;
	UINT fontsize;
	BOOL isBold;
	BOOL isItalic;
	BOOL isStrikeout;
	BOOL isUnderline;
};