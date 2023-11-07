#include "pch.h"
#include "CPlatform.h"

#include "components.h"
#include "CLogMgr.h"

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
	if ((UINT)LAYER::PLAYER == _OtherObj->GetLayerIdx() ||
		(UINT)LAYER::MONSTER == _OtherObj->GetLayerIdx())
	{
		float plattop = (_OwnCol->GetPos().y - _OwnCol->GetScale().y / 2.f);
		float otherprevbottom = (_OtherCol->GetPrevPos().y + _OtherCol->GetScale().y / 2.f);
		//float otherbottom =( _OtherCol->GetPos().y +_OtherCol->GetScale().y / 2.f);

		//if (_OwnCol->GetName() == L"PlatformCollider2")
		//	LOG(LOG_LEVEL::LOG, std::to_wstring(otherbottom).c_str());
		//if ((UINT)LAYER::MONSTER == _OtherObj->GetLayerIdx())
		//	int a = 0;

		float yfix = ((UINT)LAYER::PLAYER == _OtherObj->GetLayerIdx()) ? 0.99f : 0.95f;


		if (plattop >= otherprevbottom * yfix)// && plattop <= otherbottom)
		{

			float up = (_OwnCol->GetScale().y / 2.f 
				+ _OtherCol->GetScale().y / 2.f 
				- abs(_OwnCol->GetPos().y
					- _OtherCol->GetPos().y)
				) / 2.f;

			_OtherObj->SetPos(Vec2(_OtherObj->GetPos().x, _OtherObj->GetPos().y - up));
		}
	}
}

void CPlatform::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if ((UINT)LAYER::PLAYER == _OtherObj->GetLayerIdx() ||
		(UINT)LAYER::MONSTER == _OtherObj->GetLayerIdx())
	{
		float plattop = (_OwnCol->GetPos().y - _OwnCol->GetScale().y / 2.f);
		float otherprevbottom = (_OtherCol->GetPrevPos().y + _OtherCol->GetScale().y / 2.f);

		float yfix = ((UINT)LAYER::PLAYER == _OtherObj->GetLayerIdx()) ? 0.99f : 0.97f;

		//위에서 올라왔으면, y스피드를 0으로 고정
		if (plattop > otherprevbottom)// *yfix)
		{

			CMovement* mov = _OtherObj->GetMovement();
			
			if (nullptr != mov)
			{
				Vec2 v = mov->GetVelocity();
				mov->SetVelocity(Vec2(v.x, 0.f));
			}
		}
	}

}
