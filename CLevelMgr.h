#pragma once
#include "pch.h"

class CPlayer;

class CLevelMgr
{
	SINGLETON(CLevelMgr);
private:
	class CLevel* m_pCurLevel;
	CLevel* m_arrLevels[(UINT)LEVEL_TYPE::END];
	CPlayer* m_Player;
	int imag;

public:
	void imagUp() { imag++; }
	void imagDown() { imag--; }

	CPlayer* GetPlayer() {return m_Player;}
	Vec2 GetCurLevelCameraRangeX();
	Vec2 GetCurLevelCameraRangeY();
	Vec2 GetCurLevelMiddle();
	CLevel* GetCurLevel() { return m_pCurLevel; }

private:
	void ChangeLevel(LEVEL_TYPE _Type);
	//void GoStartLevel(LEVEL_TYPE _Type);

public:
	void init();
	void tick();
	void render(HDC _dc);

	friend class CTaskMgr;
};