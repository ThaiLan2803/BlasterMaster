#include "BrickNoColli.h"
#include "Rect.h"
#include "Utils.h"

void BrickNoColli::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void BrickNoColli::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}