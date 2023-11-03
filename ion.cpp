#include "pch.h"
#include "ion.h"

#include "CNormalMonIdle.h"
#include "CNormalMonTrace.h"


ion::ion()
{
	SetName(L"ion");

	SetScale(Vec2(200.f, 600.f));

	m_Collider = AddComponent<CCollider>(GetName()+ L"Collider");
	m_Info.HP = 5.f;
	m_Collider->SetScale(GetScale());
	m_Collider->SetOffsetPos(Vec2(-0.f, -300.f));


	m_Animator = AddComponent<CAnimator>(GetName() + L"Animator");
	m_Animator->CreateAnimation(L"first", L"ion", L"stand", Vec2(-0.f, -300.f), 1.f);
	m_Animator->CreateAnimation(L"first", L"ion", L"attack2", Vec2(-0.f, -300.f), 1.f);

	m_Animator->Play(L"firstionstand");

	// Movement 컴포넌트 추가
	m_Movement = AddComponent<CMovement>(GetName() + L"Movement");
	m_Movement->SetMass(1.f);
	m_Movement->SetInitSpeed(500.f);
	m_Movement->SetMaxSpeed(500.f);
	m_Movement->SetFrictionScale(2200.f);

	m_Movement->UseGravity(true);
	m_Movement->SetGravity(Vec2(0.f, 2500.f));
	m_Movement->SetGround(false);



	// 상태머신 컴포넌트 추가 및 설정
	m_AI = AddComponent<CStateMachine>(GetName() + L"AI");
	m_AI->AddState((UINT)ENORMAL_MON_STATE::IDLE, new CNormalMonIdle);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::TRACE, new CNormalMonTrace);
}

ion::ion(const ion& _Origin)
	: CMonster(_Origin)
{
	m_Collider = GetComponent<CCollider>();
	m_AI = GetComponent<CStateMachine>();
}

ion::~ion()
{
}


void ion::begin()
{

	Vec2 vPos = GetPos();
	m_AI->AddDataToBlackboard(L"Initial Position", vPos);
	m_AI->AddDataToBlackboard(L"Detect Range", 500.f);
	m_AI->AddDataToBlackboard(L"Attack Range", 50.f);
	m_AI->AddDataToBlackboard(L"Speed", 300.f);

	m_AI->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
}

void ion::tick(float _DT)
{
	Super::tick(_DT);
}

void ion::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	CSkill* pSkill = dynamic_cast<CSkill*>(_OtherObj);


	if ( (nullptr!= pSkill) && (pSkill->GetLayerIdx()==LAYER::PLAYER_PJ) )
	{
		m_Info.HP -= (pSkill->GetAtt()/5.f);

		if (m_Info.HP <= 0.f)
		{
			Destroy();
		}
		return;
	}
	
	CPlatform* pPlatform = dynamic_cast<CPlatform*>(_OtherObj);

	if ((nullptr != pPlatform) && (pPlatform->GetLayerIdx() == LAYER::PLATFORM))
	{
		m_Movement->SetGround(true);

		return;
	}
}

