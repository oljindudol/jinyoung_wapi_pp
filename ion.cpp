#include "pch.h"
#include "ion.h"

#include "CNormalMonIdle.h"
#include "CNormalMonTrace.h"
#include "CNormalMonRegen.h"
#include "CNormalMonDie.h"
#include "CNormalMonAtt1.h"
#include "CNormalMonAtt3.h"

#include "CMonsterMgr.h"

#include "CTimeManager.h"
#include "CLogMgr.h"


ion::ion()
{

	ort = ORT_RIGHT;
	m_s1 = L"first";
	m_s2 = L"ion";

	m_monstername = m_s1 + m_s2 ;

	//몇번째 몬스터 인지
	m_monsternum = CMonsterMgr::GetInst()->FindNextMonsterNumber(m_monstername);

	SetName(m_monstername);// + L"_" + std::to_wstring(m_monsternum));


	SetScale(Vec2(200.f, 600.f));

	// Collider 컴포넌트 추가
	m_Collider = AddComponent<CCollider>(GetName()+ L"Collider");
	m_Info.MaxHp = 5.f;
	m_Info.HP = m_Info.MaxHp;

	m_Collider->SetScale(GetScale());
	m_Collider->SetOffsetPos(Vec2(-0.f, -300.f));

	// Animator 컴포넌트 추가
	m_Animator = AddComponent<CAnimator>(GetName() + L"Animator");
	m_Animator->CreateAnimation(L"first", L"ion", L"idle", Vec2(-0.f, -260.f), 1.f);
	m_Animator->CreateAnimation(L"first", L"ion", L"attack2", Vec2(-0.f, -300.f), 1.f);
	m_Animator->CreateAnimation(L"first", L"ion", L"regen", Vec2(-0.f, -300.f), 1.f,-1);
	m_Animator->CreateAnimation(L"first", L"ion", L"die", Vec2(-0.f, -260.f), .5f, -1);
	m_Animator->CreateAnimation(L"first", L"ion", L"attack1", Vec2(-0.f, -260.f), 1, -1);
	m_Animator->CreateAnimation(L"first", L"ion", L"attack3", Vec2(-0.f, -540.f), 1, -1);

	m_Animator->Play(GetName()+L"idle");

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
	m_AI->AddState((UINT)ENORMAL_MON_STATE::REGEN, new CNormalMonRegen);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::ATTACK2, new CNormalMonTrace);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::ATTACK1, new CNormalMonAtt1);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::ATTACK3, new CNormalMonAtt3);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::DIE, new CNormalMonDie);

	m_AI->AddDataToBlackboard(L"Att1 Range", 400.f);
	m_AI->AddDataToBlackboard(L"Detect Range", firstmon_attack2_dist);
	m_AI->AddDataToBlackboard(L"Att3 Range", 1500.f);
	m_AI->AddDataToBlackboard(L"Speed", 300.f);
	

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
	//Monster::Spawn에 이관.
	//m_AI->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
}




void ion::tick(float _DT)
{
	Super::tick(_DT);
}

void ion::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	Super::BeginOverlap(_OwnCol, _OtherObj, _OtherCol);


	CSkill* pSkill = dynamic_cast<CSkill*>(_OtherObj);

	if (LAYER::PLAYER_PJ == _OtherObj->GetLayerIdx() &&
		!( (UINT)ENORMAL_MON_STATE::DIE == m_AI->GetCurStateNum() ||
			(UINT)ENORMAL_MON_STATE::REGEN == m_AI->GetCurStateNum()))
	{
		m_Info.HP -= (pSkill->GetAtt()/5.f);

		if (m_Info.HP <= 0.f)
		{
			m_AI->ChangeState((UINT)ENORMAL_MON_STATE::DIE);
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

void ion::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	Super::Overlap(_OwnCol, _OtherObj, _OtherCol);

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_OtherObj);

	if ((UINT)ENORMAL_MON_STATE::ATTACK2 == m_AI->GetCurStateNum() && pPlayer)
	{
		float acctime= m_AI->GetCurstateAcctime();

		if (m_collisiontimetoplayer < 0.1f && 
			acctime > 1.3f &&
			acctime < 2.82f
			)
		{
			float force = 5000.f;
			pPlayer->getMovement()->AddForce(Vec2((ort == ORT_LEFT) ? -1.f : 1.f, -1.f) * force);
		}
	}

	if ((UINT)ENORMAL_MON_STATE::ATTACK1 == m_AI->GetCurStateNum() && pPlayer)
	{
		float acctime = m_AI->GetCurstateAcctime();

		if (m_collisiontimetoplayer < 0.1f &&
			acctime > 0.6f &&
			acctime < 1.4f
			)
		{
			float force = 5000.f;
			pPlayer->getMovement()->AddForce(Vec2((ort == ORT_LEFT) ? -1.f : 1.f, -1.f) * force);
		}
	}

	if ((UINT)ENORMAL_MON_STATE::ATTACK3 == m_AI->GetCurStateNum() && pPlayer)
	{
		float acctime = m_AI->GetCurstateAcctime();

		if (m_collisiontimetoplayer < 0.1f &&
			acctime > 2.95f &&
			acctime < 3.8f
			)
		{
			float force = 5000.f;
			pPlayer->getMovement()->AddForce(Vec2((ort == ORT_LEFT) ? -1.f : 1.f, -1.f) * force);
		}
	}
}



void ion::EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{

	Super::EndOverlap(_OwnCol, _OtherObj, _OtherCol);
}