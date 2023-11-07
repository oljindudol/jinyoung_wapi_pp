#pragma once
#include "pch.h"

class CPlayer;

class CLevelMgr
{
	SINGLETON(CLevelMgr);
private:
	class CLevel* m_pCurLevel;
	CLevel* m_arrLevels[(UINT)LEVEL_TYPE::END];

public:
	CPlayer* GetCurLevelPlayer();
	CLevel* GetCurLevel() { return m_pCurLevel; }

private:
	void ChangeLevel(LEVEL_TYPE _Type);
	void GoStartLevel(LEVEL_TYPE _Type);

public:
	void init();
	void tick();
	void render(HDC _dc);

	friend class CTaskMgr;
};