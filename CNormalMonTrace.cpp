#include "pch.h"
#include "CNormalMonTrace.h"

CNormalMonTrace::CNormalMonTrace()
{
}

CNormalMonTrace::~CNormalMonTrace()
{
}

void CNormalMonTrace::finaltick(float _DT)
{

	// �÷��̾��� ��ġ�� �˾Ƴ���.
	Vec2 vPlayerPos = m_pTarget->GetPos();

	// ���� ������ ��ġ�� �˾Ƴ���.
	CMonster* pMonster = dynamic_cast<CMonster*>(GetOwnerSM()->GetOwner());
	if (nullptr == pMonster)
		return;
	Vec2 vMonsterPos = pMonster->GetPos();


	//left:-1
	int skillortsign = -1;

	if (0.0 == m_acctime)
	{

		// �÷��̾ Ž�������� ����� Idle ���·� ���ư���.
		// 1. �����忡�� ������ Ž�������� �����´�.
		float* pDetectRange = (float*)GetOwnerSM()->GetDataFromBlackboard(L"Detect Range");
		float DetectRange = *pDetectRange;

		// 2. �÷��̾�� ������ �Ÿ��� ���Ѵ�.
		float fDist = vPlayerPos.Distance(vMonsterPos);


		GetOwnerSM()->GetOwner()->ort =
			((vMonsterPos - vPlayerPos).x > 0.f) ?
			ORT_LEFT : ORT_RIGHT;

		// 3. �÷��̾�� ������ �Ÿ��� Ž������ �̻��̸� Idle ���·� �����Ѵ�.
		if (DetectRange < fDist)
		{
			GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
			return;
		}


		// �÷��̾ ���ݹ��� �̳��� ������ Attack ���·� �����Ѵ�.
		{


		}
		// �÷��̾ �����Ѵ�.
		// 1. ���Ͱ� �̵��� ������ �˾Ƴ���. (�÷��̾���ġ - ���� ��ġ)
		Vec2 vDir = vPlayerPos - vMonsterPos;
		vDir.Normalize();

		skillortsign = vDir.x > 0 ? 1 : -1;
	}


	m_acctime += _DT;

	if (1.2f > m_acctime)
	{
		return;
	}
	if (3.45f < m_acctime)
	{
		m_acctime = 0.f;


	}
	// 2. ����(����) �� �̵��ӵ��� �˾Ƴ���.
	float* pSpeed = (float*)GetOwnerSM()->GetDataFromBlackboard(L"Speed");
	float fSpeed = *pSpeed;

	// 3. �÷��̾ ���ؼ� �̵��Ѵ�.
	vMonsterPos += Vec2((float)skillortsign,0.f) * fSpeed * _DT;
	pMonster->SetPos(vMonsterPos);
}

void CNormalMonTrace::Enter()
{
	CAnimator* pAni= GetOwnerSM()->GetOwner()->GetComponent<CAnimator>();
	pAni->Play(L"firstionattack2");

	// ������ �ִ� �÷��̾ �˾Ƴ���.
	m_pTarget = dynamic_cast<CPlayer*>(CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));

	// Animator �� Move Animation ���
}

void CNormalMonTrace::Exit()
{
}


