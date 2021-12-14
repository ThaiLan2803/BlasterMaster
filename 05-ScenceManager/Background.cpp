#include "Background.h"
#include "Rect.h"

CBackground::CBackground()
{

}

void CBackground::Render()
{
	animation_set->at(0)->Render(x, y);
}

void CBackground::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	
}