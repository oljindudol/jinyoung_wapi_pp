#include "pch.h"
#include "CSecondBMMorningStarFall.h"
#include "CMonsterMgr.h"

CSecondBMMorningStarFall::CSecondBMMorningStarFall()
{
	SetName(L"���׿� ");
}

void CSecondBMMorningStarFall::finaltick(float _DT)
{
	m_acctime += _DT;

	if (false == m_stateskillused
		&& 1.28f < m_acctime)
	{
		m_stateskillused = true;
		CMonsterMgr::GetInst()->SpwanMonster(L"secondmorningstarfall", GetOwner()->GetPos() + Vec2(-800.f + 500.f * (RandomPercentHtH() )  , -250.f + 500.f * ( RandomPercentHtH())));
		CMonsterMgr::GetInst()->SpwanMonster(L"secondmorningstarfall", GetOwner()->GetPos() + Vec2(-400.f + 500.f * ( RandomPercentHtH() ) , -250.f + 500.f * ( RandomPercentHtH())));
		CMonsterMgr::GetInst()->SpwanMonster(L"secondmorningstarfall", GetOwner()->GetPos() + Vec2(500.f * ( RandomPercentHtH() * 0.5f)	   , -250.f + 500.f * ( RandomPercentHtH())));
		CMonsterMgr::GetInst()->SpwanMonster(L"secondmorningstarfall", GetOwner()->GetPos() + Vec2(400.f + 500.f * ( RandomPercentHtH() )  , -250.f + 500.f * ( RandomPercentHtH())));
		CMonsterMgr::GetInst()->SpwanMonster(L"secondmorningstarfall", GetOwner()->GetPos() + Vec2(800.f + 500.f * ( RandomPercentHtH())   , -250.f + 500.f * ( RandomPercentHtH())));
	}


	if (m_stateduration < m_acctime)
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
}

void CSecondBMMorningStarFall::Enter()
{
	Super::Enter();

	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"morningstarfall");
}

void CSecondBMMorningStarFall::Exit()
{
}

CSecondBMMorningStarFall::~CSecondBMMorningStarFall()
{
}
