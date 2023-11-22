#include "pch.h"
#include "CEyeofRuin_R.h"

#include "CSkillMgr.h"
#include "CLevelMgr.h"
#include "CPlayer.h"


CEyeofRuin_R::CEyeofRuin_R()
	:m_speed(0.f)
	,pPlayer(nullptr)
	,m_usetime(0.f)
	, m_dietime(0.f)
{
	m_s1 = L"second";
	m_s2 = L"eyeofruin";
	m_s3 = L"right";

	m_skillname = m_s1 + m_s2 + m_s3;

	//몇번째 스킬인지
	m_skillnum = CSkillMgr::GetInst()->FindNextSkillNumber(m_skillname);

	SetName(m_skillname + L"_" + std::to_wstring(m_skillnum));

	SetScale(Vec2(245, 245));

	//애니메이션
	m_Animator =
		AddComponent<CAnimator>(GetName() + L"Animator");

	m_Animator->
		CreateAnimation(m_s1, m_s2, L"regen",
			Vec2(0.f, 0.f), 1.f, -1, ORT_LEFT);

	m_Animator->
		CreateAnimation(m_s1, m_s2, L"use",
			Vec2(0.f, 0.f), 1.f, 0, ORT_LEFT);

	m_Animator->
		CreateAnimation(m_s1, m_s2, L"die",
			Vec2(0.f, 0.f), 1.f, -1, ORT_LEFT);


	//컬라이더
	m_Collider =
		AddComponent<CCollider>(GetName() + L"Collider");
	m_Collider->SetScale(GetScale());
	//m_Collider->m_vOffsetPos = (GetScale() / 2);

	m_skilllayer = LAYER::MONSTER_PJB;
	duration = 16.16f;
	cooltime = 0.f;
	m_att = 5.f;
	m_debuff = DEBUFF::DESTUCTION;

	m_speed = 80.f;
}


void CEyeofRuin_R::tick(float _DT)
{
	Super::tick(_DT);

	if (0.8f > m_activedtime)
	{
		return;
	}

	if (0.f == m_usetime)
	{
		m_Animator->Play(m_s1 + m_s2 + L"use");
		m_usetime = m_activedtime;
	}

	if (0.8f <= m_activedtime && (duration - 0.9f) > m_activedtime)
	{
		SetPos(	GetPos() + (pPlayer->GetPos() - GetPos()).Normalize() * m_speed * _DT);
		return;
	}

	if (0.f == m_dietime)
	{
		m_Animator->Play(m_s1 + m_s2 + L"die");
		m_dietime = m_activedtime;
	}

	if (m_dietime + 0.99f > m_activedtime)
	{
		return;
	}
	if (m_dietime + 0.99f <= m_activedtime)
	{
		Destroy();
	}

}

void CEyeofRuin_R::activate(Vec2 _beginpos, ORIENTATION _ort)
{
	pPlayer = CLevelMgr::GetInst()->GetPlayer();
	m_usetime = 0.f;
	m_dietime = 0.f;
	m_Animator->Play(m_s1 + m_s2 + L"regen");
	Super::activate(_beginpos, _ort);
}


void CEyeofRuin_R::begin()
{
	m_Collider->InitColCnt();
}

void CEyeofRuin_R::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	m_collisiontimetoplayer = 0.f;
	if (LAYER::PLAYER == (UINT)_OtherObj->GetLayerIdx())
	{
		CLevelMgr::GetInst()->GetPlayer()->GetDamaged(0.15f, DEBUFF::DESTUCTION);
	}
}

void CEyeofRuin_R::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	Super::Overlap(_OwnCol, _OtherObj, _OtherCol);
	if (_OtherObj->GetLayerIdx() == (UINT)LAYER::PLAYER)
		if (.5f < m_collisiontimetoplayer)
		{
			BeginOverlap(_OwnCol, _OtherObj, _OtherCol);
		}
}

CEyeofRuin_R::CEyeofRuin_R(const CEyeofRuin_R& _Origin)
{
}

CEyeofRuin_R::~CEyeofRuin_R()
{
}
