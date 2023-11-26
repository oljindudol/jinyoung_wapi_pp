#include "pch.h"
#include "CInventory.h"

#include "CLevelMgr.h"
#include "CState.h"
#include "CAssetMgr.h"
#include "CEngine.h"
#include "CTexture.h"
#include "CInventoryItem.h"
#include "CKeyMgr.h"
#include "CItemInfoUI.h"

CInventory::CInventory()
	:m_UItex(nullptr)
{
	m_uiname = L"inventoryui";
	SetPos(Vec2(1000.f, 200.f));

	m_UItex = CAssetMgr::GetInst()->LoadTexture(L"inventory", L"texture\\inventory.png");

	SetScale(Vec2(m_UItex->GetWidth(), m_UItex->GetHeight()));

	Vec2 accoffset = Vec2(12, 55);
	Vec2 xoffset = Vec2( 36.f,0.f);
	Vec2 yoffset = Vec2( 0.f, 35.f);

	auto piui = new CItemInfoUI;

	for (int i = 0; i < 24; ++i)
	{
		auto tmp = new CInventoryItem;
		tmp->SetPos(accoffset);
		tmp->m_pCItemInfoUI = piui;
	
		itemarr[i] = tmp;
		AddChildUI(tmp);

		if (0 == (i + 1) % 4)
		{
			accoffset = accoffset + yoffset - xoffset * 3;
		}
		else
		{
			accoffset = accoffset + xoffset;
		}
	}
	AddChildUI(piui);
}

void CInventory::tick(float _DT)
{
	if (IsLBtnDown())
	{
		Vec2 vDiff = m_vLbtnDownPos - CKeyMgr::GetInst()->GetMousePos();
		Vec2 vPos = GetPos();
		vPos -= vDiff;
		SetPos(vPos);

		m_vLbtnDownPos = CKeyMgr::GetInst()->GetMousePos();
	}

	Super::tick(_DT);
}

void CInventory::render(HDC _dc)
{
	SettexturetoDc(_dc, m_UItex, GetFinalPos());
	Super::render(_dc);
}

void CInventory::begin()
{
	// 자식 UI 들 Begin 호출
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->begin();
	}
}

void CInventory::LBtnDown(Vec2 _MousePos)
{
	// 마우스 왼쪽 버튼이 눌렸을 때 마우스의 위치를 기록
	m_vLbtnDownPos = _MousePos;
}

void CInventory::GetItem()
{
	for (int i = 0; i < 24; ++i)
	{
		if (false == itemarr[i]->m_itemon)
		{
			itemarr[i]->m_itemon = true;
			return;
		}
	}

}

CInventory::~CInventory()
{
}
