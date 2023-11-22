#include "pch.h"
#include "CMorningStarFall.h"
#include "CMorningStarFallDie.h"
#include "CSkillMgr.h"

CMorningStarFallDie::CMorningStarFallDie()
{
}

void CMorningStarFallDie::finaltick(float _DT)
{
	m_acctime += _DT;

	CMovement* pMov = GetMovement();
	pMov->SetVelocity(Vec2(0.f, 0.f));

	if (m_acctime > 0.7f)
	{
		CMorningStarFall* powner = dynamic_cast<CMorningStarFall*>(GetOwner());
		if (true == powner->IsMetFloor())
			CSkillMgr::GetInst()->ActivateSkill(L"secondunderdoguse", powner->GetPos(),ORT_LEFT);
		powner->Destroy();
	}
}

void CMorningStarFallDie::Enter()
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

void CMorningStarFallDie::Exit()
{

}

CMorningStarFallDie::~CMorningStarFallDie()
{
}
