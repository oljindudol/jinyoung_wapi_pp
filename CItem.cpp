#include "pch.h"
#include "CItem.h"


#include "CCollider.h"
#include "CProjectile.h"
#include "CAssetMgr.h"
#include "CTexture.h"
#include "CLevel.h"

#include "CItemOnAir.h"
#include "CItemOnGround.h"
#include "CItemAbsorbing.h"
#include "CSoundMgr.h"

#include "CKeyMgr.h"

CItem::CItem(wstring _name, int _number)
	:Super::CObj()
	,m_Animator(nullptr)
	, m_Collider(nullptr)
	, m_SM(nullptr)
	, m_s1(_name)
	, m_itemnum(_number)
{


	SetName(m_s1 + L"_" + std::to_wstring(m_itemnum));
	SetScale(Vec2(35, 30));


	// Animator 컴포넌트 추가
	m_Animator = AddComponent<CAnimator>(GetName() + L"Animator");
	m_Animator->CreateTurnAnimation(L"item", m_s1, L"onair", .278f, 10, Vec2(0.f, 0.f), 1.f , 0);
	m_Animator->CreateAnimation(L"item", m_s1, L"onground", Vec2(0.f, 0.f), 1.f, 0);
	m_Animator->CreateAnimation(L"item", m_s1, L"absorbing", Vec2(0.f, 0.f), 1.f, 0);

	// Collider 컴포넌트 추가
	m_Collider = AddComponent<CCollider>(GetName() + L"Collider");
	m_Collider->SetScale(GetScale());
	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));

	m_Animator->Play(L"item"+ m_s1 + L"onair");

	// 상태머신 컴포넌트 추가 및 설정
	m_SM = AddComponent<CStateMachine>(GetName() + L"AI");
	m_SM->AddState((UINT)ITEM_STATE::ON_AIR, new CItemOnAir);
	m_SM->AddState((UINT)ITEM_STATE::ON_GROUND, new CItemOnGround);
	m_SM->AddState((UINT)ITEM_STATE::ABSORBING, new CItemAbsorbing)->Setduration(.6f);
}

void CItem::begin()
{
	SetPos(CLevelMgr::GetInst()->GetCurLevelMiddle());

	m_SM->ChangeState((UINT)ITEM_STATE::ON_AIR);
}


void CItem::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	Super::Overlap(_OwnCol, _OtherObj, _OtherCol);

	if (KEY_TAP(KEY::Z))
	{
		if ((UINT)ITEM_STATE::ON_GROUND == m_SM->GetCurStateNum()
			&& (UINT)LAYER::PLAYER == _OtherObj->GetLayerIdx())
		{
			CSoundMgr::GetInst()->PlayMultipleSound(L"aquireitem", 1, 0.05f);
			m_SM->ChangeState((UINT)ITEM_STATE::ABSORBING);
		}


	}



}

void CItem::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	Super::BeginOverlap(_OwnCol, _OtherObj, _OtherCol);

	if ((UINT)ITEM_STATE::ON_AIR == m_SM->GetCurStateNum()
		&& (UINT)LAYER::PLATFORM == _OtherObj->GetLayerIdx())
	{
		m_SM->ChangeState((UINT)ITEM_STATE::ON_GROUND);
	}

}

void CItem::render(HDC _dc)
{
	Super::render(_dc);
}

CItem::~CItem()
{
}
