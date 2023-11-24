#include "pch.h"
#include "CSecondBMEyeofRuin.h"

CSecondBMEyeofRuin::CSecondBMEyeofRuin()
{
	SetName(L"ÆÄ¸êÀÇ´«");
}

void CSecondBMEyeofRuin::finaltick(float _DT)
{
	m_acctime += _DT;

	if (false == m_stateskillused
		&& 1.62f < m_acctime)
	{
		m_stateskillused = true;
		CSkillMgr::GetInst()->ActivateSkill(L"secondeyeofruinleft", GetOwner()->GetPos() + Vec2(-250,-250), ORT_LEFT);
		CSkillMgr::GetInst()->ActivateSkill(L"secondeyeofruinright", GetOwner()->GetPos() + Vec2(250, -250), ORT_LEFT);
	}


	if (m_stateduration < m_acctime)
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
}

void CSecondBMEyeofRuin::Enter()
{
	Super::Enter();

	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"eyeofruin");
}

void CSecondBMEyeofRuin::Exit()
{
}

CSecondBMEyeofRuin::~CSecondBMEyeofRuin()
{
}
