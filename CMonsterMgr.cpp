#include "pch.h"
#include "CMonsterMgr.h"

#include "CMonster.h"


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

void CMonsterMgr::DeActivateAllMonsters()
{
	for (const auto& pair : m_MonsterMap)
	{
		for (const auto& p : pair.second)
		{
			p->m_OnActivate = false;
		}
	}
}

void CMonsterMgr::DeActivateMonster(CMonster* _pMonster)
{
	if (nullptr != _pMonster) { _pMonster->m_OnActivate = false; }
}


void CMonsterMgr::AddMonster(CMonster* _pMonster)
{
	vector<CMonster*>* pMonsters;
	wstring monstername = _pMonster->m_monstername;

	pMonsters = FindMonster(_pMonster->m_monstername);

	//없어도 괜찮기 때문에 로그를 내지않는다.
	if (nullptr == pMonsters)
	{
		vector<CMonster*> newmonsvec;
		newmonsvec.push_back(_pMonster);
		m_MonsterMap.insert(pair<wstring, vector<CMonster*>>(monstername, newmonsvec));
	}
	else
	{
		pMonsters->push_back(_pMonster);
	}
}

vector<CMonster*>* CMonsterMgr::FindMonster(wstring _monstername)
{
	auto iter = m_MonsterMap.find(_monstername);

	if (iter == m_MonsterMap.end())
	{
		return nullptr;
	}
	return &(iter->second);
}

CMonster* CMonsterMgr::FindAvailableMonster(wstring _monstername)
{
	CMonster* pMonster = nullptr;
	vector< CMonster* >* pMonsters = FindMonster(_monstername);

	if (nullptr == pMonsters)
	{
		LOG(LOG_LEVEL::LOG, (L"몬스터를 찾을수 없습니다"));
		pMonster = nullptr;
	}
	else
	{
		for (auto p : (*pMonsters))
		{
			if (false == (p->m_OnActivate))
			{
				pMonster = p;
				break;
			}
		}
	}
	return pMonster;
}


void CMonsterMgr::SpwanMonster(wstring _monstername, Vec2 _pos)
{
	CMonster* pMonster = FindAvailableMonster(_monstername);
	if (nullptr == pMonster)
	{
		LOG(LOG_LEVEL::LOG, (L"몬스터를 찾을수 없습니다"));
		return;
	}

	pMonster->Spawn(_pos);

}






