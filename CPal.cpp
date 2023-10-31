#include "pch.h"
#include "CPal.h"



CPal::CPal() {
	vhp.push_back(CreatePen(PS_SOLID, 1, RGB_BLACK));
	vhp.push_back(CreatePen(PS_SOLID, 1, RGB_RED));
	vhp.push_back(CreatePen(PS_SOLID, 1, RGB_GREEN));
	vhp.push_back(CreatePen(PS_SOLID, 1, RGB_BLUE));
	vhp.push_back(CreatePen(PS_SOLID, 1, RGB_WHITE));
	vhp.push_back(CreatePen(PS_SOLID, 1, RGB_YELLOW));

	vhb.push_back(CreateSolidBrush(RGB_BLACK));
	vhb.push_back(CreateSolidBrush(RGB_RED));
	vhb.push_back(CreateSolidBrush(RGB_GREEN));
	vhb.push_back(CreateSolidBrush(RGB_BLUE));
	vhb.push_back(CreateSolidBrush(RGB_WHITE));
	vhb.push_back(CreateSolidBrush(RGB_YELLOW));
}


CPal::~CPal() {
	for (size_t i = 0; i < vhp.size(); ++i)
	{
		DeleteObject(vhp[i]);
	}
	for (size_t i = 0; i < vhb.size(); ++i)
	{
		DeleteObject(vhb[i]);
	}
}

HPEN CPal::getHPen(COLOR _COLOR)
{
	return vhp[_COLOR];
}

HBRUSH CPal::getHBrush(COLOR _COLOR)
{
	return vhb[_COLOR];
}
