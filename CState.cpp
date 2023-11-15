#include "pch.h"
#include "CState.h"


CState::CState()
	: m_pSM(nullptr)
	, m_acctime(0.f)
	, m_skillortsign(-1)
	, m_pPlayer(nullptr)
	, m_stateduration(0.f)
	, m_StateID(0)
{
}

CState::~CState()
{
}

void CState::Enter()
{
	m_acctime = 0;
	CObj* pOwner = GetOwner();
	pOwner->SetCollisionTime(0.f);

	CMonster* pOwnerMonster = dynamic_cast<CMonster*>(pOwner);
	if (nullptr != pOwnerMonster)
	{
		pOwnerMonster->SetAttackedFalse();
	}
}
