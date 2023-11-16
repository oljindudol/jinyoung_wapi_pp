#include "pch.h"
#include "pinkbean_phantomblow.h"
#include "CSkillMgr.h"
#include "CMonster.h"

void pinkbean_phantomblow::tick(float _DT)
{
	Super::tick(_DT);
}



pinkbean_phantomblow::pinkbean_phantomblow()
{

	m_s1 = L"common";
	m_s2 = L"pinkbean";
	m_s3 = L"phantomblow";

	m_skillname = m_s1 + m_s2 + m_s3;

	//몇번째 스킬인지
	m_skillnum = CSkillMgr::GetInst()->FindNextSkillNumber(m_skillname);

	SetName(m_skillname + L"_" + std::to_wstring(m_skillnum));

	//컬라이더
	m_Collider =
		AddComponent<CCollider>(GetName() + L"Collider");
	m_Collider->SetScale(Vec2(500.f, 300.f));
	m_Collider->m_vOffsetPos=(Vec2(-170.f, -110.f));

	//pNewSkill -> m_Collider->SetOffsetPos(Vec2(0.f, 0.f));

	//애니메이션
	m_Animator =
		AddComponent<CAnimator>(GetName() + L"Animator");

	m_Animator->
		CreateAnimation(m_s1, m_s2, m_s3,
			Vec2(-100.f, -100.f), 1.f, -1, ORT_LEFT);

	m_Animator->Play(m_s1 + m_s2 + m_s3);

	m_skilllayer = LAYER::PLAYER_PJ;
	duration = .6f;
	cooltime = 0.f;
	m_att = 5.f;
	m_debuff = DEBUFF::NONE;

}

pinkbean_phantomblow::pinkbean_phantomblow(const pinkbean_phantomblow& _Origin)
{

}

void pinkbean_phantomblow::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{

	CMonster* pMon = dynamic_cast<CMonster*>(_OtherObj);
	if (nullptr != pMon)
	{
		pMon->GetDamaged(0.001f, 12);
	}


}

pinkbean_phantomblow::~pinkbean_phantomblow()
{
}

void pinkbean_phantomblow::begin()
{
	m_Collider->InitColCnt();
}
