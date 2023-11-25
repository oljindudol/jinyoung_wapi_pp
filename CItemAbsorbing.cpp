#include "pch.h"
#include "CItemAbsorbing.h"

#include "CLevelMgr.h"
#include "CItem.h"
#include "CAnim.h"

CItemAbsorbing::CItemAbsorbing()
	:m_pItem(nullptr)
	,m_pAnim(nullptr)
{
}

void CItemAbsorbing::finaltick(float _DT)
{
	m_acctime += _DT;

	float stateperc = (m_stateduration - m_acctime) / m_stateduration;
	if (0.f > stateperc)
		stateperc = 0.f;
	m_pAnim->SetAlpha((int)(255 * stateperc));

	m_ItemVel = m_ItemVel + Vec2((m_pPlayer->GetPos().x - m_pItem->GetPos().x) *5.f , 1200.f) * _DT;

	m_pItem->SetPos(
		m_pItem->GetPos() + m_ItemVel * _DT);

	if (m_stateduration < m_acctime)
		m_pItem->Destroy();

}

void CItemAbsorbing::Enter()
{
	Super::Enter();

	m_pPlayer = CLevelMgr::GetInst()->GetPlayer();
	m_pItem = dynamic_cast<CItem*>(GetOwner());
	if (nullptr != m_pItem)
	{
		m_pAnim = m_pItem->GetAnimator()->Play(L"item" + m_pItem->GetItemName() + L"absorbing");

		Vec2 middle = CLevelMgr::GetInst()->GetCurLevelMiddle();
		float midx = middle.x - 220.f;

		m_ItemVel = Vec2((midx / 20.f) * m_pItem->GetItemNumber() - midx, -500.f);
	}
	
		
	m_ItemVel = Vec2((m_pPlayer->GetPos().x - m_pItem->GetPos().x), -430.f);
}

void CItemAbsorbing::Exit()
{
}

CItemAbsorbing::~CItemAbsorbing()
{
}
