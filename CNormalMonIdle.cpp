#include "pch.h"
#include "CNormalMonIdle.h"



CNormalMonIdle::CNormalMonIdle()
{
}

CNormalMonIdle::~CNormalMonIdle()
{
}

void CNormalMonIdle::finaltick(float _DT)
{
	m_acctime += _DT;

	if (m_acctime < 1.5f)
		return;


	if (GetOwnerSM()->GetForcedIdle())
		return;

	if (nullptr == m_pPlayer)
		return;

	// �÷��̾ Ž������ ���� �ִ��� Ȯ��
	// 1. �����忡 ����Ǿ��ִ� Ž�������� �����´�/
	float* pAtt1Range = (float*)GetOwnerSM()->GetDataFromBlackboard(L"Att1 Range");
	float* pDetectRange = (float*)GetOwnerSM()->GetDataFromBlackboard(L"Detect Range");
	float* pAtt3Range = (float*)GetOwnerSM()->GetDataFromBlackboard(L"Att3 Range");

	float Att1Range = *pAtt1Range;
	float DetectRange = *pDetectRange;
	float Att3Range = *pAtt3Range;



	// 2. �÷��̾�� ���Ͱ��� �Ÿ��� üũ
	Vec2 vPlayerPos = m_pPlayer->GetPos();
	CMonster* pMonster = dynamic_cast<CMonster*>(GetOwnerSM()->GetOwner());
	if (nullptr == pMonster)
		return;

	Vec2 vMonsterPos = pMonster->GetPos();

	float fDist = vPlayerPos.Distance(vMonsterPos);

	if (fDist < Att1Range)
	{
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::ATTACK1);
		return;
	}

	if (fDist < DetectRange)
	{
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::ATTACK2);
		return;
	}

	if (fDist < Att3Range)
	{
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::ATTACK3);
		return;
	}

	
}

void CNormalMonIdle::Enter()
{
	Super::Enter();

	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"idle");

	CCollider* pCol = GetCollider();
	pCol->SetScale(GetOwner()->GetScale());
	pCol->SetOffsetPos(Vec2(0.f,-300.f));

	// ������ �ִ� �÷��̾ �˾Ƴ���.
	m_pPlayer = dynamic_cast<CPlayer*>(CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));
}

void CNormalMonIdle::Exit()
{
}


