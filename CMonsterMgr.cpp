#include "pch.h"
#include "CMonsterMgr.h"

class CMonster;


CMonsterMgr::CMonsterMgr()
{
}

void CMonsterMgr::init()
{

}

CMonsterMgr::~CMonsterMgr()
{
	for (const auto& pair : m_MonsterMap)
	{
		for (const auto& p : pair.second)
		{
			delete p;
		}
	}
}


void CMonsterMgr::SpwanMonster(wstring _monstername, Vec2 _pos)
{
}

CMonster* CMonsterMgr::FindAvailableMonster(wstring _monstername)
{
	return nullptr;
}

vector<CMonster*>& CMonsterMgr::FindMonster(wstring _monstername)
{
	// TODO: ���⿡ return ���� �����մϴ�.

}

void CMonsterMgr::AddMonster(CMonster* _pMonster)
{
}
