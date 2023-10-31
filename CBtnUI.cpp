#include "pch.h"
#include "CBtnUI.h"

#include "CEngine.h"
#include "Resource.h"

#include "CKeyman.h"

CBtnUI::CBtnUI()
	: m_NormalImg(nullptr)
	, m_HoverImg(nullptr)
	, m_PressedImg(nullptr)
	, m_CurImg(nullptr)
	, m_CallBackFunc(nullptr)
	, m_Inst(nullptr)
	, m_Delegate(nullptr)
{
}

CBtnUI::~CBtnUI()
{
}

void CBtnUI::tick(float _DT)
{
	//if (IsLBtnDown())
	//{
	//	Vec2 vDiff = m_vLbtnDownPos - CKeyman::GetInst()->GetMousePos();
	//	Vec2 vPos = GetPos();
	//	vPos -= vDiff;
	//	SetPos(vPos);

	//	m_vLbtnDownPos = CKeyman::GetInst()->GetMousePos();
	//}
	Super::tick(_DT);
}

void CBtnUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();
	//Rectangle(_dc, vPos.x, vPos.y, vPos.x + vScale.x, vPos.y + vScale.y);

	if (nullptr != m_CurImg)
	{

	}
	else
	{
		Rectangle(_dc
			, (int)(vPos.x)
			, (int)(vPos.y)
			, (int)(vPos.x + vScale.x)
			, (int)(vPos.y + vScale.y));
	}


	// �θ�Ŭ����(CUI) �����Լ� ȣ��(�ڽ� UI ������ render �� ȣ���Ѵ�)
	Super::render(_dc);


}

void CBtnUI::OnHovered(Vec2 _vMousePos)
{
	m_CurImg = m_HoverImg;
}

void CBtnUI::MouseOn(Vec2 _vMousePos)
{

}

void CBtnUI::OnUnHovered(Vec2 _vMousePos)
{
	m_CurImg = m_NormalImg;
}


void CBtnUI::LBtnDown(Vec2 _vMousePos)
{
	m_CurImg = m_PressedImg;

}

void CBtnUI::LBtnUp(Vec2 _vMousePos)
{
	m_CurImg = m_NormalImg;
}

INT_PTR CALLBACK CreateTileProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void CBtnUI::LBtnClicked(Vec2 _vMousePos)
{
	if (nullptr != m_CallBackFunc)
	{
		m_CallBackFunc();
	}

	if (nullptr != m_Inst && nullptr != m_Delegate)
	{
		(m_Inst->*m_Delegate)();
	}
	//DialogBox(nullptr, MAKEINTRESOURCE(IDD_TILECOUNT), CEngine::GetInst()->GetMainWind(), CreateTileProc);
}