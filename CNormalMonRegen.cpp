#include "pch.h"
#include "CNormalMonRegen.h"

CNormalMonRegen::CNormalMonRegen()
{
}

CNormalMonRegen::~CNormalMonRegen()
{
}

void CNormalMonRegen::finaltick(float _DT)
{
	m_acctime += _DT;

	if (m_acctime > 4.2f)
	{
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);

	}


}

void CNormalMonRegen::Enter()
{
	Super::Enter();

	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"regen");

	CCollider* pCol = GetCollider();
	pCol->SetScale(Vec2(0.f, 0.f));
	pCol->SetOffsetPos(Vec2(0.f, 0.f));
}

void CNormalMonRegen::Exit()
{
	//GetOwner()->SetPos(GetOwner()->GetPos() + Vec2(0.f, -300.f));
}
