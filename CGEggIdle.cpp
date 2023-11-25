#include "pch.h"
#include "CGEggIdle.h"

CGEggIdle::CGEggIdle()
{

}

void CGEggIdle::finaltick(float _DT)
{

	m_acctime += _DT;
}

void CGEggIdle::Enter()
{
	Super::Enter();

	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"idle");
}

void CGEggIdle::Exit()
{
}

CGEggIdle::~CGEggIdle()
{
}
