#include "pch.h"
#include "CSecondBMPowerMiddle.h"

CSecondBMPowerMiddle::CSecondBMPowerMiddle()
{
	SetName(L"Áß¾Ó±Ç´É");
}

void CSecondBMPowerMiddle::finaltick(float _DT)
{
	m_acctime += _DT;
	if (false == m_stateskillused
		&& 2.61f < m_acctime)
	{
		CSkillMgr::GetInst()->ActivateSkill(L"secondpowermiddleuse", Vec2(990, 400), ORT_LEFT);
		m_stateskillused = true;
	}
	if (m_stateduration < m_acctime)
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
}

void CSecondBMPowerMiddle::Enter()
{
	Super::Enter();

	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"powermiddle");
}

void CSecondBMPowerMiddle::Exit()
{
}

CSecondBMPowerMiddle::~CSecondBMPowerMiddle()
{
}
