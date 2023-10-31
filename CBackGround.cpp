#include "pch.h"
#include "CBackGround.h"

#include "CAssetMgr.h"
#include "CTexture.h"


CBackGround::CBackGround()
	:m_Texture(nullptr)
{
	m_Texture = CAssetMgr::GetInst()->LoadTexture(L"Stage0", L"texture\\Stage0.png");
}

void CBackGround::begin()
{
}

void CBackGround::tick(float _DT)
{
	Super::tick(_DT);
}

void CBackGround::render(HDC _dc)
{
	Vec2 vRenderPos = GetRenderPos();
	Vec2 vScale = GetScale();

	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;

	blend.SourceConstantAlpha = 255; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 0

	AlphaBlend(_dc
		, int(vRenderPos.x - m_Texture->GetWidth() / 2.f)
		, int(vRenderPos.y - m_Texture->GetHeight() / 2.f)
		, m_Texture->GetWidth()
		, m_Texture->GetHeight()
		, m_Texture->GetDC()
		, 0, 0
		, m_Texture->GetWidth()
		, m_Texture->GetHeight()
		, blend);

	Super::render(_dc);
}



CBackGround::~CBackGround()
{
}
