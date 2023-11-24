#include "pch.h"
#include "CSecondBMBlindness.h"
#include "CSkillMgr.h"

CSecondBMBlindness::CSecondBMBlindness()
{
	SetName(L"¾ÏÈæ½ºÅ³");
}

void CSecondBMBlindness::finaltick(float _DT)
{
	m_acctime += _DT;

	if (false == m_stateskillused
		&& 1.26f <m_acctime)
	{
		m_stateskillused = true;
		CSkillMgr::GetInst()->ActivateSkill(L"secondblindnessuse",Vec2(-1000,-1000) , ORT_LEFT);
	}

	if (m_stateduration < m_acctime)
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
}

void CSecondBMBlindness::Enter()
{
	Super::Enter();
	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"blindness");
}

void CSecondBMBlindness::Exit()
{
}

CSecondBMBlindness::~CSecondBMBlindness()
{
}
