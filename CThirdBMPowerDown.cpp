#include "pch.h"
#include "CThirdBMPowerDown.h"

CThirdBMPowerDown::CThirdBMPowerDown()
{
}

void CThirdBMPowerDown::finaltick(float _DT)
{
}

void CThirdBMPowerDown::Enter()
{
	Super::Enter();
	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"powerdown");
}

void CThirdBMPowerDown::Exit()
{
}

CThirdBMPowerDown::~CThirdBMPowerDown()
{
}
