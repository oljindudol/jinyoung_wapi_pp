#pragma once
#include "pch.h"

class CPlayer;
class CMonster;

class CLevelMgr
{
	SINGLETON(CLevelMgr);
private:
	class CLevel* m_pCurLevel;
	UINT m_iCurLevelNum;
	CLevel* m_arrLevels[(UINT)LEVEL_TYPE::END];
	CPlayer* m_Player;
	FRule* m_pRule;
	float m_acctime;
	int imag;

public:
	void imagUp(); //{ imag++; }
	void imagDown();// { imag--; }

	FRule* GetpRule() { return m_pRule; }
	CMonster* GetCurLevelMon();

	CPlayer* GetPlayer() { return m_Player; }
	Vec2 GetCurLevelCameraRangeX();
	Vec2 GetCurLevelCameraRangeY();
	Vec2 GetCurLevelMiddle();
	CLevel* GetCurLevel() { return m_pCurLevel; }
	UINT GetCurLevelNum() { return m_iCurLevelNum; }

private:
	void ChangeLevel(LEVEL_TYPE _Type);
	//void GoStartLevel(LEVEL_TYPE _Type);

public:
	void init();
	void tick();
	void render(HDC _dc);

	friend class CTaskMgr;
};