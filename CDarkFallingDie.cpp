#include "pch.h"
#include "CDarkFallingDie.h"

CDarkFallingDie::CDarkFallingDie()
{
}

CDarkFallingDie::~CDarkFallingDie()
{
}

void CDarkFallingDie::finaltick(float _DT)
{
	m_acctime += _DT;

	if (m_acctime > .4f)
	{
		GetOwner()->Destroy();
	}
}

void CDarkFallingDie::Enter()
{
	Super::Enter();

	CMovement* pMov = GetMovement();
	pMov->SetVelocity(Vec2(0.f, 0.f));

	CAnimator* pAni = GetAnimator();
	CMonster* pCMon = dynamic_cast<CMonster*>(GetOwner());
	if (nullptr != pCMon)
	{
		pAni->Play(pCMon->GetMonName() + L"die");
	}
}

void CDarkFallingDie::Exit()
{

}
