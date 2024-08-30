#include "pch.h"
#include "CThirdBMIdle.h"

CThirdBMIdle::CThirdBMIdle()
{
}

void CThirdBMIdle::finaltick(float _DT)
{
}

void CThirdBMIdle::Enter()
{
	Super::Enter();
	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"idle");
}

void CThirdBMIdle::Exit()
{
}

CThirdBMIdle::~CThirdBMIdle()
{
}
