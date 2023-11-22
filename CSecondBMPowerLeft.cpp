#include "pch.h"
#include "CSecondBMPowerLeft.h"

CSecondBMPowerLeft::CSecondBMPowerLeft()
{
}

void CSecondBMPowerLeft::finaltick(float _DT)
{
	m_acctime += _DT;
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
