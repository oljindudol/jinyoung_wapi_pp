#include "pch.h"
#include "CNormalMonAtt3.h"

CNormalMonAtt3::CNormalMonAtt3()
	:chased(false)
	, stomped(false)
	, up(false)
{
}

CNormalMonAtt3::~CNormalMonAtt3()
{
}

void CNormalMonAtt3::finaltick(float _DT)
{
	if (4.32f < m_acctime)
	{
		GetOwnerSM()->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
		return;
	}

	m_acctime += _DT;

	if (0.54f > m_acctime)
	{
		return;
	}

	if (up == false && 0.f != m_acctime)
	{
		up = true;
		GetOwner()->SetPos(Vec2(GetOwner()->GetPos().x, 0.f));
	}

	if (1.3f > m_acctime)
	{
		return;
	}

	if (chased == false && 0.f != m_acctime)
	{
		chased = true;
		Vec2 vPlayerPos = m_pPlayer->GetPos();
		GetOwner()->SetPos(Vec2 (vPlayerPos.x, 0.f ));
	}

	if (1.3f > m_acctime)
	{
		return;
	}

	if (stomped == false && 2.95 < m_acctime)
	{
		Vec2 vPlayerPos = m_pPlayer->GetPos();
		GetOwner()->GetMovement()->SetGround(false);
		GetOwner()->SetCollisionTime(0.f);
		GetOwner()->SetPos(Vec2(vPlayerPos.x, vPlayerPos.y));
		stomped = true;
	}


}

void CNormalMonAtt3::Enter()
{

	Super::Enter();

	chased = false;
	stomped = false;
	up = false;

	GetOwnerSM()->GetColliderComponent()->SetOffsetPos(Vec2(-0.f, -300.f));
	GetOwnerSM()->GetColliderComponent()->SetScale(Vec2(200.f, 600.f));

	CAnimator* pAni = GetAnimator();
	pAni->Play(GetOwner()->GetName() + L"attack3");

	// 레벨에 있는 플레이어를 알아낸다.
	m_pPlayer = dynamic_cast<CPlayer*>(CLevelMgr::GetInst()->GetCurLevel()->FindObjectByName(L"Player"));
}

void CNormalMonAtt3::Exit()
{
}
