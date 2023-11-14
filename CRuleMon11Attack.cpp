#include "pch.h"
#include "CRuleMon11Attack.h"

CRuleMon11Attack::CRuleMon11Attack()
	:attackcnt(0)
	,attackmax(0)
{
}

CRuleMon11Attack::~CRuleMon11Attack()
{
}

void CRuleMon11Attack::finaltick(float _DT)
{
	m_acctime += _DT;

	if (m_acctime > .5f)
	{
		// 플레이어의 위치를 알아낸다.
		Vec2 vPlayerPos = m_pPlayer->GetPos();
		++attackcnt;
		m_acctime = 0.f;
		CSkillMgr::GetInst()->ActivateSkill(L"firstrulemonchainattack", vPlayerPos, ORT_LEFT);

		if(attackmax == attackcnt)
			GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
	}
}

void CRuleMon11Attack::Enter()
{
	m_acctime = 0.f;
	attackcnt = 0;
	attackmax = (rand() > 16383) ? 6 : 4;

	
	// 레벨에 있는 플레이어를 알아낸다.
	m_pPlayer = dynamic_cast<CPlayer*>(CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));

}

void CRuleMon11Attack::Exit()
{

}
