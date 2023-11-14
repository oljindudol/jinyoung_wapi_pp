#include "pch.h"
#include "CRuleMon12Attack.h"
#include "CMonsterMgr.h"

CRuleMon12Attack::CRuleMon12Attack()
	:attackcnt(0)
{

}

CRuleMon12Attack::~CRuleMon12Attack()
{
}

void CRuleMon12Attack::finaltick(float _DT)
{
	m_acctime += _DT;

	if (m_acctime > 1.2f)
	{
		m_acctime = 0.f;
		float xpos = attackcnt < 21 ?
			attackcnt * 226.f 
			: (4500.f - (attackcnt- 20) * 226.f);
		CMonsterMgr::GetInst()->SpwanMonster(L"firstdarkfalling",
			Vec2(xpos, 50.f));

		++attackcnt;

		if (40 == attackcnt)
			GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
	}
}

void CRuleMon12Attack::Enter()
{
	m_acctime = 0.f;
	attackcnt = 0;


}

void CRuleMon12Attack::Exit()
{
}
