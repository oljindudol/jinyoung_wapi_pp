#include "pch.h"
#include "CEngine.h"


#include "CPlayer.h"
#include "CMonster.h"

#include "CTimeManager.h"
#include "CKeyMgr.h"
#include "CAssetMgr.h"
#include "CLevelMgr.h"
#include "CPathMgr.h"
#include "CTaskMgr.h"
#include "CCamera.h"
#include "CCollisionMgr.h"
#include "CGCMgr.h"
#include "CLogMgr.h"
#include "CCamera.h"
#include "CUIMgr.h"
#include "CSoundMgr.h"

#include "CSkillMgr.h"
#include "CMonsterMgr.h"
#include "CThreadPoolMgr.h"
#include "CDecodeThreadPool.h"

#include "CTexture.h"

//레벨을 알고있어야 delete소멸자호출가능
#include "CLevel.h"
#include "chrono"

#include <iostream>
using namespace std;
using namespace std::chrono;




#define MEASURE_PERFORMANCE(func)                                      \
    {                                                                                    \
        auto start = std::chrono::high_resolution_clock::now();                         \
        func;                                                                            \
        auto end = std::chrono::high_resolution_clock::now();                           \
        std::chrono::duration<double> duration = end - start;                           \
        std::cout << std::fixed << std::setprecision(1);                                \
        std::cout << #func << " took " << duration.count() << " s" << std::endl;        \
    }


CEngine::CEngine()
	: m_hWnd(nullptr)
	, m_ptResolution{}
	, m_dc(nullptr)
	, m_bDebugRender(false)
	, m_arrPen{}
	, m_SubTex(nullptr)
	, m_arrFont{}
	, m_TmpTex(nullptr)
{
}

CEngine::~CEngine()
{
	// DC 해제
	ReleaseDC(m_hWnd, m_dc);


	////우리가만든 dc는 deletedc로 지워야한다
	//DeleteObject(m_subbitmap);
	//DeleteDC(m_subdc);

	// 레벨 해제
	//if (nullptr != m_Level)
	//	delete m_Level;
	for (UINT i = 0; i < PEN_END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}

}
void CEngine::CreateDefaultGDI()
{

	m_arrPen[BK_PEN] = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	m_arrPen[WT_PEN] = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	m_arrPen[YELLOW_PEN] = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
	m_arrPen[RED_PEN] = CreatePen(PS_SOLID, 1, RGB(255, 20, 20));
	m_arrPen[GREEN_PEN] = CreatePen(PS_SOLID, 1, RGB(20, 255, 20));
	m_arrPen[BLUE_PEN] = CreatePen(PS_SOLID, 1, RGB(20, 20, 255));



	SetBkMode(m_SubTex->GetDC(), TRANSPARENT);

	m_arrFont[STATUS_BAR_POINT] = CreateFont(10, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("궁서"));
	m_arrFont[LOG_TEXT] = (HFONT)SelectObject(m_SubTex->GetDC(), m_arrFont[STATUS_BAR_POINT]);
	m_arrFont[UPPER_BAR_PERCENT] = CreateFont(8, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("궁서"));
	m_arrFont[STATUS_BAR_NAME] = CreateFont(11, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("돋움"));
	m_arrFont[QUEST_DIALOG] = CreateFont(13, 0, 0, 0, 600, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("돋움"));
	m_arrFont[LEVEL_ALERT] = CreateFont(15, 0, 0, 0, 600, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("돋움"));
	m_arrFont[ACHIVEMENT] = CreateFont(15, 0, 0, 0, 600, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("돋움"));
	m_arrFont[END_ROLL] = CreateFont(30, 0, 0, 0, 700, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("돋움"));

	wstring conpath = CPathMgr::GetContentPath();
	int a = AddFontResourceW((conpath + L"D2Coding.ttf").c_str());
	m_arrFont[STATUS_DEBUG] = CreateFont(18, 0, 0, 0, 600, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("D2Coding"));
	m_arrFont[DEBUG_MENU] = CreateFont(18, 0, 0, 0, 600, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("돋움"));


}

