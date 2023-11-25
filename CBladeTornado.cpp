#include "pch.h"
#include "CBladeTornado.h"

#include "CSkillMgr.h"
#include "CAssetMgr.h"
#include "CSound.h"
#include "CSoundMgr.h"
#include "CMonster.h"
#include "CLevelMgr.h"
#include "CPlayer.h"


CBladeTornado::CBladeTornado()
	:m_sound(nullptr)
	,m_hitboxoff{ false, false, false, false, false}
	, m_animon(false)
	, m_tmp_ortsign(0)
{
	m_s1 = L"common";
	m_s2 = L"bladetornado";
	m_s3 = L"use";

	m_skillname = m_s1 + m_s2 + m_s3;

	//몇번째 스킬인지
	m_skillnum = CSkillMgr::GetInst()->FindNextSkillNumber(m_skillname);

	SetName(m_skillname + L"_" + std::to_wstring(m_skillnum));

	SetScale(Vec2(500, 500));

	//컬라이더
	m_Collider =
		AddComponent<CCollider>(GetName() + L"Collider");
	m_Collider->SetScale(GetScale());
	//m_Collider->SetOffsetPos(Vec2(0.f, GetScale().y / -2.f));

	//애니메이션
	m_Animator =
		AddComponent<CAnimator>(GetName() + L"Animator");

	m_Animator->
		CreateAnimation(m_s1, m_s2, m_s3 ,
			Vec2(0.f, GetScale().y / -2.f), 1.f, 0, ORT_LEFT);

	m_Animator->
		CreateAnimation(m_s1, m_s2, L"shoot",
			Vec2(0.f, GetScale().y / -2.f +50), 1.f, 0, ORT_LEFT);


	m_Animator->Play(m_s1 + m_s2 + m_s3 );

	m_skilllayer = LAYER::PLAYER_PJ;
	duration = 1.92f;
	cooltime = 10.f;
	m_att = 0;
	m_debuff = DEBUFF::NONE;

	int maxcnt = 14 * 2 * 6;

	//사운드
	m_sound = CAssetMgr::GetInst()->LoadSound(L"블토use", L"sound\\블토use.wav");
	m_strhitsound = L"블토hit";
	CSoundMgr::GetInst()->LoadMultipleSound(m_strhitsound, L"sound\\블토hit.wav", maxcnt);

	for (int i = 0; i < maxcnt; i++)
	{
		//hit 이펙트
		CSkillMgr::GetInst()->AddSkillEff(new CSkill
			, m_s1, m_s2, L"hit"
			, .63f, Vec2(0.f, 200.f));
	}
}




void CBladeTornado::tick(float _DT)
{
	Super::tick(_DT);


	//m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Collider->SetOffsetPos(Vec2(0.f, GetScale().y / -2.f));

	if (1.5f < m_activedtime && false == m_hitboxoff[4])
	{
		m_hitboxoff[4] = true;
		m_Collider->SetOffsetPos(Vec2(0.f, -2000.f));
	}

	if (1.2f < m_activedtime && false == m_hitboxoff[3])
	{
		m_hitboxoff[3] = true;
		m_Collider->SetOffsetPos(Vec2(0.f, -2000.f));
	}

	if (1.2f < m_activedtime)
	{
		SetPos(GetPos() + Vec2( 400 * m_tmp_ortsign * _DT, 0.f));
	}

	if (0.75f < m_activedtime && false == m_hitboxoff[2])
	{
		m_hitboxoff[2] = true;
		m_Collider->SetOffsetPos(Vec2(0.f, -2000.f));

		m_Animator->Play(m_s1 + m_s2 + L"shoot");
	}
	

	if (0.5f < m_activedtime && false == m_hitboxoff[1])
	{
		m_hitboxoff[1] = true;
		m_Collider->SetOffsetPos(Vec2(0.f, -2000.f));
	}

	if (0.25f < m_activedtime && false == m_hitboxoff[0])
	{
		m_hitboxoff[0] = true;
		m_Collider->SetOffsetPos(Vec2(0.f, -2000.f));
	}

}


void CBladeTornado::activate(Vec2 _beginpos, ORIENTATION _ort)
{
	Super::activate(_beginpos, _ort);
	for (int i = 0; i < 5; ++i)
	{
		m_hitboxoff[i] = false;
	}
	m_animon = false;
	m_sound->Play();

	m_Animator->Play(m_s1 + m_s2 + m_s3);

	//m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Collider->SetOffsetPos(Vec2(0.f, GetScale().y / -2.f));

	m_tmp_ortsign = ORT_LEFT == _ort ? -1 : 1;
}

void CBladeTornado::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
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
			pMon->GetDamaged(0.001f, cnt);
			CSoundMgr::GetInst()->PlayMultipleSound(m_strhitsound, cnt, 0.07f);
			CSkillMgr::GetInst()->PlayMultipleEff(m_s1 + m_s2 + L"hit", cnt, 0.09f, Vec2(_OtherCol->GetPos().x, _OwnCol->GetPos().y), ort);
		}
	}
}


CBladeTornado::~CBladeTornado()
{
}
