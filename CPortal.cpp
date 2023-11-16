#include "pch.h"
#include "CPortal.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"

CPortal::CPortal()
	:m_animator(nullptr)
	,m_collider(nullptr)
	,m_togo(LEVEL_TYPE::END)
{
	SetName(L"portal0");
	m_animator = AddComponent<CAnimator>(GetName()+L"animator");
	m_animator->
		CreateAnimation(L"common", L"portal",L"idle",
			Vec2(0.f, -120.f), 1.f, 0, ORT_LEFT);

	m_animator->Play(L"commonportalidle");

	m_collider = AddComponent<CCollider>(GetName() + L"collider");
	m_collider->SetOffsetPos(Vec2(0.f, -40.f));
	m_collider->SetScale(Vec2(20.f, 80.f));
	m_togo = LEVEL_TYPE::PHASE_FIRST;

}

CPortal::CPortal(const CPortal& _Origin) 
	:m_animator(nullptr)
	, m_collider(nullptr)
	, m_togo(LEVEL_TYPE::END)
{
}

CPortal::~CPortal()
{
}



void CPortal::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (KEY_TAP(KEY::UP))
	{
		ChangeLevel(m_togo);
	}
}

