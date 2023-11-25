#include "pch.h"
#include "CGEggHit.h"

CGEggHit::CGEggHit()
{
}

void CGEggHit::finaltick(float _DT)
{
	m_acctime += _DT;

	if (m_stateduration < m_acctime)
	{
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
	}
}

void CGEggHit::Enter()
{
	Super::Enter();

	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"hit");
}

void CGEggHit::Exit()
{
}

CGEggHit::~CGEggHit()
{
}
