#include "pch.h"
#include "CState.h"


CState::CState()
	: m_pSM(nullptr)
	, m_acctime(0.f)
	, m_skillortsign(-1)
	, m_pPlayer(nullptr)
	, m_stateduration(0.f)
	, m_StateID(0)
	, m_stateskillused(false)
{
}

CState::~CState()
{
}

int CState::getSkillOrt()
{
	// 플레이어의 위치를 알아낸다.
	Vec2 vPlayerPos = m_pPlayer->GetPos();

	// 몬스터 본인의 위치를 알아낸다.
	CMonster* pMonster = dynamic_cast<CMonster*>(GetOwnerSM()->GetOwner());

	Vec2 vMonsterPos = pMonster->GetPos();

	Vec2 vDir = vPlayerPos - vMonsterPos;
	vDir.Normalize();

	return vDir.x > 0 ? 1 : -1;
}

float CState::getPlayerDist()
{
	auto Pos = GetOwner()->GetPos();
	auto PlayerPos = m_pPlayer->GetPos();
	return abs(Pos.x - PlayerPos.x);
}

void CState::Enter()
{
	m_acctime = 0;
	m_stateskillused = false;

	CObj* pOwner = GetOwner();
	pOwner->SetCollisionTime(0.f);

	CMonster* pOwnerMonster = dynamic_cast<CMonster*>(pOwner);
	if (nullptr != pOwnerMonster)
	{
		pOwnerMonster->SetAttackedFalse();
	}
}
