#include "pch.h"
#include "CPlayerDown.h"
#include "CKeyMgr.h"

CPlayerDown::CPlayerDown()
{
}

CPlayerDown::~CPlayerDown()
{
}

void CPlayerDown::finaltick(float _DT)
{
	CMovement* pMov = GetMovement();
	ORIENTATION& ort = GetOwner()->GetOrtOrigin();

	if (KEY_PRESSED(LALT))
	{
		pMov->SetVelocity(Vec2(pMov->GetVelocity().x, -750.f));
		GetOwnerSM()->ChangeState((UINT)PLAYER_STATE::ON_AIR);
		return;
	}


	if (KEY_TAP(KEY::LEFT))
	{
		ort = ORT_LEFT;
		GetOwnerSM()->ChangeState((UINT)PLAYER_STATE::MOVE);
		return;
	}

	if (KEY_TAP(KEY::RIGHT))
	{
		ort = ORT_RIGHT;
		GetOwnerSM()->ChangeState((UINT)PLAYER_STATE::MOVE);
		return;
	}

	if (KEY_RELEASED(DOWN))
	{
		ChangeState((UINT)PLAYER_STATE::IDLE);
		return;
	}
	if (KEY_PRESSED(X))
	{
		GetOwnerSM()->ChangeState((UINT)PLAYER_STATE::ATT_NM);
		return;
	}

}

void CPlayerDown::Enter()
{
	CAnimator* pAni = GetAnimator();
	pAni->Play(L"commonpinkbeandown");
	GetOwner()->GetComponent<CCollider>()->SetOffsetPos(Vec2(0.f, -10.f));
	GetOwner()->GetComponent<CCollider>()->SetScale(Vec2(80.f, 20.f));
}

void CPlayerDown::Exit()
{
	GetOwner()->GetComponent<CCollider>()->SetOffsetPos(Vec2(0.f, -40.f));
	GetOwner()->GetComponent<CCollider>()->SetScale(Vec2(80.f, 80.f));
}
