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
	if (m_acctime > (2.5f / GetAnimator()->GetCurAnimmulti()))
	{
		if (L"firstion" == GetOwner()->GetName())
			ChangeLevel(LEVEL_TYPE::PHASE_SECOND);
		GetOwner()->Destroy();

	}

}

#include "CMonsterMgr.h"
void CNormalMonDie::Enter()
{
	Super::Enter();
	auto MonName = GetOwner()->GetName();
	if (-1 != MonName.find(L"ion"))
	{
		CUIMgr::GetInst()->FloatNotice(L"검은마법사를 향한 길이 열린다.", 4.f);

		auto yaldavec = CMonsterMgr::GetInst()->FindMonster(L"firstyalda");
		CMonster* yalda = nullptr;
		if (nullptr != yaldavec)
			yalda = (*yaldavec)[0];

		yalda->GetAI()->ChangeState((UINT)ENORMAL_MON_STATE::DIE);
	}

	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"die");

	CCollider* pCol = GetCollider();
	pCol->SetScale(Vec2(0.f, 0.f));
	//pCol->SetOffsetPos(Vec2(0.f, 0.f));
}

void CNormalMonDie::Exit()
{
}
