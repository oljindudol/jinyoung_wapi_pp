#include "pch.h"
#include "CNormalMonBind.h"

CNormalMonBind::CNormalMonBind()
{
}

CNormalMonBind::~CNormalMonBind()
{
}

void CNormalMonBind::finaltick(float _DT)
{
	m_acctime += _DT;

	if (m_acctime > 10.f)
	{
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);



	}
}

void CNormalMonBind::Enter()
{
	Super::Enter();

	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"bind");

	CCollider* pCol = GetCollider();
	pCol->SetScale(GetOwner()->GetScale());
	pCol->SetOffsetPos(Vec2(0.f, -300.f));
}

void CNormalMonBind::Exit()
{
}
