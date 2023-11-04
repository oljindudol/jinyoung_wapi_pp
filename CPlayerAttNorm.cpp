#include "pch.h"
#include "CPlayerAttNorm.h"
#include "CKeyMgr.h"


CPlayerAttNorm::CPlayerAttNorm()
{
}

CPlayerAttNorm::~CPlayerAttNorm()
{
}


void CPlayerAttNorm::finaltick(float _DT)
{
	CMovement* pMov = GetMovement();
	ORIENTATION& ort = GetOwner()->GetOrtOrigin();

	m_acctime += _DT;

	if (0.6f < m_acctime)
	{
		pMov->IsGround() ?
			ChangeState((UINT)PLAYER_STATE::IDLE) :
			ChangeState((UINT)PLAYER_STATE::ON_AIR) ;
	}


}

void CPlayerAttNorm::Enter()
{
	CAnimator* pAni = GetAnimator();
	pAni->Play(L"commonpinkbeanstab");

	ORIENTATION& ort = GetOwner()->GetOrtOrigin();
	CSkillMgr::GetInst()->ActivateSkill(L"commonpinkbeanphantomblow", GetOwner()->GetPos(), ort);

	m_acctime = 0.f;
}

void CPlayerAttNorm::Exit()
{
}

