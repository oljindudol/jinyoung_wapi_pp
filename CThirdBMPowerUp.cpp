#include "pch.h"
#include "CThirdBMPowerUp.h"

CThirdBMPowerUp::CThirdBMPowerUp()
{
	SetName(L"À­ ±Ç´É");
}

void CThirdBMPowerUp::finaltick(float _DT)
{
	m_acctime += _DT;
	if (m_stateduration < m_acctime)
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
}

void CThirdBMPowerUp::Enter()
{
	Super::Enter();
	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"powerup");
}

void CThirdBMPowerUp::Exit()
{
}

CThirdBMPowerUp::~CThirdBMPowerUp()
{
}