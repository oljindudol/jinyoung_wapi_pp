#include "pch.h"
#include "CPhaseSecond.h"


#include "CPlayer.h"
#include "CMonster.h"
#include "CPlatform.h"
#include "CWall.h"

#include "CEngine.h"
#include "CCamera.h"
#include "CCollisionMgr.h"

#include "CKeyMgr.h"
#include "CLevelMgr.h"

#include "CAssetMgr.h"
#include "CSound.h"

#include "CMonsterMgr.h"

#include "CBackGround.h"
#include "CLogMgr.h"

#include "CStatusUI.h"
#include "CTexture.h"

#include "CUIMgr.h"

CPhaseSecond::~CPhaseSecond()
{
}

void CPhaseSecond::init()
{

	// 배경생성
	//CBackGround* pBackGround = nullptr;
	m_BackGround = new CBackGround;
	m_BackGround->SetTextre(CAssetMgr::GetInst()->LoadTexture(L"Stage2", L"texture\\Stage2.png"));
	m_BackOn = true;

	Vec2 mapsize =
		Vec2(m_BackGround->GetTextre()->GetWidth(), m_BackGround->GetTextre()->GetHeight());

	m_LevelMiddle = Vec2(mapsize.x / 2.f, mapsize.y / 2.f);
	m_BackGround->SetPos(m_LevelMiddle);
	m_BackGround->SetScale(mapsize);
	AddObject(BACKGROUND, m_BackGround);

	// 카메라 range설정
	m_CameraRangex = Vec2(685.f, mapsize.x - 685.f);
	m_CameraRangey = Vec2(683.f, 683.f);// + (mapsize.y - 767), 683.f);

	// 카메라 lookat 설정
	CCamera::GetInst()->SetLookAt(Vec2(m_LevelMiddle.x, m_CameraRangey.x - 250.f));

	// 플레이어 가져와서 레벨에 합류
	pPlayer = CLevelMgr::GetInst()->GetPlayer();
	pPlayer->SetPos(Vec2(m_LevelMiddle.x, 400.f));
	pPlayer->getMovement()->SetGround(false);
	AddObject(PLAYER, pPlayer);

	CUIMgr::GetInst()->SetUIVisible(L"StatusUI");
	CUIMgr::GetInst()->SetUIVisible(L"UpperBarUI");

	// Cwall
	CWall* pWall1 = new CWall;
	pWall1->SetPos(Vec2(-100.f, 500.f));
	AddObject(WALL, pWall1);
	CCollider* wallcol1 = pWall1->AddComponent<CCollider>(L"WallCollider1");
	wallcol1->SetScale(Vec2(200.f, 1000.f));

	CWall* pWall2 = new CWall;
	pWall2->SetPos(Vec2(mapsize.x + 100.f, 500.f));
	AddObject(WALL, pWall2);
	CCollider* wallcol2 = pWall2->AddComponent<CCollider>(L"WallCollider2");
	wallcol2->SetScale(Vec2(200.f, 1000.f));


	// 플랫폼 설치1
	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(m_LevelMiddle.x, 850.f));
	AddObject(PLATFORM, pPlatform);
	CCollider* platforcol1 = pPlatform->AddComponent<CCollider>(L"PlatformCollider1");
	platforcol1->SetScale(Vec2(5000.f, 250.f - 65.f));


	// 
	pBgm = CAssetMgr::GetInst()->LoadSound(L"BGM_02", L"sound\\ThroneOfDarkness.wav");
	pBgm->SetVolume(20);
	pBgm->SetPosition(45.f);
	pBgm ->Play(true);


	//CMonsterMgr::GetInst()->SpwanMonster(L"firstion", Vec2((m_LevelMiddle.x - 400.f), 400.f));
	//CMonsterMgr::GetInst()->SpwanMonster(L"firstyalda", Vec2((m_LevelMiddle.x + 400.f), 400.f));
	CMonsterMgr::GetInst()->SpwanRuleMonster(L"firstrulemon11");
	CMonsterMgr::GetInst()->SpwanRuleMonster(L"firstrulemon12");


}

void CPhaseSecond::enter()
{
	init();
	CCamera::GetInst()->FadeIn(0.3f);
}

void CPhaseSecond::exit()
{
	pBgm->Stop(true);
	DeleteAllObjects();
}

void CPhaseSecond::tick()
{
	CLevel::tick();

	// Enter 키가 눌리면 StartLevel 로 변환
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::PHASE_ZERO);
	}
}
