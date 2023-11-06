#include "pch.h"
#include "CPlayerOnAir.h"
#include "CKeyMgr.h"

CPlayerOnAir::CPlayerOnAir()
{
}

CPlayerOnAir::~CPlayerOnAir()
{
}

void CPlayerOnAir::finaltick(float _DT)
{



	CMovement* pMov = GetMovement();
	ORIENTATION& ort = GetOwner()->GetOrtOrigin();

	if (pMov->IsGround())
	{
		GetOwnerSM()->ChangeState((UINT)PLAYER_STATE::IDLE);
		return;
	}
	if (KEY_PRESSED(KEY::LEFT))
	{
		ort = ORT_LEFT;
		if (400.f > abs(pMov->GetVelocity().x)){
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

	if (KEY_PRESSED(C))
	{
		GetOwnerSM()->ChangeState((UINT)PLAYER_STATE::ATT_NM);
	}

	if (KEY_TAP(KEY::LALT)) {
		if (2 > pMov->GetJmpCnt() && !(KEY_PRESSED(KEY::UP)))
		{
			CSkillMgr::GetInst()->ActivateSkill(L"commonpinkbeandoublejump", GetOwner()->GetPos(), ort);

				++(pMov->GetJmpCnt());
				float xvel = 700.f;
				if (ort == ORT_LEFT) xvel *= (-1);
				pMov->SetVelocity(Vec2(xvel, pMov->GetVelocity().y - 300.f));
		}
		else if (2 > pMov->GetJmpCnt() && (KEY_PRESSED(KEY::UP)))
		{
			++(pMov->GetJmpCnt());
			pMov->SetVelocity(Vec2(pMov->GetVelocity().x, pMov->GetVelocity().y - 1000.f));
		}


	}

	

}

void CPlayerOnAir::Enter()
{
	CAnimator* pAni = GetAnimator();
	pAni->Play(L"commonpinkbeanmove");
}

void CPlayerOnAir::Exit()
{
}
