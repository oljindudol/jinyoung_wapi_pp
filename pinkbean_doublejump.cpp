#include "pch.h"
#include "pinkbean_doublejump.h"
#include "CSkillMgr.h"

void pinkbean_doublejump::tick(float _DT)
{
	Super::tick(_DT);
}



pinkbean_doublejump::pinkbean_doublejump()
{

	wstring s1 = L"common";
	wstring s2 = L"pinkbean";
	wstring s3 = L"doublejump";

	m_skillname = s1 + s2 + s3;
	int skillnum;

	//몇번째 스킬인지
	auto iter = CSkillMgr::GetInst()->m_skillmap.find(L"m_skillname");
	if(CSkillMgr::GetInst()->m_skillmap.end() == iter) 
	{
		skillnum = 0;
	}
	else
	{
		skillnum = iter->second.size();
	}
	SetName(m_skillname + L"_" + std::to_wstring(skillnum));

	//컬라이더
	m_Collider =
		AddComponent<CCollider>(GetName() + L"Collider");
	m_Collider->SetScale(Vec2(100,20));
	//pNewSkill -> m_Collider->SetOffsetPos(Vec2(0.f, 0.f));

	//애니메이션
	m_Animator =
		AddComponent<CAnimator>(GetName() + L"Animator");

	m_Animator->
		CreateAnimation(s1, s2, s3,
			Vec2(100.f, 0.f), 1.f, -1, ORT_LEFT);

	duration = 1.5f;
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

