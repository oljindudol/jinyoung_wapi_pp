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


	if (pMov->IsGround())
	{
		GetOwnerSM()->ChangeState((UINT)PLAYER_STATE::ON_AIR);
		return;
	}

	if (KEY_PRESSED(KEY::LEFT))
	{
		ort = ORT_LEFT;
		if (m_Movement->IsGround()) {
			if (L"commonpinkbeanmove" != m_Animator->GetCurAnimName())
			{
				m_Animator->Play(L"commonpinkbeanmove");
			}
		}
		if (400.f > abs(m_Movement->GetVelocity().x))
		{
			m_Movement->AddForce(Vec2(-1000.f, 0.f));
		}
	}

	if (KEY_RELEASED(KEY::LEFT))
	{
		if (m_Movement->IsGround()) {
			m_Animator->Play(L"commonpinkbeanidle");
		}
	}




	if (KEY_PRESSED(KEY::RIGHT))
	{
		ort = ORT_RIGHT;
		if (m_Movement->IsGround()) {
			if (L"commonpinkbeanmove" != m_Animator->GetCurAnimName())
			{
				m_Animator->Play(L"commonpinkbeanmove");
			}
		}
		if (400.f > abs(m_Movement->GetVelocity().x))
		{
			m_Movement->AddForce(Vec2(1000.f, 0.f));
		}
	}



	if (KEY_RELEASED(KEY::RIGHT))
	{
		if (m_Movement->IsGround()) {
			m_Animator->Play(L"commonpinkbeanidle");
		}
	}


	if (KEY_PRESSED(KEY::UP))
	{

	}
	if (KEY_RELEASED(KEY::UP))
	{
	}

	if (KEY_PRESSED(KEY::DOWN))
	{
		if (m_Movement->IsGround()) {
			m_Animator->Play(L"commonpinkbeandown");
		}
	}
	if (KEY_RELEASED(KEY::DOWN))
	{
		if (m_Movement->IsGround()) {
			m_Animator->Play(L"commonpinkbeanidle");
		}
	}

	if (KEY_TAP(C))
	{
		CSkillMgr::GetInst()->ActivateSkill(L"commonpinkbeanphantomblow", GetPos(), ort);
		m_Animator->Play(L"commonpinkbeanstab");
	}

	if (KEY_TAP(LALT))
	{

		if (m_Movement->IsGround())
		{
			m_Movement->SetVelocity(Vec2(m_Movement->GetVelocity().x, -750.f));
		}
		else if (2 > m_Movement->GetJmpCnt() && !(KEY_PRESSED(KEY::UP)))
		{

			CSkillMgr::GetInst()->ActivateSkill(L"commonpinkbeandoublejump", GetPos(), ort);

			++(m_Movement->GetJmpCnt());
			float xvel = 700.f;
			if (ort == ORT_LEFT) xvel *= (-1);
			m_Movement->SetVelocity(Vec2(xvel, m_Movement->GetVelocity().y - 300.f));
		}
		else if (2 > m_Movement->GetJmpCnt() && (KEY_PRESSED(KEY::UP)))
		{
			++(m_Movement->GetJmpCnt());
			m_Movement->SetVelocity(Vec2(m_Movement->GetVelocity().x, m_Movement->GetVelocity().y - 1000.f));
		}
		else
		{

		}

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




