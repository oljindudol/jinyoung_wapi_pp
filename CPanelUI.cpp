#include "pch.h"
#include "CPanelUI.h"

#include "CKeyMgr.h"
#include "CTexture.h"

CPanelUI::CPanelUI()
	:m_PanmalImg(nullptr)
{
}

CPanelUI::~CPanelUI()
{
}

void CPanelUI::tick(float _DT)
{
	if (IsLBtnDown())
	{
		Vec2 vDiff = m_vLbtnDownPos - CKeyMgr::GetInst()->GetMousePos();
		Vec2 vPos = GetPos();
		vPos -= vDiff;
		SetPos(vPos);

		m_vLbtnDownPos = CKeyMgr::GetInst()->GetMousePos();
	}

	Super::tick(_DT);
}

void CPanelUI::render(HDC _dc)
{
	//(*this);
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	if (nullptr != m_PanmalImg)
	{
		BLENDFUNCTION blend = {};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;

		blend.SourceConstantAlpha = 255; // 0 ~ 255
		blend.AlphaFormat = AC_SRC_ALPHA; // 0

		AlphaBlend(_dc
			, (int)vPos.x, (int)vPos.y
			, m_PanmalImg->GetWidth(), m_PanmalImg->GetHeight()
			, m_PanmalImg->GetDC()
			, 0, 0
			, m_PanmalImg->GetWidth(), m_PanmalImg->GetHeight()
			, blend);
	}
	else
	{
		SELECT_PEN(_dc, RED_PEN);
		Rectangle(_dc
			, (int)(vPos.x)
			, (int)(vPos.y)
			, (int)(vPos.x + vScale.x)
			, (int)(vPos.y + vScale.y));
	}


	Super::render(_dc);
}
void CPanelUI::LBtnDown(Vec2 _MousePos)
{
	// 마우스 왼쪽 버튼이 눌렸을 때 마우스의 위치를 기록
	m_vLbtnDownPos = _MousePos;
}
