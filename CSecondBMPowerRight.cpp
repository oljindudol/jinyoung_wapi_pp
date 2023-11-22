#include "pch.h"
#include "CSecondBMPowerRight.h"

CSecondBMPowerRight::CSecondBMPowerRight()
{
}

void CSecondBMPowerRight::finaltick(float _DT)
{
	m_acctime += _DT;
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
