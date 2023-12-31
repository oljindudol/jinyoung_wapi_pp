#include "pch.h"
#include "CBladeStorm.h"

#include "CSkillMgr.h"
#include "CAssetMgr.h"
#include "CSound.h"
#include "CSoundMgr.h"
#include "CMonster.h"
#include "CLevelMgr.h"
#include "CPlayer.h"

CBladeStorm::CBladeStorm()
	:m_hitboxoff{}
	,m_sound(nullptr)
	,m_Player(nullptr)
{
	m_s1 = L"common";
	m_s2 = L"bladestorm";
	m_s3 = L"use";

	m_skillname = m_s1 + m_s2 + m_s3;

	//몇번째 스킬인지
	m_skillnum = CSkillMgr::GetInst()->FindNextSkillNumber(m_skillname);

	SetName(m_skillname + L"_" + std::to_wstring(m_skillnum));

	SetScale(Vec2(700, 350));

	//컬라이더
	m_Collider =
		AddComponent<CCollider>(GetName() + L"Collider");
	m_Collider->SetScale(GetScale());
	//m_Collider->SetOffsetPos(Vec2(0.f, GetScale().y / -2.f));

	//애니메이션
	m_Animator =
		AddComponent<CAnimator>(GetName() + L"Animator");

	m_Animator->
		CreateAnimation(m_s1, m_s2, m_s3,
			Vec2(GetScale().x / -3.f, GetScale().y / -3.f), 1.f, 0, ORT_LEFT);


	m_Animator->Play(m_s1 + m_s2 + m_s3);

	m_skilllayer = LAYER::PLAYER_PJ;
	duration = 5.10f;
	cooltime = 70.f;
	m_att = 0;
	m_debuff = DEBUFF::NONE;

	int maxcnt = 10 * 6;

	//사운드
	m_sound = CAssetMgr::GetInst()->LoadSound(L"블스use", L"sound\\블스Loop.wav");
	m_strhitsound = L"블스hit";
	CSoundMgr::GetInst()->LoadMultipleSound(m_strhitsound, L"sound\\블스hit.wav", maxcnt);

	for (int i = 0; i < maxcnt; i++)
	{
		//hit 이펙트
		CSkillMgr::GetInst()->AddSkillEff(new CSkill
			, m_s1, m_s2, L"hit"
			, .49f, Vec2(0.f, 100.f));
	}
}

void CBladeStorm::tick(float _DT)
{
	Super::tick(_DT);

	ort = m_Player->ort;
	SetPos(m_Player->GetPos());

	//m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Collider->SetOffsetPos(Vec2(GetScale().x  / -4.f, GetScale().y / -2.f));

	for (int i = 0; i < 42; ++i)
	{
		if ((0.3f * i)< m_activedtime && false == m_hitboxoff[i])
		{
			m_hitboxoff[i] = true;
			m_Collider->SetOffsetPos(Vec2(0.f, -2000.f));
			return;
		}
	}

}

void CBladeStorm::activate(Vec2 _beginpos, ORIENTATION _ort)
{
	Super::activate(_beginpos, _ort);
	for (int i = 0; i < 42; ++i)
	{
		m_hitboxoff[i] = false;
	}
	m_sound->Play();

	m_Animator->Play(m_s1 + m_s2 + m_s3);

	m_Collider->SetOffsetPos(Vec2(GetScale().x / -4.f , GetScale().y / -2.f));

	m_Player = CLevelMgr::GetInst()->GetPlayer();
}

void CBladeStorm::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	CMonster* pMon = dynamic_cast<CMonster*>(_OtherObj);
	int cnt = 10;
	if (L"firstyalda" == pMon->GetMonName()
		|| L"firstion" == pMon->GetMonName()
		)
		cnt = 5;

	if (nullptr != pMon)
	{
		if (!((UINT)ENORMAL_MON_STATE::REGEN == pMon->GetCurstateNum()
			|| (UINT)ENORMAL_MON_STATE::DIE == pMon->GetCurstateNum()))
		{
			pMon->GetDamaged(0.01f, cnt);
			CSoundMgr::GetInst()->PlayMultipleSound(m_strhitsound, cnt, 0.07f);
			CSkillMgr::GetInst()->PlayMultipleEff(m_s1 + m_s2 + L"hit", cnt, 0.09f, Vec2(_OtherCol->GetPos().x, _OwnCol->GetPos().y), ort);
		}
	}
}

CBladeStorm::~CBladeStorm()
{
}
