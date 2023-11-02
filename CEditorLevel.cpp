#include "pch.h"
#include "CEditorLevel.h"

#include "CLevelMgr.h"

#include "CKeyMgr.h"

#include "CEngine.h"
#include "CCamera.h"

#include "Resource.h"

#include "CTile.h"
#include "CPanelUI.h"
#include "CBtnUI.h"

void TestFunc();
INT_PTR CALLBACK CreateTileProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void CEditorLevel::init()
{
}


void CEditorLevel::enter()
{
	// 메뉴바 생성
// 리소스 아이디로 메뉴를 골라서 생성
	//HMENU hMenu = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_CLIENT));
	//HMENU hMenu = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_JINYOUNGCLIENT));

	// 메인 윈도우에 생성시킨 메뉴를 붙이기
	//SetMenu(CEngine::GetInst()->GetMainWind(), hMenu);

	// 메뉴가 추가되었기 때문에 윈도우 크기를 재조정
	//POINT ptResSol = CEngine::GetInst()->GetResolution();
	//CEngine::GetInst()->ChangeWindowSize(ptResSol, true);

	// 카메라 설정
	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;
	CCamera::GetInst()->SetLookAt(vLookAt);

	// 타일 생성
	CreateTile(10, 10);

	// UI 생성
	CPanelUI* pPanelUI = new CPanelUI;
	pPanelUI->SetScale(Vec2(500.f, 400.f));
	pPanelUI->SetPos(Vec2(800.f, 200.f));

	CBtnUI* pBtnUI = new CBtnUI;
	pBtnUI->SetScale(Vec2(200.f, 80.f));
	pBtnUI->SetPos(Vec2(10.f, 10.f));
	//pBtnUI->SetCallBack(TestFunc);
	pBtnUI->SetDeletage(this, (DelegateFunc)&CEditorLevel::OpenTileCreateWindow);

	pPanelUI->AddChildUI(pBtnUI);
	AddObject(LAYER::UI, pPanelUI);


	/*pPanelUI = pPanelUI->Clone();
	pPanelUI->SetPos(Vec2(500.f, 200.f));
	AddObject(LAYER::UI, pPanelUI);*/
}

void CEditorLevel::exit()
{
	DeleteAllObjects();

	// 메뉴바 제거
// 현재 윈도우에 붙어있는 메뉴의 핸들(아이디) 를 알아낸다.
	HMENU hMenu = GetMenu(CEngine::GetInst()->GetMainWind());

	// 메인 윈도우에 부착되어있는 메뉴를 떼어낸다.
	SetMenu(CEngine::GetInst()->GetMainWind(), nullptr);

	// 메뉴를 메모리 해제시킨다.
	DestroyMenu(hMenu);

	// 메뉴가 윈도우에서 떨어졌으니, 윈도우 크기를 다시 설정해준다.
	POINT ptResSol = CEngine::GetInst()->GetResolution();
	CEngine::GetInst()->ChangeWindowSize(ptResSol, false);
}

void CEditorLevel::tick()
{
	CLevel::tick();

	// Enter 키가 눌리면 StartLevel 로 변환
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::PLAY_LEVEL);
	}

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		int col = (int)vMousePos.x / TILE_SIZE;
		int row = (int)vMousePos.y / TILE_SIZE;
		int idx = GetTileCol() * row + col;

		if (!((int)GetTileCol() <= col) && !((int)GetTileRow() <= row)
			&& !(vMousePos.x < 0.f) && !(vMousePos.y < 0.f))
		{
			const vector<CObj*>& vecTiles = GetLayer(LAYER::TILE)->GetObjects();
			CTile* pTargetTile = dynamic_cast<CTile*>(vecTiles[idx]);
			pTargetTile->AddImgIdx();
		}
	}
}

void CEditorLevel::OpenTileCreateWindow()
{
	DialogBox(nullptr, MAKEINTRESOURCE(IDD_TILECOUNT), CEngine::GetInst()->GetMainWind(), CreateTileProc);
}


// ==============================
// CreateTile Dialog 프로시저 함수
// ==============================
INT_PTR CALLBACK CreateTileProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			// IDC_COL, IDC_ROW 에디트 컨트롤에 입력한 숫자를 알아내서
			// EditorLevel 의 타일을 해당 수치에 맞게 생성시킨다.
			int Col = GetDlgItemInt(hDlg, IDC_COL, nullptr, true);
			int Row = GetDlgItemInt(hDlg, IDC_ROW, nullptr, true);

			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
			CEditorLevel* pEditorLevel = dynamic_cast<CEditorLevel*>(pCurLevel);

			if (nullptr != pEditorLevel)
			{
				pEditorLevel->CreateTile(Row, Col);
			}

			// 다이얼로그 윈도우 종료
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			// 다이얼로그 윈도우 종료
			EndDialog(hDlg, LOWORD(wParam));
		}
		break;
	}
	return (INT_PTR)FALSE;
}

