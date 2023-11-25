#include "pch.h"
#include "CSecondBMDie.h"
#include "CUIMgr.h"

CSecondBMDie::CSecondBMDie()
{
	SetName(L"��������");
}

void CSecondBMDie::finaltick(float _DT)
{
	m_acctime += _DT;

	if (m_acctime > 4.f)
	{
		ChangeLevel(LEVEL_TYPE::PHASE_FIFTH);
		GetOwner()->Destroy();
	}

}

void CSecondBMDie::Enter()
{
	Super::Enter();

	CUIMgr::GetInst()->FloatNotice(L"����� ����� �������.", 3.8f);

	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"die");
}

void CSecondBMDie::Exit()
{
}

CSecondBMDie::~CSecondBMDie()
{
}
