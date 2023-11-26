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
	


	wstring tmptext = L"TAB 디버그 메뉴";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());

	accy += offy1;
	accy += offy1;
	int x3 = 540;
	int y3 = -40;

	tmptext = L"KEY_1    몬스터 소환";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	tmptext = L"L        디버그랜더";
	TextOut(_dc, (int)pos.x + x3, (int)pos.y + accy+ y3, tmptext.c_str(), (int)tmptext.length());
	accy += offy1;

	tmptext = L"KEY_2    몬스터 강제IDLE";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	tmptext = L"M        상태디버거";
	TextOut(_dc, (int)pos.x + x3, (int)pos.y + accy + y3, tmptext.c_str(), (int)tmptext.length());
	accy += offy1;

	tmptext = L"KEY_3    강제IDLE 해제";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	tmptext = L"ENTER  다음레벨로전환";
	TextOut(_dc, (int)pos.x + x3, (int)pos.y + accy + y3, tmptext.c_str(), (int)tmptext.length());
	accy += offy1;

	tmptext = L"KEY_4    DEBUG 상태 진입";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	tmptext = L"V        해당레벨몬스터파괴";
	TextOut(_dc, (int)pos.x + x3, (int)pos.y + accy + y3, tmptext.c_str(), (int)tmptext.length());
	accy += offy1;

	tmptext = L"K        무적ON/OFF";
	TextOut(_dc, (int)pos.x + x3, (int)pos.y + accy + y3, tmptext.c_str(), (int)tmptext.length());

	int accx2 = accx + 260;
	int accx3 = accx2 + 150;

	tmptext = L"1페이즈";
	TextOut(_dc, (int)pos.x + accx2, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	tmptext = L"2페이즈";
	TextOut(_dc, (int)pos.x + accx3, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());

	accy += offy1;

	tmptext = L"KEY_5    몬스터패턴1";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	tmptext = L"검휘두르기";
	TextOut(_dc, (int)pos.x + accx2, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	tmptext = L"암흑";
	TextOut(_dc, (int)pos.x + accx3, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	accy += offy1;


	tmptext = L"KEY_6    몬스터패턴2";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	tmptext = L"돌진";
	TextOut(_dc, (int)pos.x + accx2, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	tmptext = L"파멸의눈";
	TextOut(_dc, (int)pos.x + accx3, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	accy += offy1;

	tmptext = L"KEY_7    몬스터패턴3";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	tmptext = L"추격내리찍기";
	TextOut(_dc, (int)pos.x + accx2, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	tmptext = L"모닝스타폴";
	TextOut(_dc, (int)pos.x + accx3, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	accy += offy1;

	tmptext = L"KEY_8    몬스터패턴4";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());

	tmptext = L"녹스스피어";
	TextOut(_dc, (int)pos.x + accx3, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	accy += offy1;

	tmptext = L"KEY_9    맵패턴1(사슬공격)";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	accy += offy1;
	tmptext = L"KEY_0    맵패턴2(돌떨어짐)";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	accy += offy1;

	tmptext = L"F9       권능패턴1";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	accy += offy1;
	tmptext = L"F10      권능패턴2";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	accy += offy1;
	tmptext = L"F11      권능패턴3";
	TextOut(_dc, (int)pos.x + accx, (int)pos.y + accy, tmptext.c_str(), (int)tmptext.length());
	accy += offy1;
}

void CDebugUI::begin()
{
}

CDebugUI::~CDebugUI()
{
}
