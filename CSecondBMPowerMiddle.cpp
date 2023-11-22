#include "pch.h"
#include "CSecondBMPowerMiddle.h"

CSecondBMPowerMiddle::CSecondBMPowerMiddle()
{
}

void CSecondBMPowerMiddle::finaltick(float _DT)
{
	m_acctime += _DT;
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
