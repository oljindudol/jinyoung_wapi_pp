#include "pch.h"
#include "CThirdBMPowerDown.h"

CThirdBMPowerDown::CThirdBMPowerDown()
{
}

void CThirdBMPowerDown::finaltick(float _DT)
{
	m_acctime += _DT;
	if (m_stateduration < m_acctime)
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
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
