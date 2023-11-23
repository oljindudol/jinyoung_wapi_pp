#include "pch.h"
#include "CCollider.h"

#include "CObj.h"
#include "CEngine.h"
#include "CCamera.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"

#include "CPal.h"


CCollider::CCollider(CObj* _Owner)
	: CComponent(_Owner)
	, m_iCollisionCount(0)
	, m_coltest(false)
{

}

CCollider::CCollider(const CCollider& _Origin)
	: CComponent(_Origin)
	, m_vOffsetPos(_Origin.m_vOffsetPos)
	, m_vScale(_Origin.m_vScale)
	, m_vFinalPos(_Origin.m_vFinalPos)
	, m_iCollisionCount(0)
	, m_coltest(false)
{
}

CCollider::~CCollider()
{

}

void CCollider::finaltick(float _DT)
{
	Vec2 vOwnerPos = GetOwner()->GetPos();

	//오너의 방향에따라 오프셋 수정
	int sign = ORT_LEFT == GetOwner()->ort ?  1:-1;

	m_PrevFinalPos = m_vFinalPos;

	m_vFinalPos = vOwnerPos + Vec2(m_vOffsetPos.x* sign, m_vOffsetPos.y);
	// 현재 속해있는 레이어에 충돌체(본인) 를 등록
	int iLayerIdx = GetOwner()->GetLayerIdx();

	// Collider 를 보유하고 있는 오브젝트가 레벨 소속이 아닌데 Finaltick 이 호출된 경우
	assert(!(iLayerIdx < 0));
	CLayer* pCurLayer = CLevelMgr::GetInst()->GetCurLevel()->GetLayer(iLayerIdx);
	pCurLayer->RegisterCollider(this);
}

void CCollider::render(HDC _dc)
{
	if (!DEBUG_RENDER)
		return;

	SELECT_PEN(_dc, GREEN_PEN);
	SELECT_BRUSH(_dc, (HBRUSH)GetStockObject(HOLLOW_BRUSH));

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vFinalPos);

	float rad = GetOwner()->GetRotation();

	if (m_coltest)
	{
		SelectObject(_dc, CPal::GetInst()->getHBrush(GREEN));
	}

	// render
	if (0.f == rad)
	{
		if (0 < m_iCollisionCount)
		{
			SELECT_PEN(_dc, RED_PEN);
			// render
			Rectangle(_dc, int(vRenderPos.x - m_vScale.x / 2.f)
				, int(vRenderPos.y - m_vScale.y / 2.f)
				, int(vRenderPos.x + m_vScale.x / 2.f)
				, int(vRenderPos.y + m_vScale.y / 2.f));
		}
		else
		{
			SELECT_PEN(_dc, GREEN_PEN);

			// render
			Rectangle(_dc, int(vRenderPos.x - m_vScale.x / 2.f)
				, int(vRenderPos.y - m_vScale.y / 2.f)
				, int(vRenderPos.x + m_vScale.x / 2.f)
				, int(vRenderPos.y + m_vScale.y / 2.f));
		}
	}
	else
	{
		Vec2 UpLeft(( m_vScale.x / -2.f), (m_vScale.y / -2.f));
		Vec2 UpRight((m_vScale.x / 2.f), (m_vScale.y / -2.f)) ;
		Vec2 DownRight((m_vScale.x / 2.f), (m_vScale.y / 2.f));
		Vec2 DownLeft((m_vScale.x / -2.f), (m_vScale.y / 2.f)) ;

		UpLeft = vRenderPos + RotateDot(UpLeft, rad);
		UpRight = vRenderPos + RotateDot(UpRight, rad);
		DownRight = vRenderPos + RotateDot(DownRight, rad);
		DownLeft = vRenderPos + RotateDot(DownLeft, rad);

		POINT p[4] = { {(LONG)UpLeft.x,(LONG)UpLeft.y} ,{(LONG)UpRight.x,(LONG)UpRight.y}
		,{(LONG)DownRight.x,(LONG)DownRight.y},{(LONG)DownLeft.x,(LONG)DownLeft.y} };


		if (m_coltest)
		{
			SelectObject(_dc, CPal::GetInst()->getHBrush(GREEN));
		}

		if (0 < m_iCollisionCount)
		{
			SELECT_PEN(_dc, RED_PEN);
			// render
			Polygon(_dc, p, 4);
			//MoveToEx(_dc, int(vRenderPos.x +UpLeft.x), int(vRenderPos.y+UpLeft.y), nullptr);
			//LineTo(_dc, int(vRenderPos.x+UpRight.x), int(vRenderPos.y+UpRight.y));
			//LineTo(_dc, int(vRenderPos.x+DownRight.x), int(vRenderPos.y + DownRight.y));
			//LineTo(_dc, int(vRenderPos.x+DownLeft.x), int(vRenderPos.y + DownLeft.y));
			//LineTo(_dc, int(vRenderPos.x+UpLeft.x), int(vRenderPos.y + UpLeft.y));

		}
		else
		{
			SELECT_PEN(_dc, GREEN_PEN);

			// render
			Polygon(_dc, p, 4);
			//MoveToEx(_dc, int(vRenderPos.x + UpLeft.x), int(vRenderPos.y + UpLeft.y), nullptr);
			//LineTo(_dc, int(vRenderPos.x + UpRight.x), int(vRenderPos.y + UpRight.y));
			//LineTo(_dc, int(vRenderPos.x + DownRight.x), int(vRenderPos.y + DownRight.y));
			//LineTo(_dc, int(vRenderPos.x + DownLeft.x), int(vRenderPos.y + DownLeft.y));
			//LineTo(_dc, int(vRenderPos.x + UpLeft.x), int(vRenderPos.y + UpLeft.y));
		}
	}






	//name
	SetBkMode(_dc, OPAQUE);
	SELECT_FONT(_dc, FONT_TYPE::STATUS_BAR_POINT);
	SetTextColor(_dc, RGB(0, 0, 0));
	TextOut(_dc, (int)(vRenderPos.x - m_vScale.x / 2.f), (int)(vRenderPos.y - m_vScale.y / 2.f -10.f), GetName().c_str(), (int)GetName().length());

}




void CCollider::BeginOverlap(CCollider* _OtherCol)
{
	++m_iCollisionCount;
	GetOwner()->BeginOverlap(this, _OtherCol->GetOwner(), _OtherCol);
}

void CCollider::Overlap(CCollider* _OtherCol)
{
	GetOwner()->Overlap(this, _OtherCol->GetOwner(), _OtherCol);
}


void CCollider::EndOverlap(CCollider* _OtherCol)
{
	--m_iCollisionCount;
	GetOwner()->EndOverlap(this, _OtherCol->GetOwner(), _OtherCol);
}

