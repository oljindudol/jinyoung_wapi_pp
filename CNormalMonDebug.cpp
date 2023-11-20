#include "pch.h"
#include "CNormalMonDebug.h"
#include "CMonsterMgr.h"

CNormalMonDebug::CNormalMonDebug()
	:chased(false)
	, stomped(false)
	, up(false)
	, m_other(nullptr)
{
}

CNormalMonDebug::~CNormalMonDebug()
{
}

void CNormalMonDebug::finaltick(float _DT)
{
	if (4.32f < m_acctime)
	{
		GetOwnerSM()->m_forcedidle = true;
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
		return;
	}

	m_acctime += _DT;

	if (0.54f > m_acctime)
	{
		return;
	}

	if (up == false && 0.f != m_acctime)
	{
		up = true;
		GetOwner()->SetPos(Vec2(GetOwner()->GetPos().x, 0.f));
	}

	if (1.3f > m_acctime)
	{
		return;
	}

	if (chased == false && 0.f != m_acctime)
	{
		chased = true;
		Vec2 vYaldaPos = m_other->GetPos();
		GetOwner()->SetPos(Vec2(vYaldaPos.x, 0.f));
	}

	if (1.3f > m_acctime)
	{
		return;
	}

	if (stomped == false && 2.95 < m_acctime)
	{
		Vec2 vYaldaPos = m_other->GetPos();
		GetOwner()->GetMovement()->SetGround(false);
		GetOwner()->SetCollisionTime(0.f);
		GetOwner()->SetPos(Vec2(vYaldaPos.x-100.f, vYaldaPos.y));
		stomped = true;
	}
}

void CNormalMonDebug::Enter()
{
	Super::Enter();

	chased = false;
	stomped = false;
	up = false;

	GetOwnerSM()->GetColliderComponent()->SetOffsetPos(Vec2(-0.f, -300.f));
	GetOwnerSM()->GetColliderComponent()->SetScale(Vec2(200.f, 600.f));

	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"attack3");
	
	m_other = (*(CMonsterMgr::GetInst()->FindMonster(L"firstyalda")))[0];
}

void CNormalMonDebug::Exit()
{
}
