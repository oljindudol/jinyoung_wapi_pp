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



void CBlackMage2::render(HDC _dc)
{
	Super::render(_dc);

	//Vec2 debug_renpos = GetRenderPos() - GetScale()/2 - Vec2(165,0) ;

	//SELECT_BRUSH(_dc, (HBRUSH)GetStockObject(WHITE_BRUSH));
	//SELECT_PEN(_dc, WT_PEN);

	//Rectangle(_dc
	//	, (int)debug_renpos.x -1
	//	, (int)debug_renpos.y
	//	, (int)(debug_renpos.x + 165.f)
	//	, (int)(debug_renpos.y + GetScale().y/2 -50)
	//);

	//SetBkColor(_dc, RGB(255, 255, 255));

	//auto curstate = m_AI->GetCurState();
	//auto curacctime = curstate->GetAcctime();
	//auto curdur = curstate->GetDuration();

	//int yoffset = 0;
	//int yoffsetsize = 18;

	//SELECT_FONT2(_dc, FONT_TYPE::STATUS_DEBUG);
	//
	////현재상태
	//if (L"대기상태" == curstate->GetName())
	//{
	//	SetBkColor(_dc, RGB(255, 255, 255));
	//	SetTextColor(_dc, RGB(0, 0, 255));
	//}
	//else
	//{
	//	SetBkColor(_dc, RGB(255, 255, 0));
	//	SetTextColor(_dc, RGB(255, 0, 0));
	//}

	//wstring curstate_line = L"현재상태:" + curstate->GetName();
	//TextOut(_dc, (int)(debug_renpos.x), (int)(debug_renpos.y) + yoffset* yoffsetsize, curstate_line.c_str(), (int)curstate_line.length());
	//++yoffset;


	//wstring percwstr = std::to_wstring((curacctime / curdur) *100.f);
	//wstring curtimestr = std::to_wstring(curacctime);
	//wstring curdurstr = std::to_wstring(curdur);


	//SetBkColor(_dc, RGB(255, 255, 255));
	////if (curacctime > curdur)
	////{
	////	SetTextColor(_dc, RGB(0, 0, 255));
	////}

	////상태누적시간
	//wstring acctime_line = L"누적시간:" + curtimestr.substr(0, curtimestr.find(L".")) + L"/" + curdurstr.substr(0, curdurstr.find(L"."))
	//	+ L"(" + percwstr.substr(0, percwstr.find(L".")) + L"%)";
	//TextOut(_dc, (int)(debug_renpos.x), (int)(debug_renpos.y) + yoffset * yoffsetsize, acctime_line.c_str(), (int)acctime_line.length());
	//++yoffset; ++yoffset;

	//SetTextColor(_dc, RGB(0, 0, 0));

	////상태별 남은 쿨타임
	//wstring statecool_line = L"상태별 남은 쿨타임:";
	//TextOut(_dc, (int)(debug_renpos.x), (int)(debug_renpos.y) + yoffset * yoffsetsize, statecool_line.c_str(), (int)statecool_line.length());
	//++yoffset;

	//int size = (int)sizeof(m_left_cool) / sizeof(float);
	//for (int i = 0; i < size; ++i)
	//{

	//	if (m_left_cool[i] < 0.f)
	//	{
	//		SetBkColor(_dc, RGB(255, 255, 255));
	//		SetTextColor(_dc, RGB(0, 0, 255));
	//	}
	//	else
	//	{
	//		SetBkColor(_dc, RGB(255, 255, 255));
	//		SetTextColor(_dc, RGB(0, 0, 0));
	//	}
	//	if (curacctime * 1.1f > m_cooltime[i] - m_left_cool[i] &&
	//		curacctime * 0.9f < m_cooltime[i] - m_left_cool[i]
	//		&& 5.f < m_acctime )
	//	{
	//		SetBkColor(_dc, RGB(255, 255, 0));
	//		SetTextColor(_dc, RGB(255, 0, 0));
	//	}

	//	wstring leftcool = std::to_wstring(m_left_cool[i]);
	//	wstring cool = std::to_wstring(m_cooltime[i]);
	//	wstring tmpmsg = RSpacePad(m_state_nick[i],4) + L": " + LSpacePad_Number(leftcool.substr(0, leftcool.find(L".")),2)
	//		+ L"/" 
	//		+ LSpacePad_Number(cool.substr(0, cool.find(L".")),2);
	//	TextOut(_dc, (int)(debug_renpos.x), (int)(debug_renpos.y) + yoffset * yoffsetsize, tmpmsg.c_str(), (int)tmpmsg.length());
	//	++yoffset;
	//}


	//SetBkColor(_dc, RGB(255, 255, 255));
	//SetTextColor(_dc, RGB(0, 0, 0));


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
