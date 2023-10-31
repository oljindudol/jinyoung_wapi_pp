#include "pch.h"
#include "CEditorLevel.h"

#include "CLevelMgr.h"

#include "CKeyman.h"

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
	// �޴��� ����
// ���ҽ� ���̵�� �޴��� ��� ����
	//HMENU hMenu = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_CLIENT));
	HMENU hMenu = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_JINYOUNGCLIENT));

	// ���� �����쿡 ������Ų �޴��� ���̱�
	SetMenu(CEngine::GetInst()->GetMainWind(), hMenu);

	// �޴��� �߰��Ǿ��� ������ ������ ũ�⸦ ������
	POINT ptResSol = CEngine::GetInst()->GetResolution();
	CEngine::GetInst()->ChangeWindowSize(ptResSol, true);

	// ī�޶� ����
	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;
	CCamera::GetInst()->SetLookAt(vLookAt);

	// Ÿ�� ����
	CreateTile(10, 10);

	// UI ����
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

	// �޴��� ����
// ���� �����쿡 �پ��ִ� �޴��� �ڵ�(���̵�) �� �˾Ƴ���.
	HMENU hMenu = GetMenu(CEngine::GetInst()->GetMainWind());

	// ���� �����쿡 �����Ǿ��ִ� �޴��� �����.
	SetMenu(CEngine::GetInst()->GetMainWind(), nullptr);

	// �޴��� �޸� ������Ų��.
	DestroyMenu(hMenu);

	// �޴��� �����쿡�� ����������, ������ ũ�⸦ �ٽ� �������ش�.
	POINT ptResSol = CEngine::GetInst()->GetResolution();
	CEngine::GetInst()->ChangeWindowSize(ptResSol, false);
}

void CEditorLevel::tick()
{
	CLevel::tick();

	// Enter Ű�� ������ StartLevel �� ��ȯ
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::PLAY_LEVEL);
	}

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = CKeyman::GetInst()->GetMousePos();
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
// CreateTile Dialog ���ν��� �Լ�
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
			// IDC_COL, IDC_ROW ����Ʈ ��Ʈ�ѿ� �Է��� ���ڸ� �˾Ƴ���
			// EditorLevel �� Ÿ���� �ش� ��ġ�� �°� ������Ų��.
			int Col = GetDlgItemInt(hDlg, IDC_COL, nullptr, true);
			int Row = GetDlgItemInt(hDlg, IDC_ROW, nullptr, true);

			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
			CEditorLevel* pEditorLevel = dynamic_cast<CEditorLevel*>(pCurLevel);

			if (nullptr != pEditorLevel)
			{
				pEditorLevel->CreateTile(Row, Col);
			}

			// ���̾�α� ������ ����
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			// ���̾�α� ������ ����
			EndDialog(hDlg, LOWORD(wParam));
		}
		break;
	}
	return (INT_PTR)FALSE;
}

