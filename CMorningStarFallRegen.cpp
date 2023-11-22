#include "pch.h"
#include "CMorningStarFallRegen.h"

CMorningStarFallRegen::CMorningStarFallRegen()
{
}

void CMorningStarFallRegen::finaltick(float _DT)
{
	m_acctime += _DT;

	if (m_acctime > 0.63f)
	{
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);

	}
}

void CMorningStarFallRegen::Enter()
{
	Super::Enter();

	CMovement* pMov = GetMovement();
	pMov->SetVelocity(Vec2(0.f, 0.f));

	CAnimator* pAni = GetAnimator();
	CMonster* pCMon = dynamic_cast<CMonster*>(GetOwner());
	if (nullptr != pCMon)
	{
		pAni->Play(pCMon->GetMonName() + L"regen");
	}
}

void CMorningStarFallRegen::Exit()
{
}

CMorningStarFallRegen::~CMorningStarFallRegen()
{
}
