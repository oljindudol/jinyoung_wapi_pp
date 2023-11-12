#include "pch.h"

#include "CSkill.h"
#include "CSkillMgr.h"
#include "skills.h"

#include "CLogMgr.h"

CSkillMgr::CSkillMgr()
{
}

void CSkillMgr::init()
{
	AddSkill((CSkill*)new pinkbean_doublejump);
	AddSkill((CSkill*)new pinkbean_doublejump);
	AddSkill((CSkill*)new pinkbean_phantomblow);


	AddSkill((CSkill*)new ChainAttack);
	AddSkill((CSkill*)new ChainAttack);
	AddSkill((CSkill*)new ChainAttack);
	AddSkill((CSkill*)new ChainAttack);
}


CSkillMgr::~CSkillMgr()
{
	for (const auto& pair : m_skillmap)
	{
		for(const auto& p : pair.second )
		{
			delete p;
		}
	}
}

void CSkillMgr::DeActivateAllSkills()
{
	for (const auto& pair : m_skillmap)
	{
		for (const auto& p : pair.second)
		{
			p->m_OnActivate = false;
		}
	}
}

void CSkillMgr::DeActivateSkill(CSkill* _skill)
{
	if (nullptr != _skill) { _skill->m_OnActivate = false; }
}

int CSkillMgr::FindNextSkillNumber(wstring _skillname)
{
	auto iter = m_skillmap.find(_skillname);
	if (m_skillmap.end() == iter)
	{
		return 0;
	}

	return (int)iter->second.size();

}

void CSkillMgr::AddSkill(CSkill* _pSkill)
{
	vector<CSkill*>* pSkills;
	wstring skillname = _pSkill->m_skillname;
	pSkills = FindSkill(skillname);
	
	//없는지 확인하는게 당연한처리기 때문에 못찾아도 로그를 내지않는다.
	if (nullptr == pSkills)
	{
		vector<CSkill*> newskillvec;
		newskillvec.push_back(_pSkill);
		m_skillmap.insert(pair<wstring, vector<CSkill*>>(skillname, newskillvec));
	}
	else
	{
		pSkills->push_back(_pSkill);
	}
}


vector<CSkill*>* CSkillMgr::FindSkill(wstring _skillname)
{
	auto iter = m_skillmap.find(_skillname);

	if (iter == m_skillmap.end())
	{
		return nullptr;
	}
	return &(iter->second);
}



//bool CSkillMgr::IsActive(wstring _aname1, wstring _aname2, wstring _aname3)
//{
//	vector<CSkill*>* pskills = FindSkill(_aname1, _aname2, _aname3);
//	if (nullptr == pskills)
//	{
//		//없는스킬 로그 띄우기
//		return true;
//	}
//	return pskills->m_OnActivate;
//}

CSkill* CSkillMgr::FindAvailableSkill(wstring _skillname)
{
	CSkill* pSkill = nullptr;
	vector< CSkill* >* pSkills = FindSkill(_skillname);

	if (nullptr == pSkills)
	{
		LOG(LOG_LEVEL::LOG, (L"스킬을 찾을수 없습니다"));
		pSkill = nullptr;
	}
	else
	{
		for (auto p : (*pSkills))
		{
			if (false == (p->m_OnActivate))
			{
				pSkill = p;
				break;
			}
		}
	}
	return pSkill;
}


void CSkillMgr::ActivateSkill(wstring _skillname
	, Vec2 _pos
	, ORIENTATION _ort)
{
	CSkill* pskill = FindAvailableSkill(_skillname);
	if (nullptr == pskill)
	{
		LOG(LOG_LEVEL::LOG, (L"스킬을 찾을수 없습니다" + _skillname).c_str());
		return;
	}

	pskill->activate(_pos, _ort);
}



float CSkillMgr::GetCoolTime(wstring _skillname)
{
	vector<CSkill*>* pskills = FindSkill(_skillname);
	if (nullptr == pskills)
	{
		LOG(LOG_LEVEL::LOG, (L"스킬을 찾을수 없습니다"));
		return 0.f;
	}

	auto iter = pskills->begin();

	return (*iter)->cooltime;
}



float CSkillMgr::GetSkillDuration(wstring _skillname)
{
	vector<CSkill*>* pSkills = FindSkill(_skillname);
	if (nullptr == pSkills)
	{
		LOG(LOG_LEVEL::LOG, (L"스킬을 찾을수 없습니다"));
		return 0.f;
	}

	return (*pSkills)[0]->duration;
}


//void CSkillMgr::CreateSkill(
//	  Vec2 _colbox
//	, wstring _aname1
//	, wstring _aname2
//	, wstring _aname3
//	, Vec2 _animOffset 
//	, float _animPlaymul 
//	, int _roop 
//	, ORIENTATION _ort 
//	, float _duration
//	, float _cooltime 
//	, float _att 
//	, DEBUFF _debuff 
//)
//{
//	if (nullptr != FindSkill(_aname1, _aname2, _aname3))
//	{
//		//이미 있는스킬 로그 띄우기
//		return;
//	}
//
//	CSkill* pNewSkill = new CSkill;
//
//	wstring tmpstr = _aname1 + _aname2 + _aname3;
//
//	pNewSkill->m_skillname = tmpstr; 
//
//	//컬라이더
//	pNewSkill->m_Collider =
//		pNewSkill->AddComponent<CCollider>(tmpstr + L"Collider");
//	pNewSkill->m_Collider->SetScale(_colbox);
//	//pNewSkill -> m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
//
//	//애니메이션
//	pNewSkill->m_Animator = 
//		pNewSkill->AddComponent<CAnimator>(tmpstr +L"Animator");
//
//	pNewSkill->m_Animator->
//		CreateAnimation(_aname1, _aname2, _aname3, 
//			_animOffset,_animPlaymul,_roop,_ort);
//
//	pNewSkill->duration = _duration;
//	pNewSkill->cooltime = _cooltime;
//	pNewSkill->m_att = _att;
//	pNewSkill->m_debuff = _debuff;
//
//
//	m_skillmap.insert(pair<wstring, CSkill*>(_aname1 + _aname2 + _aname3, pNewSkill));
//
//}
//
//
//


