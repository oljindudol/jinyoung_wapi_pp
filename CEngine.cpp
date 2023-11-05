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

#include "CTexture.h"

//레벨을 알고있어야 delete소멸자호출가능
#include "CLevel.h"

CEngine::CEngine()
	: m_hWnd(nullptr)
	, m_ptResolution{}
	, m_dc(nullptr)
	, m_bDebugRender(true)
	, m_arrPen{}
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
	m_arrPen[RED_PEN] = CreatePen(PS_SOLID, 1, RGB(255, 20, 20));
	m_arrPen[GREEN_PEN] = CreatePen(PS_SOLID, 1, RGB(20, 255, 20));
	m_arrPen[BLUE_PEN] = CreatePen(PS_SOLID, 1, RGB(20, 20, 255));
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

	//m_subbitmap= CreateCompatibleBitmap(m_dc, m_ptResolution.x, m_ptResolution.y);
	//m_subdc = CreateCompatibleDC(m_dc);
	// 
	//m_subdc가 msubbitmap을 저장하고 원래 목적지로 갖고잇던BitMap 이 반환값으로 나오는데, 
	// 이걸 바로 DeleteObject 함수에 전달시켜서 삭제요청한다.
	//DeleteObject((HBITMAP)SelectObject(m_subdc, m_subbitmap));

	// Manager 초기화
	CTimeManager::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CPathMgr::init();
	CSoundMgr::GetInst()->init();

	CLevelMgr::GetInst()->init();

	//레벨매니저보다 나중에호출해야 먼저 소멸된다.
	CSkillMgr::GetInst()->init();
	CMonsterMgr::GetInst()->init();

	//레벨매니저로 이관
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

	if (KEY_TAP(KEY::NUM8))
	{
		m_bDebugRender ? m_bDebugRender = false : m_bDebugRender = true;
	}

	// LevelMgr
	CLevelMgr::GetInst()->tick();

	CCollisionMgr::GetInst()->tick();
	CUIMgr::GetInst()->tick();

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

void CEngine::ChangeWindowSize(POINT _ptResolution, bool _bMenu)
{
	m_ptResolution = _ptResolution;

	RECT rt = { 0, 0, _ptResolution.x, _ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);
	SetWindowPos(m_hWnd, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);
}