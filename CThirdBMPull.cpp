#include "pch.h"
#include "CThirdBMPull.h"

CThirdBMPull::CThirdBMPull()
{
}

void CThirdBMPull::finaltick(float _DT)
{
	m_acctime += _DT;
	if (m_stateduration < m_acctime)
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
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
