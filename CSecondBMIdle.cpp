#include "pch.h"
#include "CSecondBMIdle.h"

CSecondBMIdle::CSecondBMIdle()
{
}

void CSecondBMIdle::finaltick(float _DT)
{
	m_acctime += _DT;
}

void CSecondBMIdle::Enter()
{
	Super::Enter();

	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"idle");
}

void CSecondBMIdle::Exit()
{
}

CSecondBMIdle::~CSecondBMIdle()
{
}
