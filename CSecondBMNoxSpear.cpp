#include "pch.h"
#include "CSecondBMNoxSpear.h"
#include <algorithm>
#include <random>

CSecondBMNoxSpear::CSecondBMNoxSpear()
{
	SetName(L"³ì½ºÇÇ¾î");

	for (int i = 0; i < 7; ++i)
	{
		m_spearpos.push_back(Vec2(250, 720) + Vec2(250 * i, 0));
	}

}

void CSecondBMNoxSpear::finaltick(float _DT)
{
	m_acctime += _DT;

	if (false == m_stateskillused
		&& 1.80f < m_acctime)
	{
		m_stateskillused = true;
		CSkillMgr::GetInst()->ActivateSkillWithDelay(L"secondnoxspearuse",0.5f , m_spearpos ,  ORT_LEFT);
	}

	if (m_stateduration < m_acctime)
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
}

void CSecondBMNoxSpear::Enter()
{
	Super::Enter();

	std::random_device rd;
	std::mt19937 g(rd());
	shuffle(m_spearpos.begin(), m_spearpos.end(), g);

	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"noxspear");
}

void CSecondBMNoxSpear::Exit()
{
}

CSecondBMNoxSpear::~CSecondBMNoxSpear()
{
}
