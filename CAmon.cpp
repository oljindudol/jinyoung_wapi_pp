#include "pch.h"
#include "CAmon.h"

#include "CUIMgr.h"
#include "CMonsterMgr.h"
#include "CLevelMgr.h"
#include "CPlayer.h"


CAmon::CAmon()
	:m_dialogbox(nullptr)
	,m_pAnimator2(nullptr)
	,m_npcstate(ENPC_STATE::HAVE_QUEST)
{
	ort = ORT_LEFT;
	m_s1 = L"zero";
	m_s2 = L"amon";

	m_monstername = m_s1 + m_s2;

	//몇번째 몬스터 인지
	m_monsternum = CMonsterMgr::GetInst()->FindNextMonsterNumber(m_monstername);

	SetName(m_monstername + L"_" + std::to_wstring(m_monsternum));

	SetScale(Vec2(53.f, 70.f));

	m_MonsterLayer = (UINT)LAYER::NPC;

	// Animator 컴포넌트 추가
	m_Animator = AddComponent<CAnimator>(GetName() + L"Animator");
	m_Animator->CreateAnimation(m_s1, m_s2, L"idle", Vec2(0.f, 0.f), 1.f, 0);
	m_Animator->Play(m_s1 + m_s2 + L"idle");

	// Animator2 컴포넌트 추가 (머리위 전구)
	m_pAnimator2 = AddComponent<CAnimator>(GetName() + L"Animator2");
	m_pAnimator2->CreateAnimation(m_s1, m_s2, L"have", Vec2(5.f, -70.f), 1.f, 0);
	m_pAnimator2->CreateAnimation(m_s1, m_s2, L"ongoing", Vec2(5.f, -70.f), 1.f, 0);
	m_pAnimator2->CreateAnimation(m_s1, m_s2, L"complete", Vec2(5.f, -70.f), 1.f, 0);
	m_pAnimator2->CreateAnimation(m_s1, m_s2, L"none", Vec2(0.f, -2000.f), 1.f, 0);

	m_pAnimator2->Play(m_s1 + m_s2 + L"have");

	// Collider 컴포넌트 추가
	m_Collider = AddComponent<CCollider>(GetName() + L"Collider");
	m_Collider->SetScale(GetScale());

	if (ENPC_STATE::HAVE_QUEST == m_npcstate)
		m_pAnimator2->Play(m_s1 + m_s2 + L"have");
}


void CAmon::tick(float _DT)
{
	Super::tick(_DT);

}


void CAmon::begin()
{
	m_Animator->Play(m_s1 + m_s2 + L"idle");

	m_npcstate;
	if (ENPC_STATE::ON_QUEST == m_npcstate &&
		true == CLevelMgr::GetInst()->GetPlayer()->HasCompleteMission())
	{
		m_npcstate = ENPC_STATE::COMPLETE_QUEST;
	}

	if(ENPC_STATE::HAVE_QUEST == m_npcstate)
		m_pAnimator2->Play(m_s1 + m_s2 + L"have");
	if (ENPC_STATE::ON_QUEST == m_npcstate)
		m_pAnimator2->Play(m_s1 + m_s2 + L"ongoing");
	if (ENPC_STATE::COMPLETE_QUEST == m_npcstate)
		m_pAnimator2->Play(m_s1 + m_s2 + L"complete");
	if (ENPC_STATE::NONE == m_npcstate)
		m_pAnimator2->Play(m_s1 + m_s2 + L"none");

	m_Collider->InitColCnt();

}


void CAmon::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	//if (LAYER::PLATFORM == (UINT)_OtherObj->GetLayerIdx())
	//{
	//	m_metfloor = true;
	//	m_AI->ChangeState((UINT)ENORMAL_MON_STATE::DIE);
	//}
	CUIMgr::GetInst()->SetUIOnOffResponsible(L"dialogbox");
	
	int a = 0;

}


CAmon::CAmon(const CAmon& _Origin)
{
}

CAmon::~CAmon()
{
}
