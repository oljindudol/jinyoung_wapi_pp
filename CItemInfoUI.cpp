#include "pch.h"
#include "CItemInfoUI.h"

#include "CLevelMgr.h"
#include "CState.h"
#include "CAssetMgr.h"
#include "CEngine.h"
#include "CTexture.h"
#include "CKeyMgr.h"

CItemInfoUI::CItemInfoUI()
	:m_UItex(nullptr)
	,m_showtrigger(false)
{
	m_UItex = CAssetMgr::GetInst()->LoadTexture(L"genesisbadgeinfo", L"texture\\anim\\item\\genesisbadge\\info.PNG");

}

void CItemInfoUI::render(HDC _dc)
{
	if (true == m_showtrigger)
	{
		SettexturetoDc(_dc, m_UItex, CKeyMgr::GetInst()->GetMousePos() - Vec2(m_UItex->GetWidth(), (UINT)0));
	}
	m_showtrigger = false;
}

void CItemInfoUI::begin()
{
	m_showtrigger = false;
}

CItemInfoUI::~CItemInfoUI()
{
}
