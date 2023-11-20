#include "pch.h"
#include "CPlayerAttSp.h"
#include "CKeyMgr.h"

#include "CSkill.h"
#include "CSkillMgr.h"

CPlayerAttSp::CPlayerAttSp()
	:ptmpskill(nullptr)
	, m_animtime(0.f)
{
	m_stateduration = CSkillMgr::GetInst()->GetSkillDuration(L"commonbladestormuse") + 0.05f;
}

CPlayerAttSp::~CPlayerAttSp()
{
}

void CPlayerAttSp::finaltick(float _DT)
{

	m_acctime += _DT;
	m_animtime += _DT;

	if (KEY_RELEASED(KEY::F ))
	{
		ChangeState((UINT)PLAYER_STATE::IDLE);
		ptmpskill->Destroy();
	}

	if (KEY_PRESSED(KEY::LEFT))
	{
		GetOwner()->ort = ORT_LEFT;
		if (400.f > abs(GetMovement()->GetVelocity().x)) {
			GetMovement()->AddForce(Vec2(-1000.f, 0.f));
		}
	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		GetOwner()->ort = ORT_RIGHT;
		if (400.f > abs(GetMovement()->GetVelocity().x))
		{
			GetMovement()->AddForce(Vec2(1000.f, 0.f));
		}
	}

	if (0.3f < m_animtime)
	{
		GetAnimator()->Play(L"commonpinkbeanstab");
		m_animtime = 0.f;
	}

	if (m_stateduration < m_acctime)
	{
		ChangeState((UINT)PLAYER_STATE::IDLE);
	}
}

void CPlayerAttSp::Enter()
{
	ptmpskill = CSkillMgr::GetInst()->ActivateSkill(L"commonbladestormuse", GetOwner()->GetPos(), GetOwner()->ort);

	CAnimator* pAni = GetAnimator();
	pAni->Play(L"commonpinkbeanstab");


	m_acctime = 0.f;
}

void CPlayerAttSp::Exit()
{
}
