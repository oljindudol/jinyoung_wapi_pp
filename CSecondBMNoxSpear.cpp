#include "pch.h"
#include "CSecondBMNoxSpear.h"

CSecondBMNoxSpear::CSecondBMNoxSpear()
{
}

void CSecondBMNoxSpear::finaltick(float _DT)
{
	m_acctime += _DT;
}

void CSecondBMNoxSpear::Enter()
{
	Super::Enter();

	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"noxspear");
}

void CSecondBMNoxSpear::Exit()
{
}

CSecondBMNoxSpear::~CSecondBMNoxSpear()
{
}
