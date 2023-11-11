﻿#include "pch.h"
#include "CLevelMgr.h"

#include "CEngine.h"

#include "CLevel.h"
#include "CPlayer.h"

#include "CMonster.h"
#include "CPal.h"
#include "CCamera.h"
#include "CLogMgr.h"
#include "CCollisionMgr.h"

#include "CPlatform.h"

#include "CCollisionMgr.h"
#include "CLogMgr.h"

#include "CEnteranceLevel.h"
#include "CStartLevel.h"
#include "CEditorLevel.h"
#include "CPhaseFirst.h"
#include "CTexture.h"


CLevelMgr::CLevelMgr()
	: m_pCurLevel(nullptr)
	, m_Player(nullptr)
	, m_arrLevels{}
	, imag(1)
{

}

CLevelMgr::~CLevelMgr()
{
	delete m_Player;

	for (UINT i = 0; i < (UINT)LEVEL_TYPE::END; ++i)
	{
		if (nullptr != m_arrLevels[i])
			delete m_arrLevels[i];
	}
	//if (m_pCurLevel)
	//{
	//	if (nullptr != m_pCurLevel)
	//		delete m_pCurLevel;
	//}
}

void CLevelMgr::init()
{
	//플레이어 생성
	m_Player = new CPlayer;
	m_Player->SetScale(Vec2(50.f, 50.f));


	// 모든 레벨 생성
	m_arrLevels[(UINT)LEVEL_TYPE::START_LEVEL] = new CStartLevel;
	m_arrLevels[(UINT)LEVEL_TYPE::EDITOR_LEVEL] = new CEditorLevel;
	m_arrLevels[(UINT)LEVEL_TYPE::PHASE_FIRST] = new CPhaseFirst;
	m_arrLevels[(UINT)LEVEL_TYPE::PHASE_ZERO] = new CEnteranceLevel;

	// 레벨 초기화
	//for (UINT i = 0; i < (UINT)LEVEL_TYPE::END; ++i)
	//{
	//	m_arrLevels[i]->init();
	//}

	// Level
	ChangeLevel(LEVEL_TYPE::PHASE_ZERO);

	// Level 
	//m_pCurLevel = m_arrLevels[(UINT)LEVEL_TYPE::PLAY_LEVEL];

	//// 레벨 시작
	//m_pCurLevel->begin();

	// Level 
	//m_pCurLevel = new CLevel;

	//// 플레이어 생성
	//CPlayer* pPlayer = new CPlayer;

	//pPlayer->SetPos(Vec2(500.f, 200.f));
	//pPlayer->SetScale(Vec2(50.f, 50.f));
	////m_pCurLevel->setPlayer(pPlayer);

	//m_pCurLevel->AddObject(PLAYER, pPlayer);
	////m_pCurLevel->AddObject(pPlayer);



	//// 몬스터 생성
	//CMonster* pMonster = new CMonster;

	////pMonster->SetPos(Vec2(600.f, 500.f));
	////pMonster->SetScale(Vec2(50.f, 50.f));

	////m_pCurLevel->setMonster(pMonster);
	////m_pCurLevel->AddObject(pMonster);
	////m_pCurLevel->AddObject(MONSTER, pMonster);

	//// 플랫폼 설치
	//CPlatform* pPlatform = new CPlatform;
	//pPlatform->SetPos(Vec2(800.f, 700.f));
	//m_pCurLevel->AddObject(PLATFORM, pPlatform);



	////pMonster = new CMonster;
	////pMonster->SetPos(Vec2(900.f, 500.f));
	////pMonster->SetScale(Vec2(100.f, 100.f));
	////m_pCurLevel->AddObject(pMonster);

	////pMonster = new CMonster;
	////pMonster->SetPos(Vec2(1200.f, 200.f));
	////pMonster->SetScale(Vec2(100.f, 100.f));
	////m_pCurLevel->AddObject(pMonster);

	//// dynamic_cast
	////{
	////	CObj* pObj = nullptr;
	////	pObj = new CPlayer;
	////  CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj); // RTTI(Runtime Type Information)
	//// 
	////	pObj = new CMonster;
	////	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj); // RTTI(Runtime Type Information)
	////}

	//// 카메라 설정
	//Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	//vLookAt /= 2.f;
	//CCamera::GetInst()->SetLookAt(vLookAt);

	//// 충돌 설정
	//CCollisionMgr::GetInst()->CheckCollision(MONSTER, PLAYER);
	//CCollisionMgr::GetInst()->CheckCollision(PLAYER_PJ, MONSTER);
	//CCollisionMgr::GetInst()->CheckCollision(PLAYER, PLATFORM);


}

