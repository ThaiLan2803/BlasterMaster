#include "Background.h"
#include "Rect.h"

CBackground::CBackground()
{

}

void CBackground::Render()
{
	animation_set->at(0)->Render(x, yWorld);
	RenderBoundingBox();
}

void CBackground::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + this->width;
	b = y + this->height;
}
Rect CBackground::GetBoundingBox()
{
	return Rect(Point(0, 0), 0, 0 - 1);
}