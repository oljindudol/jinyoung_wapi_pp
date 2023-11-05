#include "pch.h"
#include "ion.h"

#include "CNormalMonIdle.h"
#include "CNormalMonTrace.h"

#include "CMonsterMgr.h"


ion::ion()
{

	m_s1 = L"first";
	m_s2 = L"ion";

	m_monstername = m_s1 + m_s2 ;

	//몇번째 몬스터 인지
	auto iter = CMonsterMgr::GetInst()->m_MonsterMap.find(m_monstername);
	if (CMonsterMgr::GetInst()->m_MonsterMap.end() == iter)
	{
		m_monsternum = 0;
	}
	else
	{
		m_monsternum = iter->second.size();
	}

	SetName(m_monstername + L"_" + std::to_wstring(m_monsternum));


	SetScale(Vec2(200.f, 600.f));

	m_Collider = AddComponent<CCollider>(GetName()+ L"Collider");
	m_Info.MaxHp = 5.f;
	m_Info.HP = m_Info.MaxHp;

	m_Collider->SetScale(GetScale());
	m_Collider->SetOffsetPos(Vec2(-0.f, -300.f));


	m_Animator = AddComponent<CAnimator>(GetName() + L"Animator");
	m_Animator->CreateAnimation(L"first", L"ion", L"idle", Vec2(-0.f, -250.f), 1.f);
	m_Animator->CreateAnimation(L"first", L"ion", L"attack2", Vec2(-0.f, -300.f), 1.f);

	m_Animator->Play(L"firstionsidle");

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

	m_AI->AddDataToBlackboard(L"Detect Range", 500.f);
	m_AI->AddDataToBlackboard(L"Attack Range", 50.f);
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


