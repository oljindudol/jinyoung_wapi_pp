#include "pch.h"
#include "CNormalMonTrace.h"

CNormalMonTrace::CNormalMonTrace()
	:m_bigcollider(false)
{
}

CNormalMonTrace::~CNormalMonTrace()
{
}

void CNormalMonTrace::finaltick(float _DT)
{

	// �÷��̾��� ��ġ�� �˾Ƴ���.
	Vec2 vPlayerPos = m_pPlayer->GetPos();

	// ���� ������ ��ġ�� �˾Ƴ���.
	CMonster* pMonster = dynamic_cast<CMonster*>(GetOwnerSM()->GetOwner());
	if (nullptr == pMonster)
		return;
	Vec2 vMonsterPos = pMonster->GetPos();


	

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

		m_skillortsign = vDir.x > 0 ? 1 : -1;
	}


	m_acctime += _DT;

	if (1.3f > m_acctime)
	{
		return;
	}

	if (3.45f < m_acctime)
	{
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
		return;
	}
	if (2.82f < m_acctime)
	{
		if (m_bigcollider) 
		{
			m_bigcollider = false;
			GetOwnerSM()->GetColliderComponent()->SetOffsetPos(Vec2(-0.f, -300.f));
			GetOwnerSM()->GetColliderComponent()->SetScale(Vec2(200.f, 600.f));
		}
		return;
	}

	if (!m_bigcollider && 0.f != m_acctime)
	{
		GetOwner()->SetCollisionTime(0.f);
		m_bigcollider = true;
		GetOwnerSM()->GetColliderComponent()->SetOffsetPos(Vec2(-150.f, -300.f));
		GetOwnerSM()->GetColliderComponent()->SetScale(Vec2(500.f, 600.f));

	}

	// 2. ����(����) �� �̵��ӵ��� �˾Ƴ���.
	float* pSpeed = (float*)GetOwnerSM()->GetDataFromBlackboard(L"Speed");
	float fSpeed = *pSpeed;

	// 3. �÷��̾ ���ؼ� �̵��Ѵ�.
	vMonsterPos += Vec2((float)m_skillortsign,0.f) * fSpeed * _DT;
	pMonster->SetPos(vMonsterPos);
}

void CNormalMonTrace::Enter()
{
	GetOwner()->SetCollisionTime(0.f);
	m_bigcollider = false;
	GetOwnerSM()->GetColliderComponent()->SetOffsetPos(Vec2(-0.f, -300.f));
	GetOwnerSM()->GetColliderComponent()->SetScale(Vec2(200.f, 600.f));
	
	CAnimator* pAni= GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"attack2");

	// ������ �ִ� �÷��̾ �˾Ƴ���.
	m_pPlayer = dynamic_cast<CPlayer*>(CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));

	// Animator �� Move Animation ���
}

void CNormalMonTrace::Exit()
{
	//m_bigcollider = false;
	//GetOwnerSM()->GetColliderComponent()->SetOffsetPos(Vec2(-0.f, -300.f));
	//GetOwnerSM()->GetColliderComponent()->SetScale(Vec2(200.f, 600.f));
}


