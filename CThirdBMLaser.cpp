#include "pch.h"
#include "CThirdBMLaser.h"

CThirdBMLaser::CThirdBMLaser()
{
}

void CThirdBMLaser::finaltick(float _DT)
{
}

void CThirdBMLaser::Enter()
{
	Super::Enter();
	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"laser");
}

void CThirdBMLaser::Exit()
{
}

CThirdBMLaser::~CThirdBMLaser()
{
}
