#include "pch.h"
#include "CSecondBMPowerLeft.h"

CSecondBMPowerLeft::CSecondBMPowerLeft()
{
	SetName(L"¿ÞÂÊ±Ç´É");
}

void CSecondBMPowerLeft::finaltick(float _DT)
{
	m_acctime += _DT;
	if (false == m_stateskillused
		&& 2.61f < m_acctime)
	{
		CSkillMgr::GetInst()->ActivateSkill(L"secondpowerleftuse", Vec2(990, 400), ORT_LEFT);
		m_stateskillused = true;
	}
	if (m_stateduration < m_acctime)
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
}

void CSecondBMPowerLeft::Enter()
{
	Super::Enter();

	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"powerleft");
}

void CSecondBMPowerLeft::Exit()
{
}

CSecondBMPowerLeft::~CSecondBMPowerLeft()
{
}
