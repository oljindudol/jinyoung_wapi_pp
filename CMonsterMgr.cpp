#include "pch.h"
#include "CMonsterMgr.h"

#include "CMonster.h"
#include "monsters.h"
#include "CKeyMgr.h"


CMonsterMgr::CMonsterMgr()
{
}

void CMonsterMgr::init()
{
	AddMonster(new ion);
	AddMonster(new yalda);
	AddMonster(new rulemon11);
	for (int i = 0; i < 30; i++)
	{
		AddMonster(new CDarkFalling);
	}
	AddMonster(new rulemon12);

	AddMonster(new CBlackMage2);

	for (int i = 0; i < 15; i++)
	{
		AddMonster(new CMorningStarFall);
	}

	AddMonster(new CGenesisEgg);


}

void CMonsterMgr::tick()
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


void CMonsterMgr::DeActivateMonster(CMonster* _pMonster)
{
	if (nullptr != _pMonster) { _pMonster->m_OnActivate = false; }
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

int CMonsterMgr::FindNextMonsterNumber(wstring _mostername)
{
	auto iter = m_MonsterMap.find(_mostername);

	if (m_MonsterMap.end() == iter)
	{
		return 0;
	}

	return (int)iter->second.size();
	
}

void CMonsterMgr::ChangeAllMonsterForcedIdle()
{
	for (const auto& pair : m_MonsterMap)
	{
		for (const auto& p : pair.second)
		{
			if (nullptr != p->m_AI)
			{
				p->m_AI->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
				p->m_AI->m_forcedidle = true;
			}
				
		}
	}
}

void CMonsterMgr::ChangeAllMonsterIdle()
{
	for (const auto& pair : m_MonsterMap)
	{
		for (const auto& p : pair.second)
		{
			if (nullptr != p->m_AI)
			{
				p->m_AI->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
				p->m_AI->m_forcedidle = false;
			}
				
		}
	}
}


void CMonsterMgr::AddMonster(CMonster* _pMonster)
{
	vector<CMonster*>* pMonsters;
	wstring monstername = _pMonster->m_monstername;

	pMonsters = FindMonster(monstername);

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

void CMonsterMgr::SpwanRuleMonster(wstring _monstername)
{
	CMonster* pMonster = FindAvailableMonster(_monstername);
	if (nullptr == pMonster)
	{
		LOG(LOG_LEVEL::LOG, (L"몬스터를 찾을수 없습니다"));
		return;
	}
	pMonster->SpawnRuleMon();
}





