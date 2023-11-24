#include "pch.h"
#include "CSecondBMPowerRight.h"

CSecondBMPowerRight::CSecondBMPowerRight()
{
	SetName(L"오른권능");
}

void CSecondBMPowerRight::finaltick(float _DT)
{
	m_acctime += _DT;

	if (false == m_stateskillused
		&& 2.61f < m_acctime)
	{
		CSkillMgr::GetInst()->ActivateSkill(L"secondpowerrightuse",Vec2(990, 400), ORT_LEFT);
		m_stateskillused = true;
	}
	if (m_stateduration < m_acctime)
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
}

void CSecondBMPowerRight::Enter()
{
	Super::Enter();

	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"powerright");
}

void CSecondBMPowerRight::Exit()
{
}

CSecondBMPowerRight::~CSecondBMPowerRight()
{
}
