//---------------------------------------------------------------------------

#pragma hdrstop

#include "position.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


bool DoCirclesOverlap (float x1, float y1, float r1, float x2, float y2, float r2)
{
	return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) <= (r1 + r2)*(r1 + r2);
};

bool Caught (float x1, float y1, float r1, float x2, float y2, float r2)
{
	return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) <= (r1 - r2)*(r1 - r2);
};

bool IsPointInCircle (float x1, float y1, float r1, float px, float py)
{
	return (x1 - px)*(x1 - px) + (y1 - py)*(y1 - py) < (r1 * r1);
};


