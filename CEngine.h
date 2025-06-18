#pragma once
#include "pch.h"
class CLevel;
class CTexture;

void AttachConsoleAndRedirect();
void DetachConsoleAndCleanup();
//엔진은 게임프로그램의 관리자.
//디자인패턴(설계의 유형)
//Singleton 패턴 단 하나의 객체를 위해설계됨
//두개이상 만들어지는것을 금지함
class CEngine
{

	//정적 멤버변수
	//-데이터 영역(생성된 객체안에 포함이 안됨,1개) == 모든객체들이 공유하는 하나의 변수
	//  
	//-멤버변수의 특징(멤버함수에서 접근가능) this 없이도 접근가능
	//- 정적멤버함수에서도 접근가능하다.
	// 문법:클래스안에 있는 선언은 전방선언역할
	// 실제 초기화는 cpp에서 해줘야한다.

	SINGLETON(CEngine);

private:
	HWND		m_hWnd;			// 메인 윈도우 핸들
	POINT		m_ptResolution;	// 윈도우 해상도

	HDC			m_dc;
	//HDC			m_subdc;
	//HBITMAP		m_subbitmap;
	CTexture* m_SubTex;
	CTexture* m_TmpTex;

	bool	m_bDebugRender;
	HPEN	m_arrPen[PEN_END];
	HFONT	m_arrFont[FONT_END];

public:
	HDC GetTmpDc();
	CTexture* GetTmpTex() { return m_TmpTex; }
	HWND GetMainWind() { return m_hWnd; }
	HDC GetMainDC() { return m_dc; }
	POINT GetResolution() { return m_ptResolution; }

	HPEN GetPen(PEN_TYPE _type) { return m_arrPen[_type]; }
	HFONT GetFont(FONT_TYPE _type) { return m_arrFont[_type]; }

	bool DebugRender() { return m_bDebugRender; }
	void ChangeWindowSize(POINT _ptResolution, bool _bMenu);

private:
	void CreateDefaultGDI();

public:
	void init(HWND _hWnd, POINT _ptResolution);
	void tick();
	//정적멤버함수
	//객체가 없어도 됨(객체에 상대적이지않음)
	//this가없음
	//static CEngine* GetInst()
	//{

	//	//static 정적변수 은 함수의 호출종료 상관없이 유지되는변수
	//	//초기화는 한번만된다.
	//	if (nullptr==pEngine)
	//	{
	//		pEngine = new CEngine;
	//	}
	//	return pEngine;
	//}

	//static void Destroy()
	//{
	//	delete pEngine;
	//	pEngine = nullptr;
	//}

	//장점 : 데이터영역에 있으므로 destroy가필요없다.
	//단점 : runtime 도중에 지울 수 없다. (여러개 매니저가 쌓여있을 수 있음)


};