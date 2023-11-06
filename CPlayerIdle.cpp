#include "pch.h"
#include "CPlayerIdle.h"
#include "CKeyMgr.h"


CPlayerIdle::CPlayerIdle()
{
}

CPlayerIdle::~CPlayerIdle()
{
}

void CPlayerIdle::finaltick(float _DT)
{
	CMovement* pMov = GetMovement();
	ORIENTATION& ort = GetOwner()->GetOrtOrigin();

	if (!pMov->IsGround())
	{
		GetOwnerSM()->ChangeState((UINT)PLAYER_STATE::ON_AIR);
		return;
	}


	if (KEY_PRESSED(KEY::LEFT))
	{
		ort = ORT_LEFT;
		GetOwnerSM()->ChangeState((UINT)PLAYER_STATE::MOVE);
		return;
	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		ort = ORT_RIGHT;
		GetOwnerSM()->ChangeState((UINT)PLAYER_STATE::MOVE);
		return;
	}

	if (KEY_TAP(KEY::DOWN))
	{
		GetOwnerSM()->ChangeState((UINT)PLAYER_STATE::DOWN);
	}

	if (KEY_PRESSED(C))
	{
		GetOwnerSM()->ChangeState((UINT)PLAYER_STATE::ATT_NM);
	}

	if (KEY_PRESSED(LALT))
	{
		pMov->SetVelocity(Vec2(pMov->GetVelocity().x, -750.f));
		GetOwnerSM()->ChangeState((UINT)PLAYER_STATE::ON_AIR);
	}



}

void CPlayerIdle::Enter()
{
	CAnimator* pAni = GetAnimator();
	pAni->Play(L"commonpinkbeanidle");
}

void CPlayerIdle::Exit()
{
}




