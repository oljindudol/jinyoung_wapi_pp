#include "pch.h"
#include "CKarmaFury.h"

#include "CSkillMgr.h"
#include "CAssetMgr.h"
#include "CSound.h"
#include "CSoundMgr.h"
#include "CMonster.h"
#include "CLevelMgr.h"
#include "CPlayer.h"





CKarmaFury::CKarmaFury()
	:m_sound(nullptr)
	, m_hitboxon{false,false, false, false ,false}
	, m_player(nullptr)
{
	m_s1 = L"common";
	m_s2 = L"karmafury";
	m_s3 = L"use";

	m_skillname = m_s1 + m_s2 + m_s3;

	//몇번째 스킬인지
	m_skillnum = CSkillMgr::GetInst()->FindNextSkillNumber(m_skillname);

	SetName(m_skillname + L"_" + std::to_wstring(m_skillnum));

	SetScale(Vec2(923.f, 638.f));

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
		CreateAnimation(m_s1, m_s2, m_s3,
			Vec2(0.f, GetScale().y / -3.f), 1.f, -1, ORT_LEFT);

	m_Animator->Play(m_s1 + m_s2 + m_s3);

	m_skilllayer = LAYER::PLAYER_PJ;
	duration = 1.65f;
	cooltime = 8.f;
	m_att = 0;
	m_debuff = DEBUFF::NONE;

	int maxcnt = 14 * 2 * 5;

	//사운드
	m_sound = CAssetMgr::GetInst()->LoadSound(L"카퓨use", L"sound\\카퓨use.wav");
	m_strhitsound = L"카퓨hit";
	CSoundMgr::GetInst()->LoadMultipleSound(m_strhitsound, L"sound\\카퓨hit.wav", maxcnt);

	for (int i = 0; i < maxcnt; i++)
	{
		//hit 이펙트
		CSkillMgr::GetInst()->AddSkillEff(new CSkill
			, m_s1, m_s2, L"hit"
			, .2f, Vec2(0.f, 150.f));
	}

}

void CKarmaFury::activate(Vec2 _beginpos, ORIENTATION _ort)
{
	Super::activate(_beginpos, _ort);
	for (int i = 0; i < 5; ++i)
	{
		m_hitboxon[i] = false;
	}
	m_sound->Play();

	m_Collider->SetOffsetPos(Vec2(0.f, -2000.f));

	m_player = CLevelMgr::GetInst()->GetPlayer();
}

void CKarmaFury::tick(float _DT)
{
	Super::tick(_DT);

	SetPos(m_player->GetPos());

	m_Collider->SetOffsetPos(Vec2(0.f, -2000.f));
	

	if (1.35f < m_activedtime && false == m_hitboxon[3])
	{
		m_hitboxon[3] = true;
		m_Collider->SetOffsetPos(Vec2(0.f, GetScale().y / -3.f));
	}

	if (1.2f < m_activedtime && false == m_hitboxon[3])
	{
		m_hitboxon[3] = true;
		m_Collider->SetOffsetPos(Vec2(0.f, GetScale().y / -3.f));
	}


	if (1.05f < m_activedtime && false == m_hitboxon[2])
	{
		m_hitboxon[2] = true;
		m_Collider->SetOffsetPos(Vec2(0.f, GetScale().y / -3.f));
	}

	if (0.9f < m_activedtime && false == m_hitboxon[1])
	{
		m_hitboxon[1] = true;
		m_Collider->SetOffsetPos(Vec2(0.f, GetScale().y / -3.f));
	}

	if (0.75f < m_activedtime && false == m_hitboxon[0])
	{
		m_hitboxon[0] = true;
		m_Collider->SetOffsetPos(Vec2(0.f, GetScale().y / -3.f));
	}


}

void CKarmaFury::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{

	CMonster* pMon = dynamic_cast<CMonster*>(_OtherObj);
	if (nullptr != pMon)
	{
		if (!((UINT)ENORMAL_MON_STATE::REGEN == pMon->GetCurstateNum()
			|| (UINT)ENORMAL_MON_STATE::DIE == pMon->GetCurstateNum()))
		{
			pMon->GetDamaged(0.0001f, 14);
			CSoundMgr::GetInst()->PlayMultipleSound(m_strhitsound, 14, 0.07f);
			CSkillMgr::GetInst()->PlayMultipleEff(m_s1 + m_s2 + L"hit", 14, 0.09f, Vec2(_OtherCol->GetPos().x, _OwnCol->GetPos().y), ort);
		}
	}
}
CKarmaFury::~CKarmaFury()
{
}
