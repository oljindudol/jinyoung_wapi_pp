#include "pch.h"
#include "ChainAttack.h"
#include "CSkillMgr.h"

void ChainAttack::tick(float _DT)
{
	Super::tick(_DT);

	m_activedtime += _DT;

	if (m_activedtime > 0.1f)
	{
		SetRotation(GetRotation() + .1f);
		m_activedtime = 0.f;
	}
}

ChainAttack::ChainAttack()
{
	m_s1 = L"first";
	m_s2 = L"rulemon";
	m_s3 = L"chainattack";

	m_skillname = m_s1 + m_s2 + m_s3;

	//몇번째 스킬인지
	m_skillnum = CSkillMgr::GetInst()->FindNextSkillNumber(m_skillname);

	SetName(m_skillname + L"_" + std::to_wstring(m_skillnum));

	//컬라이더
	m_Collider =
		AddComponent<CCollider>(GetName() + L"Collider");
	m_Collider->SetScale(Vec2(300.f, 300.f));
	m_Collider->m_vOffsetPos = (Vec2(-170.f, -110.f));

	//pNewSkill -> m_Collider->SetOffsetPos(Vec2(0.f, 0.f));

	//애니메이션
	m_Animator =
		AddComponent<CAnimator>(GetName() + L"Animator");

	m_Animator->
		CreateAnimation(m_s1, m_s2, m_s3,
			Vec2(-100.f, -100.f), 1.f, -1, ORT_LEFT);

	m_skilllayer = LAYER::MONSTER_PJ;
	duration = 3.f;
	cooltime = 0.f;
	m_att = 5.f;
	m_debuff = DEBUFF::NONE;
}

ChainAttack::ChainAttack(const ChainAttack& _Origin)
{

}



void ChainAttack::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
}



ChainAttack::~ChainAttack()
{
}