void CEngine::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;

	ChangeWindowSize(_ptResolution, false);

	//m_ptResolution = _ptResolution;

	//// 해상도 변경
	//SetWindowPos(m_hWnd, nullptr, 20, 10, m_ptResolution.x, m_ptResolution.y, 0);
	ShowWindow(m_hWnd, true);

	// DC : Device Context
	// pen : Black 
	// brush : White
	// Bitmap(그림 그릴 곳) : 핸들에 해당하는 윈도우 비트맵
	m_dc = GetDC(m_hWnd);


	// 추가 비트맵 버퍼
	m_SubTex = CAssetMgr::GetInst()->CreateTexture(L"SubTex", m_ptResolution.x, m_ptResolution.y);

	// 추가 비트맵 버퍼
	m_TmpTex = CAssetMgr::GetInst()->CreateTexture(L"TmpTex", m_ptResolution.x, m_ptResolution.y);



	//m_subbitmap= CreateCompatibleBitmap(m_dc, m_ptResolution.x, m_ptResolution.y);
	//m_subdc = CreateCompatibleDC(m_dc);
	// 
	//m_subdc가 msubbitmap을 저장하고 원래 목적지로 갖고잇던BitMap 이 반환값으로 나오는데, 
	// 이걸 바로 DeleteObject 함수에 전달시켜서 삭제요청한다.
	//DeleteObject((HBITMAP)SelectObject(m_subdc, m_subbitmap));

	// Manager 초기화
	CAssetMgr::GetInst()->init();
	MEASURE_PERFORMANCE(CThreadPoolMgr::GetInst()->init());
	MEASURE_PERFORMANCE(CDecodeThreadPool::GetInst()->Init());
	MEASURE_PERFORMANCE(CTimeManager::GetInst()->init());
	MEASURE_PERFORMANCE(CKeyMgr::GetInst()->init());
	MEASURE_PERFORMANCE(CPathMgr::init());
	MEASURE_PERFORMANCE(CSoundMgr::GetInst()->init());
	MEASURE_PERFORMANCE(CCollisionMgr::GetInst()->init());
	MEASURE_PERFORMANCE(CSkillMgr::GetInst()->init());
	//UI매니저가 스킬매니저를 참조한다.
	MEASURE_PERFORMANCE(CUIMgr::GetInst()->init());
	MEASURE_PERFORMANCE(CMonsterMgr::GetInst()->init());
	//레벨매니저가 위에있는 것을 참조한다.(UI 등)
	MEASURE_PERFORMANCE(CLevelMgr::GetInst()->init());
	//CAssetMgr::GetInst()->PrintAllTextures();
	CAssetMgr::GetInst()->PrintTextureMemoryUsage();


	//레벨매니저로 이동
	//// Level 생성
	//m_Level = new CLevel;

	//CPlayer* pPlayer = new CPlayer;

	//pPlayer->SetPos(Vec2(200.f, 500.f));
	//pPlayer->SetScale(Vec2(50.f, 50.f));

	//m_Level->AddObject(pPlayer);

	//CMonster* pMonster = new CMonster;

	//pMonster->SetPos(Vec2(600.f, 500.f));
	//pMonster->SetScale(Vec2(50.f, 50.f));

	//m_Level->AddObject(pMonster);

	// Default GDI Object 생성
	CreateDefaultGDI();

}

//tick() 1회 ==>1프레임
//FPS(Frame Per Second
void CEngine::tick()
{
	// TimeMgr
	CTimeManager::GetInst()->tick();
	CKeyMgr::GetInst()->tick();
	CCamera::GetInst()->tick();



	//m_Level->tick();
	//m_Level->render(m_dc);
	//Rectangle(m_dc, 0, 0, m_ptResolution.x, m_ptResolution.y);

	if (KEY_TAP(KEY::L))
	{
		m_bDebugRender ? m_bDebugRender = false : m_bDebugRender = true;
	}


	CMonsterMgr::GetInst()->tick();

	// LevelMgr
	CLevelMgr::GetInst()->tick();


	CCollisionMgr::GetInst()->tick();

	CUIMgr::GetInst()->tick();
	CSkillMgr::GetInst()->tick();
	CSoundMgr::GetInst()->tick();
	CLevelMgr::GetInst()->render(m_SubTex->GetDC());

	// Camera render
	CCamera::GetInst()->render(m_SubTex->GetDC());

	// m_SubDC -> m_DC 로 비트맵 복사
	BitBlt(CEngine::GetInst()->GetMainDC()
		, 0, 0
		, m_ptResolution.x, m_ptResolution.y
		, m_SubTex->GetDC()
		, 0, 0, SRCCOPY);





	// Task Execute
	CTaskMgr::GetInst()->tick();
	// CG
	CGCMgr::GetInst()->tick();

	/*static int Call = 0;
	++Call;
	int CurCount = 0;
	static int PrevCount = GetTickCount();


	CurCount = GetTickCount();


	if (1000 < (CurCount - PrevCount))
	{
		Call = 0;
		PrevCount = CurCount;
	}*/

}

HDC CEngine::GetTmpDc()
{
	return m_TmpTex->GetDC();
}

void CEngine::ChangeWindowSize(POINT _ptResolution, bool _bMenu)
{
	m_ptResolution = _ptResolution;

	RECT rt = { 0, 0, _ptResolution.x, _ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);
	SetWindowPos(m_hWnd, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);
}