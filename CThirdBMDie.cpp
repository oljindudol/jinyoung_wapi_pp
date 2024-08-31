#include "pch.h"
#include "CThirdBMDie.h"

CThirdBMDie::CThirdBMDie()
{
}

void CThirdBMDie::finaltick(float _DT)
{
	m_acctime += _DT;
	if (m_stateduration < m_acctime)
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
}

void CThirdBMDie::Enter()
{
	Super::Enter();
	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"die");
}

void CThirdBMDie::Exit()
{
}

CThirdBMDie::~CThirdBMDie()
{
}
