#include "pch.h"
#include "CThirdBMPush.h"

CThirdBMPush::CThirdBMPush()
{
}

void CThirdBMPush::finaltick(float _DT)
{
	m_acctime += _DT;
	if (0.6f > m_acctime)
	{
		return;
	}

	if (m_stateduration < m_acctime)
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
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
