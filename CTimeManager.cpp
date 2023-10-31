#include "pch.h"
#include "CTimeManager.h"

#include "CEngine.h"

// 제일 큰 자료형 기준으로 같은 공간을 지칭하는 DataType 선언 방식
//union MousePos
//{
//	struct
//	{
//		short High;
//		short Low;
//	};
//
//	UINT value;
//};


CTimeManager::CTimeManager()
	: m_Frequency{}
	, m_PrevCount{}
	, m_CurCount{}
	, m_fTime(0.f)
{

}


CTimeManager::~CTimeManager()
{
}

void CTimeManager::init()
{
	// 초당 빈도
	QueryPerformanceFrequency(&m_Frequency);

	QueryPerformanceCounter(&m_PrevCount);
}



void CTimeManager::tick()
{
	//초당 빈도
	QueryPerformanceCounter(&m_CurCount);

	m_DeltaTime= float(m_CurCount.QuadPart - m_PrevCount.QuadPart)/float(m_Frequency.QuadPart);

	m_PrevCount = m_CurCount;

	// DT 보정
	if ((1.f / 60.f) < m_DeltaTime)
		m_DeltaTime = (1.f / 60.f);


	// 시간 누적 ==> 1초마다 if 구문 실행
	m_fTime += m_DeltaTime;
	if (1.f <= m_fTime)
	{
		wchar_t szText[50] = {};
		swprintf_s(szText, 50, L"DeltaTime : %f, FPS : %d", m_DeltaTime, m_iCall);
		SetWindowText(CEngine::GetInst()->GetMainWind(), szText);

		m_iCall = 0;
		m_fTime = 0.f;
	}

	++m_iCall;

}