#include "pch.h"
#include "pinkbean_doublejump.h"
#include "CSkillMgr.h"

void pinkbean_doublejump::tick(float _DT)
{
	Super::tick(_DT);
}



pinkbean_doublejump::pinkbean_doublejump()
{

	m_s1 = L"common";
	m_s2 = L"pinkbean";
	m_s3 = L"doublejump";

	m_skillname = m_s1 + m_s2 + m_s3;

	//몇번째 스킬인지
	auto iter = CSkillMgr::GetInst()->m_skillmap.find(m_skillname);
	if(CSkillMgr::GetInst()->m_skillmap.end() == iter) 
	{
		m_skillnum = 0;
	}
	else
	{
		m_skillnum = iter->second.size();
	}

	SetName(m_skillname + L"_" + std::to_wstring(m_skillnum));

	//컬라이더
	m_Collider =
		AddComponent<CCollider>(GetName() + L"Collider");
	m_Collider->SetScale(Vec2(0.f,0.f));
	//pNewSkill -> m_Collider->SetOffsetPos(Vec2(0.f, 0.f));

	//애니메이션
	m_Animator =
		AddComponent<CAnimator>(GetName() + L"Animator");

	m_Animator->
		CreateAnimation(m_s1, m_s2, m_s3,
			Vec2(50.f, 0.f), 1.f, -1, ORT_LEFT);

	m_skilllayer = LAYER::PLAYER_SKILL;
	duration = .6f;
	cooltime = 0.f;
	m_att = 0;
	m_debuff = DEBUFF::NONE;

}

void pinkbean_doublejump::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
}



pinkbean_doublejump::~pinkbean_doublejump()
{
}