void CLevelMgr::tick()
{
	//m_pCurLevel->tick();
	if (nullptr != m_pCurLevel)
		m_pCurLevel->tick();
}

void CLevelMgr::render(HDC _dc)
{
	if (nullptr == m_pCurLevel)
		return;
	// Level Render
	// 화면 Clear
	POINT ptResolution = CEngine::GetInst()->GetResolution();
	SelectObject(_dc, CPal::GetInst()->getHPen(BLACK));
	SelectObject(_dc, CPal::GetInst()->getHBrush(BLACK));


	HDC tmpdc = CEngine::GetInst()->GetTmpDc();
	CTexture* tmptex = CEngine::GetInst()->GetTmpTex();


	Rectangle(_dc, -1, -1, tmptex->GetWidth() + 1, tmptex->GetHeight() + 1);

	// 레벨 render
	m_pCurLevel->render(_dc);



	float mag = 1.f + (((float)imag - 1.f) / 10.f);


	if (imag != 1)
	{
		BitBlt(tmpdc
			, 0, 0
			, tmptex->GetWidth(), tmptex->GetHeight()
			, _dc
			, 0, 0, SRCCOPY);

		Rectangle(_dc, -1, -1, tmptex->GetWidth() + 1, tmptex->GetHeight() + 1);

		StretchBlt(
			_dc,
			(int)(ptResolution.x * ((mag - 1.f) / (-2.f))),
			(int)(ptResolution.y * ((mag - 1.f) / (-2.f))),
			(int)(ptResolution.x * mag),
			(int)(ptResolution.y * mag),
			tmpdc,
			(int)(ptResolution.x * ((1.f - mag) / (-2.f))),
			(int)(ptResolution.x * ((1.f - mag) / (-2.f))),
			(int)(ptResolution.x / mag),
			(int)(ptResolution.y / mag),
			SRCCOPY
		);
	}



	// Log
	CLogMgr::GetInst()->tick(_dc);

	// m_SubDC -> m_DC 로 비트맵 복사
	//BitBlt(CEngine::GetInst()->GetMainDC(), 0, 0, ptResolution.x, ptResolution.y, _dc, 0, 0, SRCCOPY);

}


Vec2 CLevelMgr::GetCurLevelCameraRangeX()
{
	return m_pCurLevel->m_CameraRangex;
}

Vec2 CLevelMgr::GetCurLevelCameraRangeY()
{
	return m_pCurLevel->m_CameraRangey;
}

Vec2 CLevelMgr::GetCurLevelMiddle()
{
	return m_pCurLevel->m_LevelMiddle;
}


void CLevelMgr::ChangeLevel(LEVEL_TYPE _Type)
{
	if (m_pCurLevel == m_arrLevels[(UINT)_Type])
		return;

	if (nullptr != m_pCurLevel)
		m_pCurLevel->exit();

	m_pCurLevel = m_arrLevels[(UINT)_Type];

	m_pCurLevel->enter();

	m_pCurLevel->begin();
}

//void CLevelMgr::GoStartLevel(LEVEL_TYPE _Type)
//{
//	if (m_pCurLevel == m_arrLevels[(UINT)_Type])
//		return;
//
//	if (nullptr != m_pCurLevel)
//		m_pCurLevel->exit();
//
//	m_pCurLevel = m_arrLevels[(UINT)_Type];
//
//	m_pCurLevel->begin();
//}