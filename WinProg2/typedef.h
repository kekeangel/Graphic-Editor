#pragma once

enum Bold{
	NON, ONE, TWO, THREE, FOUR, FIVE, SIX
};

enum Select{
	LINE, POLYLINE, TEXT, RECTANGLE, ELLIPSE, FREELINE, EMPTY, SELECT, FILL
};

enum Command{
	NONE, MOVE, DEL, FILLCOLOR, RESIZE
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