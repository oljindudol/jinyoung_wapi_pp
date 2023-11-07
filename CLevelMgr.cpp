#include "pch.h"
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


CLevelMgr::CLevelMgr()
	: m_pCurLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
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
	// 모든 레벨 생성
	m_arrLevels[(UINT)LEVEL_TYPE::START_LEVEL] = new CStartLevel;
	m_arrLevels[(UINT)LEVEL_TYPE::PLAY_LEVEL] = new CEnteranceLevel;
	m_arrLevels[(UINT)LEVEL_TYPE::EDITOR_LEVEL] = new CEditorLevel;

	// 레벨 초기화
	for (UINT i = 0; i < (UINT)LEVEL_TYPE::END; ++i)
	{
		m_arrLevels[i]->init();
	}

	// Level
	GoStartLevel(LEVEL_TYPE::PLAY_LEVEL);

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
	SelectObject(_dc, CPal::GetInst()->getHPen(WHITE));
	SelectObject(_dc, CPal::GetInst()->getHBrush(WHITE));
	Rectangle(_dc, -1, -1, ptResolution.x + 1, ptResolution.y + 1);

	// 레벨 render
	m_pCurLevel->render(_dc);

	// Log
	CLogMgr::GetInst()->tick(_dc);

	// m_SubDC -> m_DC 로 비트맵 복사
	//BitBlt(CEngine::GetInst()->GetMainDC(), 0, 0, ptResolution.x, ptResolution.y, _dc, 0, 0, SRCCOPY);

}


CPlayer* CLevelMgr::GetCurLevelPlayer()
{
	return m_pCurLevel->GetPlayer();
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

void CLevelMgr::GoStartLevel(LEVEL_TYPE _Type)
{
	if (m_pCurLevel == m_arrLevels[(UINT)_Type])
		return;

	if (nullptr != m_pCurLevel)
		m_pCurLevel->exit();

	m_pCurLevel = m_arrLevels[(UINT)_Type];

	m_pCurLevel->begin();
}