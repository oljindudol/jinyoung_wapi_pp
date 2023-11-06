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
	AddMonster(new ion);
	AddMonster(new ion);
	AddMonster(new ion);
	AddMonster(new ion);
	AddMonster(new ion);
	AddMonster(new ion);
	AddMonster(new ion);
	AddMonster(new ion);
	AddMonster(new ion);
	AddMonster(new ion);
	AddMonster(new ion);
	AddMonster(new ion);
	AddMonster(new ion);

}

void CMonsterMgr::tick()
{

	if (KEY_PRESSED(KEY::_2))
	{
		for (const auto& pair : m_MonsterMap)
		{
			for (const auto& p : pair.second)
			{
				if (nullptr != p->m_AI)
					p->m_AI->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
				p->m_AI->m_forcedidle = true;
			}
		}
	}

	if (KEY_PRESSED(KEY::_3))
	{
		for (const auto& pair : m_MonsterMap)
		{
			for (const auto& p : pair.second)
			{
				if (nullptr != p->m_AI)
					p->m_AI->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
				p->m_AI->m_forcedidle = false;
			}
		}
	}

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

	//��� ������ ������ �α׸� �����ʴ´�.
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
		LOG(LOG_LEVEL::LOG, (L"���͸� ã���� �����ϴ�"));
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
		LOG(LOG_LEVEL::LOG, (L"���͸� ã���� �����ϴ�"));
		return;
	}

	pMonster->Spawn(_pos);

}






