#include "pch.h"
#include "CItemOnAir.h"
#include "CItem.h"
#include "CLevelMgr.h"



CItemOnAir::CItemOnAir()
	:m_pItem(nullptr)
{

}

void CItemOnAir::finaltick(float _DT)
{
	m_ItemVel = m_ItemVel + Vec2(0,1200) * _DT;
	m_pItem->SetPos(m_pItem->GetPos() + m_ItemVel*_DT);
}

void CItemOnAir::Enter()
{
	m_pItem = dynamic_cast<CItem*>(GetOwner());
	if (nullptr != m_pItem)
	{
		m_pItem->GetAnimator()->Play(L"item" + m_pItem->GetItemName() + L"onair");
		Vec2 middle = CLevelMgr::GetInst()->GetCurLevelMiddle();
		float midx = middle.x - 220.f;

		m_ItemVel = Vec2((midx / 20.f) * m_pItem->GetItemNumber() - midx, -500.f);
	}
}

void CItemOnAir::Exit()
{

}

CItemOnAir::~CItemOnAir()
{
}
