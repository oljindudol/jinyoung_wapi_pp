#include "pch.h"
#include "CInventoryItem.h"

#include "CLevelMgr.h"
#include "CState.h"
#include "CAssetMgr.h"
#include "CEngine.h"
#include "CTexture.h"
#include "CKeyMgr.h"
#include "CItemInfoUI.h"

#include "CSoundMgr.h"

CInventoryItem::CInventoryItem()
	:m_itemon(false)
	,m_hovered(false)
	, m_ItemIcon(nullptr)
	, m_pCItemInfoUI(nullptr)
	, m_onclick(0.f)
{
	m_ItemIcon = CAssetMgr::GetInst()->LoadTexture(L"genesisbadge", L"texture\\anim\\item\\genesisbadge\\inven.png");

	SetScale(Vec2(m_ItemIcon->GetWidth(), m_ItemIcon->GetHeight()));

}

void CInventoryItem::tick(float _DT)
{
	Super::tick(_DT);

	m_onclick -= _DT;
}

void CInventoryItem::render(HDC _dc)
{
	if (true == m_itemon)
	{
		SettexturetoDc(_dc, m_ItemIcon, GetFinalPos());
	}

	//Super::render

	if (true == m_itemon && true == m_hovered)
	{
		m_pCItemInfoUI->m_showtrigger = true;
	}

}

void CInventoryItem::begin()
{
	m_hovered = false;
	m_onclick = 0.f;
}

void CInventoryItem::OnUnHovered(Vec2 _vMousePos)
{
	m_hovered = false;
}

void CInventoryItem::OnHovered(Vec2 _vMousePos)
{
	m_hovered = true;
}

void CInventoryItem::MouseOn(Vec2 _vMousePos)
{

}

void CInventoryItem::LBtnClicked(Vec2 _vMousePos)
{
	if (0.f < m_onclick)
	{
		DoubleClicked();
	}
	else
	{
		m_onclick = 0.5f;
		CAssetMgr::GetInst()->LoadSound(L"DragItem", L"sound\\DropItem.wav")->Play();
	}
}

void CInventoryItem::DoubleClicked()
{
	CAssetMgr::GetInst()->LoadSound(L"DragEnd", L"sound\\DragEnd.wav")->Play();

	CSkillMgr::GetInst()->ActivateSkill(L"fifthendrolluse",
		Vec2(990, 400), ORT_LEFT);

	CSkillMgr::GetInst()->ActivateSkill(L"fifthachievementuse",
		Vec2(990, 400), ORT_LEFT);

	m_itemon = false;
	m_pCItemInfoUI->m_showtrigger = false;

	CAssetMgr::GetInst()->LoadSound(L"BGM_04", L"sound\\LostSpace.wav")->Stop();
}

CInventoryItem::~CInventoryItem()
{
}
