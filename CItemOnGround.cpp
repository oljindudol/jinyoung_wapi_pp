#include "pch.h"
#include "CItemOnGround.h"
#include "CItem.h"

CItemOnGround::CItemOnGround()
	:m_pItem(nullptr)

{
}

void CItemOnGround::finaltick(float _DT)
{

	m_ItemVel = m_ItemVel 
		//º¹¿ø·Â
		+ (m_initialpos- m_pItem->GetPos()) * 5.f* _DT;


	m_pItem->SetPos(m_pItem->GetPos() + m_ItemVel * _DT);
}

void CItemOnGround::Enter()
{
	m_pItem = dynamic_cast<CItem*>(GetOwner());
	if (nullptr != m_pItem)
	{
		m_pItem->GetAnimator()->Play(L"item" + m_pItem->GetItemName() + L"onground");
		m_initialpos = m_pItem->GetPos();
	}
	m_ItemVel = Vec2(0, 10);
}

void CItemOnGround::Exit()
{
}

CItemOnGround::~CItemOnGround()
{
}
