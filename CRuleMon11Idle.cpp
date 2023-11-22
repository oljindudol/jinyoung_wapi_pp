#include "pch.h"
#include "CRuleMon11Idle.h"


CRuleMon11Idle::CRuleMon11Idle()
{
}

CRuleMon11Idle::~CRuleMon11Idle()
{
}

void CRuleMon11Idle::finaltick(float _DT)
{
	if (GetOwnerSM()->GetForcedIdle())
		return;

	m_acctime += _DT;

	if (6.f < m_acctime)
	{
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::ATTACK1);
	}

}

void CRuleMon11Idle::Enter()
{
	m_acctime = 0.f;
}

void CRuleMon11Idle::Exit()
{
}
