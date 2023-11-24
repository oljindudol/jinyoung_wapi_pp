#include "pch.h"
#include "CSecondBMDie.h"

CSecondBMDie::CSecondBMDie()
{
	SetName(L"авю╫╩Себ");
}

void CSecondBMDie::finaltick(float _DT)
{
	m_acctime += _DT;

	if (m_stateduration < m_acctime)
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
}

void CSecondBMDie::Enter()
{
	Super::Enter();

	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"die");
}

void CSecondBMDie::Exit()
{
}

CSecondBMDie::~CSecondBMDie()
{
}
