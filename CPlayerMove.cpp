#include "pch.h"
#include "CPlayerMove.h"
#include "CKeyMgr.h"

CPlayerMove::CPlayerMove()
{
}

CPlayerMove::~CPlayerMove()
{
}

void CPlayerMove::finaltick(float _DT)
{
	CMovement* pMov = GetMovement();
	ORIENTATION& ort = GetOwner()->GetOrtOrigin();

	if (KEY_PRESSED(KEY::LEFT))
	{
		ort = ORT_LEFT;
		if (400.f > abs(pMov->GetVelocity().x)) {
			pMov->AddForce(Vec2(-1000.f, 0.f));
		}
	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		ort = ORT_RIGHT;
		if (400.f > abs(pMov->GetVelocity().x))
		{
			pMov->AddForce(Vec2(1000.f, 0.f));
		}
	}

	if (KEY_RELEASED(KEY::RIGHT))
	{
		ChangeState((UINT)PLAYER_STATE::IDLE);
		return;
	}
	if (KEY_RELEASED(KEY::LEFT))
	{
		ChangeState((UINT)PLAYER_STATE::IDLE);
		return;
	}

	if (KEY_PRESSED(LALT))
	{
		pMov->SetVelocity(Vec2(pMov->GetVelocity().x, -750.f));
		GetOwnerSM()->ChangeState((UINT)PLAYER_STATE::ON_AIR);
	}

	if (KEY_TAP(KEY::DOWN))
	{
		GetOwnerSM()->ChangeState((UINT)PLAYER_STATE::DOWN);
	}

	if (KEY_PRESSED(C))
	{
		GetOwnerSM()->ChangeState((UINT)PLAYER_STATE::ATT_NM);
	}
}

void CPlayerMove::Enter()
{
	CAnimator* pAni = GetAnimator();
	pAni->Play(L"commonpinkbeanmove");
}

void CPlayerMove::Exit()
{
}
