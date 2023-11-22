#include "pch.h"
#include "CSecondBMDie.h"

CSecondBMDie::CSecondBMDie()
{
}

void CSecondBMDie::finaltick(float _DT)
{
	m_acctime += _DT;
}

void CSecondBMDie::Enter()
{
	Super::Enter();

	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"die");
}

void CSecondBMDie::Exit()
{
}

CSecondBMDie::~CSecondBMDie()
{
}
