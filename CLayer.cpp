#include "pch.h"
#include "CLayer.h"

#include "CObj.h"

#include "CGCMgr.h"

#include "CSkillMgr.h"
#include "CSkill.h"
#include "CMonster.h"
#include "CMonsterMgr.h"


CLayer::CLayer()
{
}

CLayer::~CLayer()
{
	DeleteAllObjects();
	//for (size_t i = 0; i < m_vecObjects.size(); ++i)
	//{
	//	delete m_vecObjects[i];
	//}
}

void CLayer::begin()
{
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
	{
		m_vecObjects[i]->begin();
	}
}

void CLayer::tick(float _DT)
{
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
	{
		m_vecObjects[i]->tick(_DT);
	}
}
void CLayer::finaltick(float _DT)
{
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
	{
		m_vecObjects[i]->finaltick(_DT);
	}
}
void CLayer::render(HDC _dc)
{
	vector<CObj*>::iterator iter = m_vecObjects.begin();
	
	LAYER idxlayer = getLayer();

	for (; iter != m_vecObjects.end();)
	{
		if ((*iter)->IsDead())
		{
			if ((LAYER::MONSTER_PJ == idxlayer) ||
				(LAYER::PLAYER_PJ == idxlayer) ||
				(LAYER::PLAYER_SKILL == idxlayer))
			{
				CSkill* pSkill = dynamic_cast<CSkill*>(*iter);
				CSkillMgr::GetInst()->DeActivateSkill(pSkill);
			}
			//if ((LAYER::MONSTER == idxlayer) )
			//{
			//	CMonster* pMonster = dynamic_cast<CMonster*>(*iter);
			//	CMonsterMgr::GetInst()->DeActivateMonster(pMonster);
			//}
			iter = m_vecObjects.erase(iter);
		}
		else
		{
			(*iter)->render(_dc);
			++iter;
		}
	}
}

void CLayer::DeleteAllObjects()
{
	for (size_t i = 0; i < m_vecObjects.size(); ++i)
	{
		LAYER idxlayer = getLayer();
		//스킬매니저에 이관
		if ((LAYER::MONSTER_PJ == idxlayer) ||
			(LAYER::PLAYER_PJ == idxlayer) ||
			(LAYER::PLAYER_SKILL == idxlayer))
		{continue;}
		//몬스터매니저에 이관
		//if ((LAYER::MONSTER) == idxlayer)
		//	continue;

		if(m_vecObjects[i])
		delete m_vecObjects[i];
	}

	m_vecObjects.clear();
}