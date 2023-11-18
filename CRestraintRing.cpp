#include "pch.h"
#include "CRestraintRing.h"
#include "pinkbean_doublejump.h"
#include "CSkillMgr.h"
#include "CAssetMgr.h"
#include "CSound.h"



CRestraintRing::CRestraintRing()
	:m_roop(false)
	,m_end(false)
	,m_sound(nullptr)
{
	m_s1 = L"common";
	m_s2 = L"restraintring";
	m_s3 = L"roop";

	m_skillname = m_s1 + m_s2 + m_s3;

	//몇번째 스킬인지
	m_skillnum = CSkillMgr::GetInst()->FindNextSkillNumber(m_skillname);

	SetName(m_skillname + L"_" + std::to_wstring(m_skillnum));

	SetScale( Vec2( 470.f, 904.f));

	//컬라이더
	m_Collider =
		AddComponent<CCollider>(GetName() + L"Collider");
	m_Collider->SetScale(GetScale());
	m_Collider->SetOffsetPos(Vec2(0.f, GetScale().y / -3.f));
	//pNewSkill -> m_Collider->SetOffsetPos(Vec2(0.f, 0.f));

	//애니메이션
	m_Animator =
		AddComponent<CAnimator>(GetName() + L"Animator");

	m_Animator->
		CreateAnimation(m_s1, m_s2, L"start",
			Vec2(-24.f, GetScale().y / -3.f), 1.f, -1, ORT_LEFT);

	m_Animator->
		CreateAnimation(m_s1, m_s2, m_s3,
			Vec2(-24.f, GetScale().y / -3.f), 1.f, 0, ORT_LEFT);

	m_Animator->
		CreateAnimation(m_s1, m_s2, L"end",
			Vec2(-24.f, GetScale().y / -3.f), 1.f, -1, ORT_LEFT);

	m_Animator->Play(m_s1 + m_s2 + L"start");

	m_skilllayer = LAYER::PLAYER_SKILL;
	duration = 15.36f;
	cooltime = 180.f;
	m_att = 0;
	m_debuff = DEBUFF::NONE;

	m_sound = CAssetMgr::GetInst()->LoadSound(L"restraintring", L"sound\\시드링use.wav");

}

void CRestraintRing::tick(float _DT)
{
	Super::tick(_DT);


	if ( (duration - .18f) < m_activedtime && (false == m_end))
	{
		m_end = true;
		m_Animator->Play(m_s1 + m_s2 + L"end");
		return;
	}

	if (0.18f < m_activedtime && (false == m_roop))
	{
		m_roop = true;
		m_Animator->Play(m_s1 + m_s2 + L"roop");
		return;
	}

}


void CRestraintRing::activate(Vec2 _beginpos, ORIENTATION _ort)
{
	Super::activate(_beginpos, _ort);
	m_end = false;
	m_roop = false;

	m_activedtime = 0.f;
	m_Animator->Play(m_s1 + m_s2 + L"start");

	m_sound->Play();

	CSkillMgr::GetInst()->PlayMultipleEff(L"commonrestraintringeff", 1, 0.f, GetPos(),ORT_LEFT );
}

void CRestraintRing::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	
}

void CRestraintRing::EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if ((UINT)LAYER::PLAYER == _OtherObj->GetLayerIdx())
	{
		Destroy();
	}
}




CRestraintRing::CRestraintRing(const CRestraintRing& _Origin)
{
}

CRestraintRing::~CRestraintRing()
{
}
