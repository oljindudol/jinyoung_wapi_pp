#include "pch.h"
#include "CDarkFallingRegen.h"

CDarkFallingRegen::CDarkFallingRegen()
{
}

CDarkFallingRegen::~CDarkFallingRegen()
{
}

void CDarkFallingRegen::finaltick(float _DT)
{
	m_acctime += _DT;

	if (m_acctime > 0.5f)
	{
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);

	}
}

void CDarkFallingRegen::Enter()
{
	m_acctime = 0.f;

	CAnimator* pAni = GetAnimator();
	CMonster* pCMon = dynamic_cast<CMonster*>(GetOwner());
	if (nullptr != pCMon)
	{
		pAni->Play(pCMon->GetMonName() + L"regen");
	}
}

void CDarkFallingRegen::Exit()
{
}
