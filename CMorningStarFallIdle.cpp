#include "pch.h"
#include "CMorningStarFallIdle.h"

CMorningStarFallIdle::CMorningStarFallIdle()
{
}

void CMorningStarFallIdle::finaltick(float _DT)
{
	m_acctime += _DT;

	auto pMov = GetMovement();
	if (1000.f > pMov->GetVelocity().Length())
	{
		pMov->AddForce(Vec2(-50.f, 50.f) * _DT);
	}

	if (10.f < m_acctime)
	{
		ChangeState((UINT)ENORMAL_MON_STATE::DIE);
	}
}

void CMorningStarFallIdle::Enter()
{
	Super::Enter();
	CMovement* pMov = GetMovement();
	pMov->SetVelocity(Vec2(0.f, 0.f));

	CAnimator* pAni = GetAnimator();
	CMonster* pCMon = dynamic_cast<CMonster*>(GetOwner());
	if (nullptr != pCMon)
	{
		pAni->Play(pCMon->GetMonName() + L"idle");
	}
}

void CMorningStarFallIdle::Exit()
{
}

CMorningStarFallIdle::~CMorningStarFallIdle()
{
}
