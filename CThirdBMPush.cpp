#include "pch.h"
#include "CThirdBMPush.h"

CThirdBMPush::CThirdBMPush()
{
}

void CThirdBMPush::finaltick(float _DT)
{
}

void CThirdBMPush::Enter()
{
	Super::Enter();
	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"push");
}

void CThirdBMPush::Exit()
{
}

CThirdBMPush::~CThirdBMPush()
{
}
