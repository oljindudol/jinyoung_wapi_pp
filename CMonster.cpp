#include "pch.h"
#include "CMonster.h"

#include "CCollider.h"
#include "CProjectile.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CNormalMonIdle.h"
#include "CNormalMonTrace.h"


CMonster::CMonster()
	: m_Info{}
	, m_Collider(nullptr)
	, m_AI(nullptr)
	, m_Animator(nullptr)
	, m_Movement(nullptr)
{
;
}

CMonster::CMonster(const CMonster& _Origin)
	: CObj(_Origin)
	, m_Info(_Origin.m_Info)
	, m_Collider(nullptr)
	, m_AI(nullptr)
	, m_Animator(nullptr)
	, m_Movement(nullptr)
{
}

CMonster::~CMonster()
{

}

void CMonster::begin()
{

}


void CMonster::tick(float _DT)
{
	Super::tick(_DT);
}


//void CMonster::render(HDC _dc)
//{
//	//Vec2 vRenderPos = GetRenderPos();
//	//Vec2 vScale = GetScale();
//
//	//BLENDFUNCTION blend = {};
//	//blend.BlendOp = AC_SRC_OVER;
//	//blend.BlendFlags = 0;
//
//	//blend.SourceConstantAlpha = 255; // 0 ~ 255
//	//blend.AlphaFormat = AC_SRC_ALPHA; // 0
//
//	//AlphaBlend(_dc
//	//	, int(vRenderPos.x - m_Texture->GetWidth() / 2.f)
//	//	, int(vRenderPos.y - m_Texture->GetHeight() / 2.f)
//	//	, m_Texture->GetWidth()
//	//	, m_Texture->GetHeight()
//	//	, m_Texture->GetDC()
//	//	, 0, 0
//	//	, m_Texture->GetWidth()
//	//	, m_Texture->GetHeight()
//	//	, blend);
//
//	Super::render(_dc);
//}


void CMonster::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	//if (dynamic_cast<CProjectile*>(_OtherObj))
	//{
	//	m_Info.HP -= 1.f;

	//	if (m_Info.HP <= 0.f)
	//	{
	//		Destroy();
	//	}
	//}
}
