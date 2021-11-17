#include "Brick.h"
#include "Rect.h"

CBrick::CBrick(float w, float h)
{
	this->height = h;
	this->width = w;
}

void CBrick::Render()
{
//	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + this->width;
	b = y + this->height;
}
Rect CBrick::GetBoundingBox()
{
	return Rect(Point(0, 0 + 6), 0, 0 - 1);
	//return new Rect();
}