#include "pch.h"
#include "CThirdBMDie.h"

CThirdBMDie::CThirdBMDie()
{
}

void CThirdBMDie::finaltick(float _DT)
{
}

void CThirdBMDie::Enter()
{
	Super::Enter();
	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"die");
}

void CThirdBMDie::Exit()
{
}

CThirdBMDie::~CThirdBMDie()
{
}
