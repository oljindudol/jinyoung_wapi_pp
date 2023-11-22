#include "pch.h"
#include "CSecondBMBlindness.h"

CSecondBMBlindness::CSecondBMBlindness()
{
}

void CSecondBMBlindness::finaltick(float _DT)
{
	m_acctime += _DT;
}

void CSecondBMBlindness::Enter()
{
	Super::Enter();

	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"blindness");
}

void CSecondBMBlindness::Exit()
{
}

CSecondBMBlindness::~CSecondBMBlindness()
{
}
