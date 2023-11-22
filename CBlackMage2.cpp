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


CBlackMage2::CBlackMage2()
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
	m_AI->AddState((UINT)ENORMAL_MON_STATE::IDLE, new CSecondBMIdle);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::DIE, new CSecondBMDie);

	m_AI->AddState((UINT)ENORMAL_MON_STATE::ATTACK1, new CSecondBMMorningStarFall);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::ATTACK2, new CSecondBMEyeofRuin);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::ATTACK3, new CSecondBMNoxSpear);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::ATTACK4, new CSecondBMBlindness);

	m_AI->AddState((UINT)ENORMAL_MON_STATE::POWER1, new CSecondBMPowerLeft);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::POWER2, new CSecondBMPowerMiddle);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::POWER3, new CSecondBMPowerRight);


	//m_AI->AddDataToBlackboard(L"Att1 Range", 400.f);
	//m_AI->AddDataToBlackboard(L"Detect Range", firstmon_attack2_dist);
	//m_AI->AddDataToBlackboard(L"Att3 Range", 1500.f);
	//m_AI->AddDataToBlackboard(L"Speed", 300.f);


}

void CBlackMage2::begin()
{
	Super::begin();
}

void CBlackMage2::tick(float _DT)
{
	Super::tick(_DT);

}

void CBlackMage2::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	Super::BeginOverlap(_OwnCol, _OtherObj, _OtherCol);



	//CPlatform* pPlatform = dynamic_cast<CPlatform*>(_OtherObj);

	//if ((nullptr != pPlatform) && (pPlatform->GetLayerIdx() == LAYER::PLATFORM))
	//{
	//	m_Movement->SetGround(true);

	//	return;
	//}
}

void CBlackMage2::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
}

void CBlackMage2::EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	Super::EndOverlap(_OwnCol, _OtherObj, _OtherCol);
}

CBlackMage2::CBlackMage2(const CBlackMage2& _Origin)
{
	m_Collider = GetComponent<CCollider>();
	m_AI = GetComponent<CStateMachine>();
}

CBlackMage2::~CBlackMage2()
{
}
