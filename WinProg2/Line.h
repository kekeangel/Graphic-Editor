#include "stdafx.h"
#include "Object_Draw.h"

class Line : public Object_Draw
{
public:
	Line();
	virtual ~Line();
	
	void virtual draw(CDC*);
	
	void virtual Set(int left, int top, int right, int bottom);
	
private:
};
