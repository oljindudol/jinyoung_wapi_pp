#include "pch.h"
#include "CGenesisEgg.h"


#include "CGEggIdle.h"
#include "CGEggDie.h"
#include "CGEggHit.h"

#include "CMonsterMgr.h"
#include "CTimeManager.h"
#include "CLogMgr.h"
#include "CKeyMgr.h"
#include "CUIMgr.h"

CGenesisEgg::CGenesisEgg()
{
	ort = ORT_LEFT;
	m_s1 = L"fifth";
	m_s2 = L"genesisegg";


	//몇번째 몬스터 인지
	m_monsternum = CMonsterMgr::GetInst()->FindNextMonsterNumber(m_monstername);

	m_monstername = m_s1 + m_s2;
	SetName(m_monstername);// + L"_" + std::to_wstring(m_monsternum));


	SetScale(Vec2(507, 507));


	// Collider 컴포넌트 추가
	m_Collider = AddComponent<CCollider>(GetName() + L"Collider");

	m_Collider->SetScale(GetScale());
	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));

	// Animator 컴포넌트 추가
	m_Animator = AddComponent<CAnimator>(GetName() + L"Animator");
	m_Animator->CreateAnimation(m_s1, m_s2, L"idle", Vec2(0.f, 0.f), 1.f);
	m_Animator->CreateAnimation(m_s1, m_s2, L"die", Vec2(0.f, 0.f), 1.f ,-1);
	m_Animator->CreateAnimation(m_s1, m_s2, L"hit", Vec2(0.f, 0.f), 1.f, -1);

	m_Animator->Play(GetName() + L"idle");

	// 상태머신 컴포넌트 추가 및 설정
	m_AI = AddComponent<CStateMachine>(GetName() + L"AI");
	m_AI->AddState((UINT)ENORMAL_MON_STATE::IDLE, new CGEggIdle);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::DIE, new CGEggDie)->Setduration(1.f);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::BIND, new CGEggHit)->Setduration(0.2f);

}

void CGenesisEgg::begin()
{
}

void CGenesisEgg::tick(float _DT)
{
	Super::tick(_DT);

}

void CGenesisEgg::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	Super::BeginOverlap(_OwnCol, _OtherObj, _OtherCol);


}

CGenesisEgg::CGenesisEgg(const CGenesisEgg& _Origin)
{
}

CGenesisEgg::~CGenesisEgg()
{
}
