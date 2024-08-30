#include "pch.h"
#include "CThirdBMPowerUp.h"

CThirdBMPowerUp::CThirdBMPowerUp()
{
	SetName(L"À­ ±Ç´É");
}

void CThirdBMPowerUp::finaltick(float _DT)
{
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