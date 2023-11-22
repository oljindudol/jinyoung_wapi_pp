#include "pch.h"
#include "CObj.h"
#include "CComponent.h"

#include "CTimeManager.h"
#include "CEngine.h"



CObj::CObj()
	: m_iLayerIdx(-1)
	, ort(ORT_LEFT)
{
}

CObj::CObj(const CObj& _Origin)
	: CEntity(_Origin)
	, m_Pos(_Origin.m_Pos)
	, m_Scale(_Origin.m_Scale)
	, m_iLayerIdx(-1)
	, ort(ORT_LEFT)
	, m_collisiontimetoplayer(0.f)
{
	for (size_t i = 0; i < _Origin.m_vecComponent.size(); ++i)
	{
		CComponent* pCom = _Origin.m_vecComponent[i]->Clone();
		pCom->m_pOwner = this;
		m_vecComponent.push_back(pCom);
	}
}


CObj::~CObj()
{
	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		if (nullptr != m_vecComponent[i])
			delete m_vecComponent[i];
	}
}



void CObj::tick(float _DT)
{
	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		m_vecComponent[i]->tick(_DT);
	}
}

void CObj::finaltick(float _DT)
{
	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		m_vecComponent[i]->finaltick(_DT);
	}
}
void CObj::render(HDC _dc)
{
	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		m_vecComponent[i]->render(_dc);
	}

	if (!DEBUG_RENDER)
		return;

	if (LAYER::UI == (UINT)m_iLayerIdx)
		return;


	SELECT_PEN(_dc, RED_PEN);

	Vec2 vRenderPos = GetRenderPos();
	MoveToEx(_dc, int(vRenderPos.x - 7.f), (int)vRenderPos.y, nullptr);
	LineTo(_dc, int(vRenderPos.x + 7.f), (int)vRenderPos.y);

	MoveToEx(_dc, int(vRenderPos.x), int(vRenderPos.y - 7.f), nullptr);
	LineTo(_dc, int(vRenderPos.x), int(vRenderPos.y + 7.f));
	//Vec2 vRenderPos = GetRenderPos();

	//Rectangle(_dc
	//	, int(vRenderPos.x - m_Scale.x / 2)
	//	, int(vRenderPos.y - m_Scale.y / 2)
	//	, int(vRenderPos.x + m_Scale.x / 2)
	//	, int(vRenderPos.y + m_Scale.y / 2));
}

void CObj::Destroy()
{
	FTask task;
	task.Type = TASK_TYPE::DELETE_OBJECT;
	task.Param_1 = (INT_PTR)this;

	CTaskMgr::GetInst()->AddTask(task);
}

void CObj::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	//if (_OtherObj->m_iLayerIdx==(UINT)LAYER::PLAYER ) 
		//m_collisiontimetoplayer = 0.f;
}

void CObj::EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	//if (_OtherObj->m_iLayerIdx == (UINT)LAYER::PLAYER) 
	//	m_collisiontimetoplayer = 0.f;
}

void CObj::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (_OtherObj->m_iLayerIdx == (UINT)LAYER::PLAYER)
		m_collisiontimetoplayer += DT;
}


void CObj::SetDead()
{
	m_bDead = true;

	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		m_vecComponent[i]->m_bDead = true;
	}
}

void CObj::SetLive()
{
	m_bDead = false;

	for (size_t i = 0; i < m_vecComponent.size(); ++i)
	{
		m_vecComponent[i]->m_bDead = false;
	}
}