// jinyoung_client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "jinyoung_client.h"
#include "CEngine.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst=0;                                // 현재 인스턴스입니다.
//MAX_LOADSTRING= 100;
//WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
//WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWnd = 0;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // 안쓰는 인자라고 알려주는 것. 첫두줄은 실제로는 아무것도 하지않는다.
    // 옛날 인터페이스에서는 부터 내려와 지금은 필요없게된인자이다.
    //UNREFERENCED_PARAMETER(hPrevInstance);
    //UNREFERENCED_PARAMETER(lpCmdLine);
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(77738);

    // 전역 문자열을 초기화합니다. //MAX_LOADSTRING= 100;
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    //LoadStringW(hInstance, IDC_JINYOUNGCLIENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
    CEngine::GetInst()->init(g_hWnd, POINT{ 1366 , 768 });


    //단축키 테이블 참조
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_JINYOUNGCLIENT));

    MSG msg;


    //GetMessage 함수는 메세지큐에 WM_QUIT 메세지가 들어있으면 false 를 반환한다.
    // GetMessage 함수는 메세지큐에서 가져온 메세지가 WM_QUIT 이 아닌면 언제나 true 를 반환
    // getmessage 함수는 메세지가 없어도 함수가 종료되지않음
    // 메세지가 있으면 메세지를 큐에서 메세지 구조체에 이동를함.
    // 
    // peekmessage 함수는 메세지큐에 메세지가 있으면 true를 반환
    // peekmessage 함수는 메세지큐에 메세지가 없으면 false 를 반환.
    // peekmessage 함수는 메세지가 없으면 함수가 종료됨.
    // 메세지가 있으면 메세지를 큐에서 메세지 구조체에 복사를함.
    // 
    // 기본 메시지 루프입니다:

    

    while (true)
    {
        //싱글톤 패턴1. 항상 같은 객체리턴(처음만들어진)
        //CEngine* cep= CEngine::GetInst();
        //싱글톤 패턴2. 외부에서 생성불가.
        //CEngine a;
        //new CEngine;

        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {

            if (WM_QUIT == msg.message)
            {
                break;
            }
            //if (WM_LBUTTONDOWN == msg.message)
            //{
            //    int a = 0;
            //}

         //단축키 조합이 눌렸는지 확인
         if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
         {
             //메세지 처리
             TranslateMessage(&msg);
             DispatchMessage(&msg);
         }

        }
        //메세지가 없었다.(대부분의 시간)
        else 
        {
            CEngine::GetInst()->tick();
        }
    }
    //KillTimer(g_hWnd,TimerID);
    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_JINYOUNGCLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    //wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH+1);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    //메뉴바
    wcex.lpszMenuName = nullptr; //MAKEINTRESOURCEW(IDC_JINYOUNGCLIENT); 
    wcex.lpszClassName = L"MyWindow";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   //윈도우 생성 후 핸들값 반환(전역변수)
   g_hWnd = CreateWindowW(L"MyWindow", L"MyGame", WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, false);
   UpdateWindow(g_hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
//bool g_bLBtn = false;
//POINT g_point;
//POINT g_playerpos = {500,500};
//POINT g_monstpos = { 100,500 };


INT_PTR CALLBACK CreateTileProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {


    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            INT_PTR ReturnValue = 0;
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;

            case ID_MENU_COUNT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_TILECOUNT), hWnd, CreateTileProc);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_MOUSEWHEEL:
        if ((SHORT)HIWORD(wParam) > 0)
            CLevelMgr::GetInst()->imagUp();
        if ((SHORT)HIWORD(wParam) < 0)
            CLevelMgr::GetInst()->imagDown();

    break;

    case WM_SYSKEYDOWN:
    case WM_KEYDOWN://alt키막기
        switch (wParam)
        {
        case VK_MENU:
            break;
        }
        break;


        //lParam :마우스 좌표값
    //case WM_LBUTTONDOWN:
    //{
    //    g_bLBtn = true;
    //    //마우스의 x좌표를 검출
    //    g_point.x = LOWORD(lParam);
    //    //마우스의 y좌표를 검출
    //    g_point.y = HIWORD(lParam);
    //    //강제 WM_PAINT메세지발생
    //    InvalidateRect(hWnd, nullptr, false);
    //}
    //    break;
    //    //wParam : 눌린 키값.
    //case WM_KEYDOWN:
    //{
    //    switch (wParam)
    //    {
    //    case 'w':
    //        ++g_playerpos.y;
    //        break;
    //    case 's':
    //        --g_playerpos.y;
    //        break;
    //    case 'a':
    //        ++g_playerpos.x;
    //        break;
    //    case 'd':
    //        --g_playerpos.x;
    //        break;

    //    default:
    //        break;
    //    }
    //    InvalidateRect(hWnd, nullptr, false);

    //}
    //    break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            /*if (g_bLBtn)
            {
                Ellipse(hdc, g_point.x - 50, g_point.y - 50, g_point.x + 50, g_point.y + 50);

                Rectangle(hdc, g_playerpos.x - 20, g_playerpos.y - 20, g_playerpos.x + 20, g_playerpos.y + 20);
                Rectangle(hdc, g_monstpos.x - 20, g_monstpos.y - 20, g_monstpos.x + 20, g_monstpos.y + 20);
            }*/
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        //InvalidateRect(hWnd, nullptr, false);
    }
    return 0;
}



// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
