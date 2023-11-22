#include "pch.h"
#include "CSecondBMMorningStarFall.h"

CSecondBMMorningStarFall::CSecondBMMorningStarFall()
{
}

void CSecondBMMorningStarFall::finaltick(float _DT)
{
	m_acctime += _DT;
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
