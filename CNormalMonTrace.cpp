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

	// 플레이어의 위치를 알아낸다.
	Vec2 vPlayerPos = m_pPlayer->GetPos();

	// 몬스터 본인의 위치를 알아낸다.
	CMonster* pMonster = dynamic_cast<CMonster*>(GetOwnerSM()->GetOwner());
	if (nullptr == pMonster)
		return;
	Vec2 vMonsterPos = pMonster->GetPos();


	

	if (0.0 == m_acctime)
	{

		// 플레이어가 탐지범위를 벗어나면 Idle 상태로 돌아간다.
		// 1. 블랙보드에서 몬스터의 탐지범위를 꺼내온다.
		float* pDetectRange = (float*)GetOwnerSM()->GetDataFromBlackboard(L"Detect Range");
		float DetectRange = *pDetectRange;

		// 2. 플레이어와 몬스터의 거리를 구한다.
		float fDist = vPlayerPos.Distance(vMonsterPos);


		GetOwnerSM()->GetOwner()->ort =
			((vMonsterPos - vPlayerPos).x > 0.f) ?
			ORT_LEFT : ORT_RIGHT;

		// 3. 플레이어와 몬스터의 거리가 탐지범위 이상이면 Idle 상태로 변경한다.
		if (DetectRange < fDist)
		{
			GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
			return;
		}


		// 플레이어가 공격범위 이내로 들어오면 Attack 상태로 변경한다.
		{


		}
		// 플레이어를 추적한다.
		// 1. 몬스터가 이동할 방향을 알아낸다. (플레이어위치 - 몬스터 위치)
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

	// 2. 본인(몬스터) 의 이동속도를 알아낸다.
	float* pSpeed = (float*)GetOwnerSM()->GetDataFromBlackboard(L"Speed");
	float fSpeed = *pSpeed;

	// 3. 플레이어를 향해서 이동한다.
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

	// 레벨에 있는 플레이어를 알아낸다.
	m_pPlayer = dynamic_cast<CPlayer*>(CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));

	// Animator 에 Move Animation 재생
}

void CNormalMonTrace::Exit()
{
	//m_bigcollider = false;
	//GetOwnerSM()->GetColliderComponent()->SetOffsetPos(Vec2(-0.f, -300.f));
	//GetOwnerSM()->GetColliderComponent()->SetScale(Vec2(200.f, 600.f));
}


