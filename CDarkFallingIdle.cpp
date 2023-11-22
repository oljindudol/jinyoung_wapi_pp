#include "pch.h"
#include "CDarkFallingIdle.h"

CDarkFallingIdle::CDarkFallingIdle()
{
}

CDarkFallingIdle::~CDarkFallingIdle()
{
}

void CDarkFallingIdle::finaltick(float _DT)
{
	m_acctime += _DT;

	if (10.f < m_acctime)
	{
		ChangeState((UINT)ENORMAL_MON_STATE::DIE);
	}

}

void CDarkFallingIdle::Enter()
{
	Super::Enter();
	CMovement* pMov = GetMovement();
	pMov->SetVelocity(Vec2(0.f, 150.f));

	CAnimator* pAni = GetAnimator();
	CMonster* pCMon = dynamic_cast<CMonster*>(GetOwner());
	if (nullptr != pCMon)
	{
		pAni->Play(pCMon->GetMonName() + L"idle");
	}
}

void CDarkFallingIdle::Exit()
{
}
