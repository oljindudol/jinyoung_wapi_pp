#include "pch.h"
#include "CBlackMage2.h"

#include "CSecondBMBlindness.h"
#include "CSecondBMEyeofRuin.h"
#include "CSecondBMMorningStarFall.h"
#include "CSecondBMNoxSpear.h"
#include "CSecondBMPowerLeft.h"
#include "CSecondBMPowerMiddle.h"
#include "CSecondBMPowerRight.h"
#include "CSecondBMDie.h"
#include "CSecondBMIdle.h"

#include "CMonsterMgr.h"
#include "CTimeManager.h"
#include "CLogMgr.h"
#include "CKeyMgr.h"
#include "CUIMgr.h"

#include "CPal.h"

CBlackMage2::CBlackMage2()
	:m_cooltime{
	//0 : 권능
	50.f
	//1 : 블라인드
	,50.f
	//2 : 파멸의 눈
	,25.f
	//1: 모닝스타폴
	,50.f
	//3:녹스스피어 
	,20.f
	}
	, m_left_cool{ 0.f,0.f,0.f,0.f,0.f }
	,m_state_nick{ L"권능", L"암흑", L"파멸의눈", L"메테오", L"녹스피어" }
	, m_state_numarr{
		(UINT)ENORMAL_MON_STATE::POWER1
		,(UINT)ENORMAL_MON_STATE::ATTACK1 
		,(UINT)ENORMAL_MON_STATE::ATTACK2
		,(UINT)ENORMAL_MON_STATE::ATTACK3
		,(UINT)ENORMAL_MON_STATE::ATTACK4
	}
{
	ort = ORT_LEFT;
	m_s1 = L"second";
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
	m_Animator->CreateAnimation(L"second", L"blackmage", L"idle", Vec2(0.f, 0.f), 1.f);
	m_Animator->CreateAnimation(L"second", L"blackmage", L"die",  Vec2(0.f, 0.f),  1.f);

	m_Animator->CreateAnimation(L"second", L"blackmage", L"morningstarfall", Vec2(-8.f, 0.f),1.f,  -1);
	m_Animator->CreateAnimation(L"second", L"blackmage", L"eyeofruin", Vec2(7.f, -14.f),1.f,  -1);
	m_Animator->CreateAnimation(L"second", L"blackmage", L"noxspear", Vec2(-8.f, 0.f), 1.f, -1);
	m_Animator->CreateAnimation(L"second", L"blackmage", L"blindness", Vec2(18.f, 0.f),1.f,  -1);

	m_Animator->CreateAnimation(L"second", L"blackmage", L"powerleft", Vec2(-75.f, 0.f), 1.f, -1);
	m_Animator->CreateAnimation(L"second", L"blackmage", L"powermiddle", Vec2(7.f, 0.f), 1.f, -1);
	m_Animator->CreateAnimation(L"second", L"blackmage", L"powerright", Vec2(84.f, 0.f), 1.f, -1);

	m_Animator->Play(GetName() + L"idle");



	// 상태머신 컴포넌트 추가 및 설정
	m_AI = AddComponent<CStateMachine>(GetName() + L"AI");
	m_AI->AddState((UINT)ENORMAL_MON_STATE::IDLE, new CSecondBMIdle)->Setduration(5.f);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::DIE, new CSecondBMDie)->Setduration(4.f);

	m_AI->AddState((UINT)ENORMAL_MON_STATE::ATTACK1, new CSecondBMBlindness)->Setduration(2.16f);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::ATTACK2, new CSecondBMEyeofRuin)->Setduration(2.16f);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::ATTACK3, new CSecondBMMorningStarFall)->Setduration(2.16f);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::ATTACK4, new CSecondBMNoxSpear)->Setduration(2.16f);

	m_AI->AddState((UINT)ENORMAL_MON_STATE::POWER1, new CSecondBMPowerLeft)->Setduration(3.33f);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::POWER2, new CSecondBMPowerMiddle)->Setduration(3.8f);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::POWER3, new CSecondBMPowerRight)->Setduration(3.51f);



	//m_AI->AddDataToBlackboard(L"Att1 Range", 400.f);
	//m_AI->AddDataToBlackboard(L"Detect Range", firstmon_attack2_dist);
	//m_AI->AddDataToBlackboard(L"Att3 Range", 1500.f);
	//m_AI->AddDataToBlackboard(L"Speed", 300.f);


}

void CBlackMage2::begin()
{

	Super::begin();
	m_left_cool[0] = 50.f;
	m_left_cool[1] = 0.f;
	m_left_cool[2] = 20.f;
	m_left_cool[3] = 0.f;
	m_left_cool[4] = 0.f;

	m_acctime = 0.f;
}

void CBlackMage2::tick(float _DT)
{
	m_acctime += _DT;

	Super::tick(_DT);

	int size = (int)sizeof(m_left_cool) / sizeof(float);

	for (int i = 0; i < size; ++i)
	{
		m_left_cool[i] -= _DT;
	}


	if (KEY_TAP(KEY::M))
	{
		CUIMgr::GetInst()->SetUIOnOffResponsible(L"statedebugui");
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

void CBlackMage2::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	Super::BeginOverlap(_OwnCol, _OtherObj, _OtherCol);

}

void CBlackMage2::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
}

void CBlackMage2::EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	Super::EndOverlap(_OwnCol, _OtherObj, _OtherCol);
}


CBlackMage2::CBlackMage2(const CBlackMage2& _Origin)
	:m_cooltime{
		//0 : 권능
		50.f
		//1 : 블라인드
		,30.f
		//2 : 파멸의 눈
		,20.f
		//1: 모닝스타폴
		,50.f
		//3:녹스스피어 
		,20.f
	}
	, m_state_nick{ L"권능", L"암흑", L"파멸의눈", L"메테오", L"녹스피어" }
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

CBlackMage2::~CBlackMage2()
{
}
