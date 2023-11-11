#include "pch.h"
#include "CNormalMonDie.h"
#include "CMonsterMgr.h"

CNormalMonDie::CNormalMonDie()
{
}

CNormalMonDie::~CNormalMonDie()
{
}

void CNormalMonDie::finaltick(float _DT)
{
	m_acctime += _DT;
	if (m_acctime > (1.5f/ GetAnimator()->GetCurAnimmulti()) )
	{
		GetOwner()->Destroy();
	}
}

void CNormalMonDie::Enter()
{
	m_acctime = 0.f;

	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"die");

	CCollider* pCol = GetCollider();
	pCol->SetScale(Vec2(0.f, 0.f));
	//pCol->SetOffsetPos(Vec2(0.f, 0.f));
}

void CNormalMonDie::Exit()
{
}
