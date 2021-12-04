#include "Brick.h"
#include "Rect.h"
#include "Utils.h"

void CBrick::Render()
{

	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}
//Rect CBrick::GetBoundingBox()
//{
//	return Rect(Point(x, yWorld + 6), BRICK_BBOX_WIDTH - 1, BRICK_BBOX_HEIGHT - 1);
//	//return new Rect();
//}