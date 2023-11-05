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

void CSkillMgr::AddSkill(CSkill* _pSkill)
{
	vector<CSkill*>* pSkills;
	wstring skillname = _pSkill->m_skillname;
	pSkills = FindSkill(skillname);

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

CSkill* CSkillMgr::FindAvailableSkill(wstring _skillname)
{
	CSkill* pSkill = nullptr;
	vector< CSkill* >* pSkills = FindSkill(_skillname);

	if (nullptr == pSkills)
	{
		pSkill =  nullptr;
	}
	else
	{
		for (auto p : (*pSkills) )
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



vector<CSkill*>* CSkillMgr::FindSkill(wstring _skillname)
{
	auto iter = m_skillmap.find(_skillname);

	if (iter == m_skillmap.end())
	{
		return nullptr;
	}
	return &(iter->second);
}

float CSkillMgr::GetCoolTime(wstring _skillname)
{
	vector<CSkill*>* pskills = FindSkill(_skillname);
	if (nullptr == pskills)
	{
		//���½�ų �α� ����
		return 0.f;
	}

	auto iter = pskills->begin();

	return (*iter)->cooltime;
}



//bool CSkillMgr::IsActive(wstring _aname1, wstring _aname2, wstring _aname3)
//{
//	vector<CSkill*>* pskills = FindSkill(_aname1, _aname2, _aname3);
//	if (nullptr == pskills)
//	{
//		//���½�ų �α� ����
//		return true;
//	}
//	return pskills->m_OnActivate;
//}

void CSkillMgr::ActivateSkill(wstring _skillname
	,Vec2 _pos
	,ORIENTATION _ort)
{
	CSkill* pskill = FindAvailableSkill(_skillname);
	if (nullptr == pskill)
	{
		//���½�ų �α� ����
		return;
	}

	pskill->activate(_pos, _ort);
}

float CSkillMgr::GetSkillDuration(wstring _skillname)
{
	vector<CSkill*>* pSkills = FindSkill(_skillname);
	if (nullptr == pSkills)
	{
		//���½�ų �α� ����
		return 0.f;
	}

	LOG(LOG_LEVEL::LOG, (L"��ųduration�� ã�ҽ��ϴ�"));//+_skillname+L"_"+ std::to_wstring((*pSkills)[0]->duration)))
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
//		//�̹� �ִ½�ų �α� ����
//		return;
//	}
//
//	CSkill* pNewSkill = new CSkill;
//
//	wstring tmpstr = _aname1 + _aname2 + _aname3;
//
//	pNewSkill->m_skillname = tmpstr; 
//
//	//�ö��̴�
//	pNewSkill->m_Collider =
//		pNewSkill->AddComponent<CCollider>(tmpstr + L"Collider");
//	pNewSkill->m_Collider->SetScale(_colbox);
//	//pNewSkill -> m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
//
//	//�ִϸ��̼�
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


