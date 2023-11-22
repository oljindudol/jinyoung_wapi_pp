#include "pch.h"
#include "CSecondBMEyeofRuin.h"

CSecondBMEyeofRuin::CSecondBMEyeofRuin()
{
}

void CSecondBMEyeofRuin::finaltick(float _DT)
{
	m_acctime += _DT;
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
