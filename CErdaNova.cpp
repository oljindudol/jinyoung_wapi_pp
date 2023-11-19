#include "pch.h"
#include "CErdaNova.h"

#include "CSkillMgr.h"
#include "CAssetMgr.h"
#include "CSound.h"
#include "CSoundMgr.h"
#include "CMonster.h"

CErdaNova::CErdaNova()
	:m_sound(nullptr)
	,m_hitboxon(false)
{
	m_s1 = L"common";
	m_s2 = L"erdanova";
	m_s3 = L"use";

	m_skillname = m_s1 + m_s2 + m_s3;

	//몇번째 스킬인지
	m_skillnum = CSkillMgr::GetInst()->FindNextSkillNumber(m_skillname);

	SetName(m_skillname + L"_" + std::to_wstring(m_skillnum));

	SetScale(Vec2(630.f, 510.f));

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
			Vec2(0.f, GetScale().y / -3.f), 2.f, -1, ORT_LEFT);



	m_Animator->Play(m_s1 + m_s2 + m_s3);

	m_skilllayer = LAYER::PLAYER_PJ;
	duration = 1.6f;
	cooltime = 120.f;
	m_att = 0;
	m_debuff = DEBUFF::NONE;

	//사운드
	m_strhitsound = L"노바hit";
	m_sound = CAssetMgr::GetInst()->LoadSound(L"노바use", L"sound\\노바use.wav");
	CSoundMgr::GetInst()->LoadMultipleSound(m_strhitsound, L"sound\\노바hit.wav", 10);

	for (int i = 0; i < 10; i++)
	{
		//hit 이펙트
		CSkillMgr::GetInst()->AddSkillEff(new CSkill
			, L"common", L"erdanova", L"hit"
			, .36f, Vec2(0.f, 0.f));
	}

	for (int i = 0; i < 2; i++)
	{
		//디버프 이펙트
		CSkillMgr::GetInst()->AddSkillEff(new CSkill
			, L"common", L"erdanova", L"debuff"
			, 10.f, Vec2(0.f, 0.f) ,0);
	}
}

void CErdaNova::activate(Vec2 _beginpos, ORIENTATION _ort)
{
	Super::activate(_beginpos,_ort);
	m_hitboxon = false;
	m_activedtime = 0.f;
	m_sound->Play();
	m_Collider->SetOffsetPos(Vec2(0.f, -2000.f));

}


void CErdaNova::tick(float _DT)
{
	Super::tick(_DT);

	if (0.4f < m_activedtime && false == m_hitboxon)
	{
		m_hitboxon = true;
		m_Collider->SetOffsetPos(Vec2(0.f, GetScale().y / -3.f));
	}
}

void CErdaNova::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	CMonster* pMon = dynamic_cast<CMonster*>(_OtherObj);
	if (nullptr != pMon)
	{
		if (!((UINT)ENORMAL_MON_STATE::REGEN == pMon->GetCurstateNum()
			|| (UINT)ENORMAL_MON_STATE::DIE == pMon->GetCurstateNum()))
		{
			pMon->GetDamaged(0.0001f, 5);
			pMon->GetAI()->ChangeState((UINT)ENORMAL_MON_STATE::BIND);
			CSoundMgr::GetInst()->PlayMultipleSound(L"노바hit", 5, 0.09f);
			CSkillMgr::GetInst()->PlayMultipleEff(m_s1+ m_s2+L"hit", 5, 0.09f, Vec2(_OtherCol->GetPos().x, _OwnCol->GetPos().y), ort);// - _OwnCol->GetScale().y / 2.f), ort);
			CSkillMgr::GetInst()->PlayMultipleEff(m_s1 + m_s2 + L"debuff", 1, 0.09f, Vec2(_OtherCol->GetPos().x, _OwnCol->GetPos().y), ort);
			
		}
	}

}

CErdaNova::~CErdaNova()
{
}
