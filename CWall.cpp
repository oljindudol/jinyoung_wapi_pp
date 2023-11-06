#include "pch.h"
#include "CWall.h"


CWall::CWall()
	: m_Collider(nullptr)
{
}

CWall::CWall(const CWall& _Origin)
	: CObj(_Origin)
	, m_Collider(nullptr)
{
}

CWall::~CWall()
{
}


void CWall::tick(float _DT)
{
}

void CWall::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if ((UINT)LAYER::PLAYER == _OtherObj->GetLayerIdx())
	{
		Vec2 OwnPos = _OwnCol->GetPos();
		Vec2 OwnprevPos = _OwnCol->GetPrevPos();
		Vec2 OwnScale = _OwnCol->GetScale();
		Vec2 OtherPos = _OtherCol->GetPos();
		Vec2 OtherScale = _OtherCol->GetScale();

		// 벽이 왼쪽  , 상대가 오른쪽에있으면 +
		// 벽이 오른쪽, 왼쪽이면		 -
		int ortsign = (OtherPos.x - OwnprevPos.x)>0 ? +1 : -1 ;

		float wallend = OwnPos.x +  (OwnScale.x / 2.f) *ortsign;
		float otherend = OtherPos.x - (OtherScale.x / 2.f) * ortsign;


		if (plattop >= otherbottom)
		{
			float up = (_OwnCol->GetScale().x / 2.f +
				_OtherCol->GetScale().x / 2.f -
				abs(_OwnCol->GetPos().x
					- _OtherCol->GetPos().x)
				) / 2.f;

			_OtherObj->SetPos(Vec2(_OtherObj->GetPos().y - up, _OtherObj->GetPos().x));
		}
	}


}

