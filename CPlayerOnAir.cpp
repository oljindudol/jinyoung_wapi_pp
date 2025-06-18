#include "pch.h"
#include "CPlayerOnAir.h"
#include "CKeyMgr.h"
#include "CAssetMgr.h"

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

	if (nullptr == m_pPlayer)
		m_pPlayer = CLevelMgr::GetInst()->GetPlayer();

	bool CanChageState = true;
	if (nullptr != m_pPlayer)
		CanChageState = m_pPlayer->IsDebuffActive(DEBUFF::INABILITY);
	if (false == CanChageState)
	{
		if (KEY_PRESSED(X))
		{
			GetOwnerSM()->ChangeState((UINT)PLAYER_STATE::ATT_NM);
		}

		if (KEY_TAP(KEY::LALT)) {
			if (2 > pMov->GetJmpCnt() && !(KEY_PRESSED(KEY::UP)))
			{
				CSkillMgr::GetInst()->ActivateSkill(L"commonpinkbeandoublejump", GetOwner()->GetPos(), ort);
				CAssetMgr::GetInst()->LoadSound(L"doublejump", L"sound\\´þÁ¡3.wav")->Play();

				++(pMov->GetJmpCnt());
				float xvel = 700.f;
				if (ort == ORT_LEFT) xvel *= (-1);
				pMov->SetVelocity(Vec2(xvel, pMov->GetVelocity().y - 300.f));
			}
			else if (2 > pMov->GetJmpCnt() && (KEY_PRESSED(KEY::UP)))
			{
				CSkillMgr::GetInst()->ActivateSkill(L"commonpinkbeanupperjump", GetOwner()->GetPos(), ort);
				CAssetMgr::GetInst()->LoadSound(L"doublejump", L"sound\\´þÁ¡3.wav")->Play();
				++(pMov->GetJmpCnt());
				pMov->SetVelocity(Vec2(pMov->GetVelocity().x, pMov->GetVelocity().y - 1000.f));
			}
		}
	}



}

void CPlayerOnAir::Enter()
{
	CAnimator* pAni = GetAnimator();
	pAni->Play(L"commonpinkbeanonair");
	CAssetMgr::GetInst()->LoadSound(L"JUMP", L"sound\\Jump.wav")->Play();
}

void CPlayerOnAir::Exit()
{
}
