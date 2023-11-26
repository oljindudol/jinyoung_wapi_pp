#include "pch.h"
#include "CGEggDie.h"
#include "CLevelMgr.h"
#include "CPhaseFifth.h"

CGEggDie::CGEggDie()
	:m_ItemDroped(false)
{
}

void CGEggDie::finaltick(float _DT)
{
	m_acctime += _DT;

	if (m_stateduration < m_acctime)
	{
		CPhaseFifth* pf = dynamic_cast<CPhaseFifth*>(CLevelMgr::GetInst()->GetCurLevel());
		if (false == m_ItemDroped &&nullptr != pf)
		{
			pf->dropitem();
			m_ItemDroped = true;
		}
		GetOwner()->Destroy();
	}

}

void CGEggDie::Enter()
{
	Super::Enter();

	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"die");

	m_ItemDroped = false;

	CLevelMgr::GetInst()->GetPlayer()->CompleteMission();
}

void CGEggDie::Exit()
{
}

CGEggDie::~CGEggDie()
{
}
