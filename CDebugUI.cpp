#include "pch.h"
#include "CDebugUI.h"


#include "CLevelMgr.h"
#include "CBlackMage2.h"
#include "CState.h"
#include "CAssetMgr.h"
#include "CEngine.h"

CDebugUI::CDebugUI()
{
	m_uiname = L"debugui";
	m_UItex = CAssetMgr::GetInst()->LoadTexture(L"debuguitex", L"texture\\debugmenu.png");
	SetScale(Vec2(830, 650));
	SetPos(Vec2(268, 60));

}

void CDebugUI::tick(float _DT)
{
	Super::tick(_DT);
}

void CDebugUI::render(HDC _dc)
{
	Vec2 pos = GetFinalPos();

	SettexturetoDcWithAlpha(_dc, m_UItex, pos, 220);

	int  accx = 50;
	int  accy = 50;

	int offy1 = 35;

	SetBkMode(_dc, TRANSPARENT);
	SELECT_FONT(_dc, FONT_TYPE::DEBUG_MENU);
	SetTextColor(_dc, RGB(255, 255, 255));
	


	wstring tmptext = L"TAB ����� �޴�";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());

	accy += offy1;
	accy += offy1;
	int x3 = 540;
	int y3 = -40;

	tmptext = L"KEY_1    ���� ��ȯ";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	tmptext = L"L        ����׷���";
	TextOut(_dc, (int)pos.x + x3, (int)pos.y + accy+ y3, tmptext.c_str(), (int)tmptext.length());
	accy += offy1;

	tmptext = L"KEY_2    ���� ����IDLE";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	tmptext = L"M        ���µ����";
	TextOut(_dc, (int)pos.x + x3, (int)pos.y + accy + y3, tmptext.c_str(), (int)tmptext.length());
	accy += offy1;

	tmptext = L"KEY_3    ����IDLE ����";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	tmptext = L"ENTER  ������������ȯ";
	TextOut(_dc, (int)pos.x + x3, (int)pos.y + accy + y3, tmptext.c_str(), (int)tmptext.length());
	accy += offy1;

	tmptext = L"KEY_4    DEBUG ���� ����";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	tmptext = L"V        �ش緹�������ı�";
	TextOut(_dc, (int)pos.x + x3, (int)pos.y + accy + y3, tmptext.c_str(), (int)tmptext.length());
	accy += offy1;

	tmptext = L"K        ����ON/OFF";
	TextOut(_dc, (int)pos.x + x3, (int)pos.y + accy + y3, tmptext.c_str(), (int)tmptext.length());

	int accx2 = accx + 260;
	int accx3 = accx2 + 150;

	tmptext = L"1������";
	TextOut(_dc, (int)pos.x + accx2, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	tmptext = L"2������";
	TextOut(_dc, (int)pos.x + accx3, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());

	accy += offy1;

	tmptext = L"KEY_5    ��������1";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	tmptext = L"���ֵθ���";
	TextOut(_dc, (int)pos.x + accx2, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	tmptext = L"����";
	TextOut(_dc, (int)pos.x + accx3, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	accy += offy1;


	tmptext = L"KEY_6    ��������2";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	tmptext = L"����";
	TextOut(_dc, (int)pos.x + accx2, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	tmptext = L"�ĸ��Ǵ�";
	TextOut(_dc, (int)pos.x + accx3, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	accy += offy1;

	tmptext = L"KEY_7    ��������3";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	tmptext = L"�߰ݳ������";
	TextOut(_dc, (int)pos.x + accx2, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	tmptext = L"��׽�Ÿ��";
	TextOut(_dc, (int)pos.x + accx3, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	accy += offy1;

	tmptext = L"KEY_8    ��������4";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());

	tmptext = L"�콺���Ǿ�";
	TextOut(_dc, (int)pos.x + accx3, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	accy += offy1;

	tmptext = L"KEY_9    ������1(�罽����)";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	accy += offy1;
	tmptext = L"KEY_0    ������2(��������)";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	accy += offy1;

	tmptext = L"F9       �Ǵ�����1";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	accy += offy1;
	tmptext = L"F10      �Ǵ�����2";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	accy += offy1;
	tmptext = L"F11      �Ǵ�����3";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	accy += offy1;
}

void CDebugUI::begin()
{
}

CDebugUI::~CDebugUI()
{
}
