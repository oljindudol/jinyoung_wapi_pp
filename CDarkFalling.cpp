#include "pch.h"
#include "CDarkFalling.h"

#include "CMonsterMgr.h"
#include "CDarkFallingRegen.h"
#include "CDarkFallingIdle.h"
#include "CDarkFallingDie.h"
#include "CLevelMgr.h"


CDarkFalling::CDarkFalling()
{
	ort = ORT_LEFT;
	m_s1 = L"first";
	m_s2 = L"darkfalling";

	m_monstername = m_s1 + m_s2;

	//몇번째 몬스터 인지
	m_monsternum = CMonsterMgr::GetInst()->FindNextMonsterNumber(m_monstername);

	SetName(m_monstername +L"_" + std::to_wstring(m_monsternum));


	SetScale(Vec2(100.f, 100.f));

	m_MonsterLayer = (UINT)LAYER::FALL_OBJ;

	// Movement 컴포넌트 추가
	m_Movement = AddComponent<CMovement>(GetName() + L"Movement");
	m_Movement->SetMass(1.f);
	m_Movement->SetInitSpeed(500.f);
	m_Movement->SetMaxSpeed(500.f);
	m_Movement->SetFrictionScale(2200.f);

	m_Movement->UseGravity(false);
	m_Movement->SetGravity(Vec2(0.f, 2500.f));
	m_Movement->SetGround(false);


	// Animator 컴포넌트 추가
	m_Animator = AddComponent<CAnimator>(GetName() + L"Animator");
	m_Animator->CreateAnimation(m_s1, m_s2, L"regen", Vec2(0.f, 0.f), 1.f, -1);
	m_Animator->CreateAnimation(m_s1, m_s2, L"idle", Vec2(0.f, 0.f), 1.f , 0);
	m_Animator->CreateAnimation(m_s1, m_s2, L"die", Vec2(0.f, 0.f), 1.f, -1);


	// Collider 컴포넌트 추가
	m_Collider = AddComponent<CCollider>(GetName() + L"Collider");
	m_Collider->SetScale(GetScale());
	m_Collider->SetOffsetPos(Vec2(-10.f, 0.f));


	// 상태머신 컴포넌트 추가 및 설정
	m_AI = AddComponent<CStateMachine>(GetName() + L"AI");
	m_AI->AddState((UINT)ENORMAL_MON_STATE::REGEN, new CDarkFallingRegen);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::IDLE, new CDarkFallingIdle);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::DIE, new CDarkFallingDie);


}

CDarkFalling::CDarkFalling(const CDarkFalling& _Origin)
{
}

CDarkFalling::~CDarkFalling()
{
}


void CDarkFalling::begin()
{
	m_Collider->InitColCnt();
}

void CDarkFalling::tick(float _DT)
{
}

void CDarkFalling::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (LAYER::PLATFORM == (UINT)_OtherObj->GetLayerIdx())
		m_AI->ChangeState((UINT)ENORMAL_MON_STATE::DIE);

	if (LAYER::PLAYER == (UINT)_OtherObj->GetLayerIdx()
		&&  (UINT)ENORMAL_MON_STATE::DIE != m_AI->GetCurStateNum())
	{
		CLevelMgr::GetInst()->GetPlayer()->GetDamaged(0.1f, DEBUFF::CREATION);
		m_AI->ChangeState((UINT)ENORMAL_MON_STATE::DIE);
	}
}

void CDarkFalling::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
}

void CDarkFalling::EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
}


