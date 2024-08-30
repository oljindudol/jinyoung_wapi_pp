#include "pch.h"
#include "CThirdBMPull.h"

CThirdBMPull::CThirdBMPull()
{
}

void CThirdBMPull::finaltick(float _DT)
{
}

void CThirdBMPull::Enter()
{
	Super::Enter();
	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"pull");
}

void CThirdBMPull::Exit()
{
}

CThirdBMPull::~CThirdBMPull()
{
}
