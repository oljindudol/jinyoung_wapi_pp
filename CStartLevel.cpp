#include "pch.h"
#include "CStartLevel.h"
#include "CKeyMan.h"
#include "CLevelMgr.h"

void CStartLevel::init()
{
}

void CStartLevel::enter()
{
}

void CStartLevel::exit()
{
	DeleteAllObjects();
}

void CStartLevel::tick()
{
	CLevel::tick();

	// Enter Ű�� ������ PlayLevel �� ��ȯ
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::PLAY_LEVEL);
	}
}
