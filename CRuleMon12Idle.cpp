#include "pch.h"
#include "CRuleMon12Idle.h"

CRuleMon12Idle::CRuleMon12Idle()
{
}

CRuleMon12Idle::~CRuleMon12Idle()
{
}

void CRuleMon12Idle::finaltick(float _DT)
{
	if (GetOwnerSM()->GetForcedIdle())
		return;

	m_acctime += _DT;

	if (3.f < m_acctime)
	{
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::ATTACK1);
	}
}

void CRuleMon12Idle::Enter()
{
	m_acctime = 0.f;
}

void CRuleMon12Idle::Exit()
{
}
