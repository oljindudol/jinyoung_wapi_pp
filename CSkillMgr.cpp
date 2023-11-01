#include "pch.h"
#include "CSkillMgr.h"

void CSkillMgr::init()
{
	CreateSkill(Vec2()
		,L"common", L"pinkbean", L"doublejump"
		,Vec2(100.f,0.f),1.f,-1,ORT_LEFT
		,1.f,0.f,0.f,DEBUFF::NONE
	);


}

CSkill* CSkillMgr::FindSkill(wstring _aname1, wstring _aname2, wstring _aname3)
{
	auto iter = m_skillmap.find(_aname1 + _aname2 + _aname3);

	if (iter == m_skillmap.end())
	{
		return nullptr;
	}
	return iter->second;
}

float CSkillMgr::GetCoolTime(wstring _aname1, wstring _aname2, wstring _aname3)
{
	CSkill* pskill = FindSkill(_aname1, _aname2, _aname3);
	if (nullptr == pskill)
	{
		//없는스킬 로그 띄우기
		return 0.f;
	}

	return pskill->m_leftcool;
}

void CSkillMgr::ActivateSkill(
	wstring _aname1,
	wstring _aname2,
	wstring _aname3, 
	Vec2 _pos,
	ORIENTATION _ort)
{
	CSkill* pskill = FindSkill(_aname1, _aname2, _aname3);
	if (nullptr == pskill)
	{
		//없는스킬 로그 띄우기
		return;
	}

	pskill->activate(_pos, _ort);
}


void CSkillMgr::CreateSkill(
	  Vec2 _colbox
	, wstring _aname1
	, wstring _aname2
	, wstring _aname3
	, Vec2 _animOffset 
	, float _animPlaymul 
	, int _roop 
	, ORIENTATION _ort 
	, float _duration
	, float _cooltime 
	, float _att 
	, DEBUFF _debuff 
)
{
	if (nullptr != FindSkill(_aname1, _aname2, _aname3))
	{
		//이미 있는스킬 로그 띄우기
		return;
	}

	CSkill* pNewSkill = new CSkill;

	wstring tmpstr = _aname1 + _aname2 + _aname3;

	pNewSkill->m_skillname = tmpstr; 

	//컬라이더
	pNewSkill->m_Collider =
		pNewSkill->AddComponent<CCollider>(tmpstr + L"Collider");
	pNewSkill->m_Collider->SetScale(_colbox);
	//pNewSkill -> m_Collider->SetOffsetPos(Vec2(0.f, 0.f));

	//애니메이션
	pNewSkill->m_Animator = 
		pNewSkill->AddComponent<CAnimator>(tmpstr +L"Animator");

	pNewSkill->m_Animator->
		CreateAnimation(_aname1, _aname2, _aname3, 
			_animOffset,_animPlaymul,_roop,_ort);

	pNewSkill->duration = _duration;
	pNewSkill->cooltime = _cooltime;
	pNewSkill->att = _att;
	pNewSkill->m_debuff = _debuff;




	m_skillmap.insert(pair<wstring, CSkill*>(_aname1 + _aname2 + _aname3, pNewSkill));

}


