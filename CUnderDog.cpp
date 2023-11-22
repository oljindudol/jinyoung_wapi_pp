#include "pch.h"
#include "CUnderDog.h"

#include "CSkillMgr.h"
#include "CLevelMgr.h"
#include "CPlayer.h"

CUnderDog::CUnderDog()
	:m_MetWallTime(0.f)
{
	m_s1 = L"second";
	m_s2 = L"underdog";
	m_s3 = L"use";

	m_skillname = m_s1 + m_s2 + m_s3;

	//몇번째 스킬인지
	m_skillnum = CSkillMgr::GetInst()->FindNextSkillNumber(m_skillname);

	SetName(m_skillname + L"_" + std::to_wstring(m_skillnum));

	SetScale(Vec2(80, 90));

	//pNewSkill -> m_Collider->SetOffsetPos(Vec2(0.f, 0.f));

	//애니메이션
	m_Animator =
		AddComponent<CAnimator>(GetName() + L"Animator");

	m_Animator->
		CreateAnimation(m_s1, m_s2, m_s3,
			Vec2(0.f, 0.f), 1.f, 7, ORT_LEFT);

	m_Animator->
		CreateAnimation(m_s1, m_s2, L"die",
			Vec2(0.f, 0.f), 1.f, -1, ORT_LEFT);


	//컬라이더
	m_Collider =
		AddComponent<CCollider>(GetName() + L"Collider");
	m_Collider->SetScale(GetScale());
	m_Collider->m_vOffsetPos = (GetScale()/2);

	m_skilllayer = LAYER::MONSTER_PJB;
	duration = 15.f;
	cooltime = 0.f;
	m_att = 5.f;
	m_debuff = DEBUFF::NONE;

}

void CUnderDog::tick(float _DT)
{
	Super::tick(_DT);

	if (0.f == m_MetWallTime)
	{
		SetPos(GetPos() + (Vec2(200.f, 0.f) * _DT));
	}
	else
	{
		if (m_MetWallTime + 0.9f < m_activedtime)
		{
			Destroy();
		}
	}

}

void CUnderDog::activate(Vec2 _beginpos, ORIENTATION _ort)
{
	m_Animator->Play(m_s1 + m_s2 + m_s3);
	Super::activate(_beginpos, _ort);
}

void CUnderDog::begin()
{
	m_MetWallTime = 0.f;
	m_Collider->InitColCnt();
}

void CUnderDog::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	m_collisiontimetoplayer = 0.f;
	if (LAYER::PLAYER == (UINT)_OtherObj->GetLayerIdx())
	{
		CLevelMgr::GetInst()->GetPlayer()->GetDamaged(0.15f, DEBUFF::DESTUCTION);
	}

	if (LAYER::WALL == (UINT)_OtherObj->GetLayerIdx())
	{
		m_MetWallTime = m_activedtime;
		m_Animator->Play(m_s1 + m_s2 + L"die");
	}
}

void CUnderDog::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	Super::Overlap(_OwnCol, _OtherObj, _OtherCol);
	if (_OtherObj->GetLayerIdx() == (UINT)LAYER::PLAYER)
		if (.7f < m_collisiontimetoplayer)
		{
			BeginOverlap(_OwnCol, _OtherObj, _OtherCol);
		}
}

CUnderDog::CUnderDog(const CUnderDog& _Origin)
{
}

CUnderDog::~CUnderDog()
{
}
