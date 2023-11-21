#include "pch.h"
#include "CNormalMonDie.h"
#include "CMonsterMgr.h"
#include "CUIMgr.h"

CNormalMonDie::CNormalMonDie()
{
}

CNormalMonDie::~CNormalMonDie()
{
}

void CNormalMonDie::finaltick(float _DT)
{
	m_acctime += _DT;
	if (m_acctime > (2.5f/ GetAnimator()->GetCurAnimmulti()) )
	{
		if (L"firstion" == GetOwner()->GetName())
			ChangeLevel(LEVEL_TYPE::PHASE_SECOND);
		GetOwner()->Destroy();

	}

}

void CNormalMonDie::Enter()
{

	Super::Enter();
	CUIMgr::GetInst()->FloatNotice(L"���������縦 ���� ���� ������.", 4.f);

	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"die");

	CCollider* pCol = GetCollider();
	pCol->SetScale(Vec2(0.f, 0.f));
	//pCol->SetOffsetPos(Vec2(0.f, 0.f));
}

void CNormalMonDie::Exit()
{
}
