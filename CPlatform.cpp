#include "pch.h"
#include "CPlatform.h"

#include "components.h"

CPlatform::CPlatform()
{

}

CPlatform::CPlatform(const CPlatform& _Origin)
	: CObj(_Origin)
	, m_Collider(nullptr)
{
	m_Collider = GetComponent<CCollider>();
}


CPlatform::~CPlatform()
{

}

void CPlatform::tick(float _DT)
{

}

void CPlatform::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if ((UINT)LAYER::PLAYER == _OtherObj->GetLayerIdx())
	{
		float plattop = _OwnCol->GetPos().y - _OwnCol->GetScale().y / 2.f;
		float otherbottom = _OtherCol->GetPos().y + _OtherCol->GetScale().y / 2.f;


		if (plattop >= otherbottom)
		{
			float up = (_OwnCol->GetScale().y / 2.f +
				_OtherCol->GetScale().y / 2.f -
				abs(_OwnCol->GetPos().y
					- _OtherCol->GetPos().y)
				) / 2.f;

			_OtherObj->SetPos(Vec2(_OtherObj->GetPos().x, _OtherObj->GetPos().y - up));
		}

	}



}