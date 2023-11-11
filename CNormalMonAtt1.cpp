#include "pch.h"
#include "CNormalMonAtt1.h"

CNormalMonAtt1::CNormalMonAtt1()
	:m_bigcollider(false)
{
}

CNormalMonAtt1::~CNormalMonAtt1()
{
}

void CNormalMonAtt1::finaltick(float _DT)
{
	if (1.5f < m_acctime)
	{
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
		return;
	}

	if (0.0 == m_acctime)
	{
		// 플레이어의 위치를 알아낸다.
		Vec2 vPlayerPos = m_pPlayer->GetPos();

		// 몬스터 본인의 위치를 알아낸다.
		CMonster* pMonster = dynamic_cast<CMonster*>(GetOwnerSM()->GetOwner());
		if (nullptr == pMonster)
			return;
		Vec2 vMonsterPos = pMonster->GetPos();


		Vec2 vDir = vPlayerPos - vMonsterPos;
		vDir.Normalize();

		m_skillortsign = vDir.x > 0 ? 1 : -1;

		m_acctime += _DT;

		GetOwner()->ort =
			((vMonsterPos - vPlayerPos).x > 0.f) ?
			ORT_LEFT : ORT_RIGHT;

	}

	m_acctime += _DT;
	
	if (0.6f > m_acctime)
	{
		return;
	}

	if (1.4f < m_acctime)
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


}

void CNormalMonAtt1::Enter()
{
	m_acctime = 0;
	GetOwner()->SetCollisionTime(0.f);
	m_bigcollider = false;
	GetOwnerSM()->GetColliderComponent()->SetOffsetPos(Vec2(-0.f, -300.f));
	GetOwnerSM()->GetColliderComponent()->SetScale(Vec2(200.f, 600.f));

	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName()+ L"attack1");

	// 레벨에 있는 플레이어를 알아낸다.
	m_pPlayer = dynamic_cast<CPlayer*>(CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));

}

void CNormalMonAtt1::Exit()
{
}
