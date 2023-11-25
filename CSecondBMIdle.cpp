#include "pch.h"
#include "CSecondBMIdle.h"

#include "CBlackMage2.h"

CSecondBMIdle::CSecondBMIdle()
	:m_pBlackMage2(nullptr)
{
	SetName(L"대기상태");
}

void CSecondBMIdle::finaltick(float _DT)
{
	if (true == GetOwnerSM()->GetForcedIdle())
	{
		return;
	}

	m_acctime += _DT;

	if (m_stateduration > m_acctime)
		return;

	for (int i = 0; i < 5; ++i)
	{
		if (0.f >= (m_pBlackMage2->m_left_cool[i]))
		{
			m_pBlackMage2->m_left_cool[i] = m_pBlackMage2->m_cooltime[i];
			if (0 == i)
			{
				ActivatePower();
			}
			else
			{
				GetOwnerSM()->ChangeState(m_pBlackMage2->m_state_numarr[i]);
			}
			return;
		}
	}
}

void CSecondBMIdle::Enter()
{
	Super::Enter();

	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"idle");


	m_pBlackMage2 = dynamic_cast<CBlackMage2*>(GetOwner());
}

void CSecondBMIdle::ActivatePower()
{
	int a = rand() % 3;

	if (0 == a)
	{
	GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::POWER1);
	}
	else if(1 == a)
	{
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::POWER2);
	}
	else
	{
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::POWER3);
	}

}

void CSecondBMIdle::Exit()
{
}


CSecondBMIdle::~CSecondBMIdle()
{
}
