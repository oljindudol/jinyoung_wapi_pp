#include "pch.h"
#include "CBlackMage3.h"

#include "CThirdBMIdle.h"
#include "CThirdBMDie.h"
#include "CThirdBMLaser.h"
#include "CThirdBMMorningStarFall.h"
#include "CThirdBMPush.h"
#include "CThirdBMPull.h"
#include "CThirdBMPowerUp.h"
#include "CThirdBMPowerDown.h"

#include "CMonsterMgr.h"
#include "CTimeManager.h"
#include "CLogMgr.h"
#include "CKeyMgr.h"
#include "CUIMgr.h"

#include "CPal.h"

CBlackMage3::CBlackMage3()
	:m_cooltime{
		//0 : 권능
		50.f
		//1 : 밀기
		,3.f
	//2 : 끌기
	,20.f
	//3: 메테오
	,25.f
	//4:레이저 
	,15.f
	}
	, m_left_cool{ 0.f,0.f,0.f,0.f,0.f }
	, m_state_nick{ L"권능", L"밀기", L"끌기", L"메테오", L"레이저" }
	, m_state_numarr{
		(UINT)ENORMAL_MON_STATE::POWER1
		,(UINT)ENORMAL_MON_STATE::ATTACK1
		,(UINT)ENORMAL_MON_STATE::ATTACK2
		,(UINT)ENORMAL_MON_STATE::ATTACK3
		,(UINT)ENORMAL_MON_STATE::ATTACK4
	}
{
	ort = ORT_LEFT;
	m_s1 = L"third";
	m_s2 = L"blackmage";

	//몇번째 몬스터 인지
	m_monsternum = CMonsterMgr::GetInst()->FindNextMonsterNumber(m_monstername);

	m_monstername = m_s1 + m_s2;
	SetName(m_monstername);// + L"_" + std::to_wstring(m_monsternum));

	SetScale(Vec2(440.f, 440.f));

	// Collider 컴포넌트 추가
	m_Collider = AddComponent<CCollider>(GetName() + L"Collider");

	m_Collider->SetScale(GetScale());
	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));

	// Animator 컴포넌트 추가
	m_Animator = AddComponent<CAnimator>(GetName() + L"Animator");
	m_Animator->CreateAnimation(L"third", L"blackmage", L"idle", Vec2(0.f, 0.f), 1.f);
	m_Animator->CreateAnimation(L"third", L"blackmage", L"die", Vec2(-7.f, -24.f), 1.f);

	m_Animator->CreateAnimation(L"third", L"blackmage", L"laser", Vec2(-1.f, -24.f), 1.f);
	m_Animator->CreateAnimation(L"third", L"blackmage", L"move", Vec2(0.f, 0.f), 1.f);
	m_Animator->CreateAnimation(L"third", L"blackmage", L"powerup", Vec2(4.f, -75.f), 1.f);
	m_Animator->CreateAnimation(L"third", L"blackmage", L"powerdown", Vec2(4.f, -26.f), 1.f);
	m_Animator->CreateAnimation(L"third", L"blackmage", L"push", Vec2(-26.f, -24.f), 1.f);
	m_Animator->CreateAnimation(L"third", L"blackmage", L"pull", Vec2(3.f, -24.f), 1.f);

	m_Animator->Play(GetName() + L"idle");

	// 상태머신 컴포넌트 추가 및 설정
	m_AI = AddComponent<CStateMachine>(GetName() + L"AI");
	m_AI->AddState((UINT)ENORMAL_MON_STATE::IDLE, new CThirdBMIdle)->Setduration(5.f);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::DIE, new CThirdBMDie)->Setduration(4.f);

	m_AI->AddState((UINT)ENORMAL_MON_STATE::ATTACK1, new CThirdBMPush)->Setduration(2.16f);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::ATTACK2, new CThirdBMPull)->Setduration(2.16f);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::ATTACK3, new CThirdBMMorningStarFall)->Setduration(2.16f);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::ATTACK4, new CThirdBMLaser)->Setduration(2.16f);

	m_AI->AddState((UINT)ENORMAL_MON_STATE::POWER1, new CThirdBMPowerUp)->Setduration(3.33f);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::POWER2, new CThirdBMPowerDown)->Setduration(3.8f);

}

void CBlackMage3::begin()
{
	Super::begin();
	//권능
	m_left_cool[0] = m_cooltime[0];
	//밀기
	m_left_cool[1] = 10.f;
	//끌기
	m_left_cool[2] = 7.f;
	//메테오
	m_left_cool[3] = 5.f;
	//레이저
	m_left_cool[4] = 9.f;

	m_acctime = 0.f;
}

#include "CLevelMgr.h"
void CBlackMage3::tick(float _DT)
{
	m_acctime += _DT;

	Super::tick(_DT);

	int size = (int)sizeof(m_left_cool) / sizeof(float);

	for (int i = 0; i < size; ++i)
	{
		m_left_cool[i] -= _DT;
	}


	if (KEY_TAP(KEY::_5))
	{
		m_AI->ChangeState((UINT)ENORMAL_MON_STATE::ATTACK1);
	}
	if (KEY_TAP(KEY::_6))
	{
		m_AI->ChangeState((UINT)ENORMAL_MON_STATE::ATTACK2);
	}
	if (KEY_TAP(KEY::_7))
	{
		m_AI->ChangeState((UINT)ENORMAL_MON_STATE::ATTACK3);
	}
	if (KEY_TAP(KEY::_8))
	{
		m_AI->ChangeState((UINT)ENORMAL_MON_STATE::ATTACK4);
	}

	if (KEY_TAP(KEY::F9))
	{
		m_AI->ChangeState((UINT)ENORMAL_MON_STATE::POWER1);
	}
	if (KEY_TAP(KEY::F10))
	{
		m_AI->ChangeState((UINT)ENORMAL_MON_STATE::POWER2);
	}
	if (KEY_TAP(KEY::F11))
	{
		m_AI->ChangeState((UINT)ENORMAL_MON_STATE::POWER3);
	}
}

void CBlackMage3::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	Super::BeginOverlap(_OwnCol, _OtherObj, _OtherCol);
}

void CBlackMage3::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
}

void CBlackMage3::EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	Super::EndOverlap(_OwnCol, _OtherObj, _OtherCol);
}

CBlackMage3::CBlackMage3(const CBlackMage3& _Origin)
	:m_cooltime{
		//0 : 권능
		50.f
		//1 : 밀기
		,3.f
	//2 : 끌기
	,20.f
	//3: 메테오
	,25.f
	//4:레이저 
	,15.f
	}
	, m_left_cool{ 0.f,0.f,0.f,0.f,0.f }
	, m_state_nick{ L"권능", L"밀기", L"끌기", L"메테오", L"레이저" }
	, m_state_numarr{
		(UINT)ENORMAL_MON_STATE::POWER1
		,(UINT)ENORMAL_MON_STATE::ATTACK1
		,(UINT)ENORMAL_MON_STATE::ATTACK2
		,(UINT)ENORMAL_MON_STATE::ATTACK3
		,(UINT)ENORMAL_MON_STATE::ATTACK4
	}
{
	m_Collider = GetComponent<CCollider>();
	m_AI = GetComponent<CStateMachine>();
}

CBlackMage3::~CBlackMage3()
{
}
