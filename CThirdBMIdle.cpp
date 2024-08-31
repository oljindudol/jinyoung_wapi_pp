#include "pch.h"
#include "CThirdBMIdle.h"
#include "CBlackMage3.h"

CThirdBMIdle::CThirdBMIdle()
{
}

void CThirdBMIdle::finaltick(float _DT)
{
	m_acctime += _DT;
	const float vel = 50.f;

	bool IsFar = getPlayerDist() > 250.f;

	if (true == IsFar)
	{
		m_skillortsign = getSkillOrt();
		GetOwner()->ort =
			m_skillortsign < 0 ?
			ORT_LEFT : ORT_RIGHT;
		auto Pos = GetOwner()->GetPos();
		GetOwner()->SetPos(Vec2(Pos.x + m_skillortsign * vel * _DT, Pos.y));
	}

	if (m_stateduration > m_acctime)
		return;

	for (int i = 0; i < 5; ++i)
	{
		if (0.f >= (m_pBlackMage3->m_left_cool[i]))
		{
			m_pBlackMage3->m_left_cool[i] = m_pBlackMage3->m_cooltime[i];
			if (0 == i)
			{
				ActivatePower();
			}
			else if (1 == i)
			{
				if (false == IsFar)
				{
					GetOwnerSM()->ChangeState(m_pBlackMage3->m_state_numarr[i]);
				}
			}
			else
			{
				GetOwnerSM()->ChangeState(m_pBlackMage3->m_state_numarr[i]);
			}
			return;
		}
	}
}

#include "CTimeManager.h"
void CThirdBMIdle::Enter()
{
	Super::Enter();
	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"idle");

	// 레벨에 있는 플레이어를 알아낸다.
	m_pPlayer = dynamic_cast<CPlayer*>(CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));

	m_skillortsign = getSkillOrt();

	GetOwner()->ort =
		m_skillortsign < 0 ?
		ORT_LEFT : ORT_RIGHT;

	m_pBlackMage3 = dynamic_cast<CBlackMage3*>(GetOwner());
}

void CThirdBMIdle::Exit()
{
}

void CThirdBMIdle::ActivatePower()
{
	int a = rand() % 2;

	if (0 == a)
	{
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::POWER1);
	}
	else
	{
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::POWER2);
	}
}

CThirdBMIdle::~CThirdBMIdle()
{
}
