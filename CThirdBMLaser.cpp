#include "pch.h"
#include "CThirdBMLaser.h"

CThirdBMLaser::CThirdBMLaser()
{
}

void CThirdBMLaser::finaltick(float _DT)
{
	m_acctime += _DT;
	if (m_stateduration < m_acctime)
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
}

void CThirdBMLaser::Enter()
{
	Super::Enter();
	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"laser");
}

void CThirdBMLaser::Exit()
{
}

CThirdBMLaser::~CThirdBMLaser()
{
}
