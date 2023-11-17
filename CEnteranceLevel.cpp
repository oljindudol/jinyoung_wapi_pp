#include "pch.h"
#include "CEnteranceLevel.h"

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
#include "CPortal.h"

CEnteranceLevel::~CEnteranceLevel()
{


}

void CEnteranceLevel::init()
{
	// ������
	//CBackGround* pBackGround = nullptr;
	m_BackGround = new CBackGround;
	m_BackGround->SetTextre(CAssetMgr::GetInst()->LoadTexture(L"Stage0", L"texture\\Stage0.png"));
	m_BackOn = true;

	Vec2 mapsize =
		Vec2(m_BackGround->GetTextre()->GetWidth(), m_BackGround->GetTextre()->GetHeight());

	m_LevelMiddle = Vec2(mapsize.x/2.f, mapsize.y / 2.f);
	m_BackGround->SetPos(m_LevelMiddle);
	m_BackGround->SetScale(mapsize);
	AddObject(BACKGROUND, m_BackGround);


	// ī�޶� range����
	m_CameraRangex = Vec2(685.f, mapsize.x - 685.f);
	m_CameraRangey = Vec2(683.f + (mapsize.y - 767),683.f);

	// ī�޶� lookat ����
	CCamera::GetInst()->SetLookAt(Vec2(m_CameraRangex.x, m_CameraRangey.x -300.f));


	// �÷��̾� �����ͼ� ������ �շ�
	pPlayer = CLevelMgr::GetInst()->GetPlayer();
	pPlayer->SetPos(Vec2(250.f, 200.f));
	pPlayer->getMovement()->SetGround(false);
	//pPlayer->getCollider()->InitColCnt();
	AddObject(PLAYER, pPlayer);

	// �������ͽ��� ����
	//CStatusUI* pStatusUI = new CStatusUI;
	//AddObject(LAYER::UI, pStatusUI);
	CUIMgr::GetInst()->SetUIVisible(L"StatusUI");

	// ���� �Ŵ����� �̰�
	// ���� ����
	//ion* p_ion = nullptr;

	//p_ion = new ion;
	//p_ion->SetPos(Vec2(900.f, 800.f));
	//p_ion->SetScale(Vec2(100.f, 100.f));
	//AddObject(MONSTER, p_ion);


	// Cwall
	CWall* pWall1 = new CWall;
	pWall1->SetPos(Vec2(-100.f, 500.f));
	AddObject(WALL, pWall1);
	CCollider* wallcol1 = pWall1->AddComponent<CCollider>(L"WallCollider1");
	wallcol1->SetScale(Vec2(200.f, 1000.f));


	CWall* pWall2 = new CWall;
	pWall2->SetPos(Vec2(mapsize.x+100.f, 500.f));
	AddObject(WALL, pWall2);
	CCollider* wallcol2 = pWall2->AddComponent<CCollider>(L"WallCollider2");
	wallcol2->SetScale(Vec2(200.f, 1000.f));


	//��Ż��ġ
	CPortal* pPortal = new CPortal;
	pPortal->SetPos(Vec2(m_LevelMiddle.x, 620.f - 80.f));
	AddObject(PORTAL, pPortal);

	// �÷��� ��ġ2
	CPlatform* pPlatform2 = new CPlatform;
	pPlatform2->SetPos(Vec2(m_LevelMiddle.x, 620.f - 80.f));
	AddObject(PLATFORM_DEBUG, pPlatform2);
	CCollider* platforcol2 = pPlatform2->AddComponent<CCollider>(L"PlatformCollider2");
	platforcol2->SetScale(Vec2(550.f, 1.f));

	// �÷��� ��ġ1
	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(m_LevelMiddle.x , 795.f -85.f));
	AddObject(PLATFORM, pPlatform);
	CCollider* platforcol1 = pPlatform->AddComponent<CCollider>(L"PlatformCollider1");
	platforcol1->SetScale(Vec2(3000.f, 250.f));


	// ī�޶� ����
	//Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	//vLookAt /= 2.f;
	//CCamera::GetInst()->SetLookAt(vLookAt);

	// �浹 ����
	//CCollisionMgr::GetInst()->CheckCollision(MONSTER, PLAYER);
	//CCollisionMgr::GetInst()->CheckCollision(PLAYER_PJ, MONSTER);
	//CCollisionMgr::GetInst()->CheckCollision(PLAYER, PLATFORM);
	//CCollisionMgr::GetInst()->CheckCollision(MONSTER, PLATFORM);



	//CPanelUI* pStatusUI = new CPanelUI;
	//pStatusUI->SetScale(Vec2(204.f, 70.f));
	//pStatusUI->SetPos(Vec2(600.f, 690.f));


	pBgm = CAssetMgr::GetInst()->LoadSound(L"BGM_00", L"sound\\TheWorld��sEnd.wav");
	pBgm->SetVolume(20);
	pBgm->SetPosition(45.f);
	pBgm->Play(true);



}

void CEnteranceLevel::enter()
{
	init();
	//CCamera::GetInst()->FadeOut(3.f);
	CCamera::GetInst()->FadeIn(0.3f);

	//CCamera::GetInst()->FadeOut(0.3f);
	//CCamera::GetInst()->FadeIn(0.3f);

	//CCamera::GetInst()->FadeOut(0.3f);
	//CCamera::GetInst()->FadeIn(0.3f);

	//CCamera::GetInst()->FadeOut(0.3f);
	//CCamera::GetInst()->FadeIn(0.3f);

	//CCamera::GetInst()->FadeOut(0.3f);
	//CCamera::GetInst()->FadeIn(0.3f);

}

void CEnteranceLevel::exit()
{
	pBgm->Stop(true);
	DeleteAllObjects();
}

void CEnteranceLevel::tick()
{
	CLevel::tick();
	
	// Enter Ű�� ������ StartLevel �� ��ȯ
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::PHASE_FIRST);
	}

	//if (KEY_TAP(KEY::M))
	//{
	//	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"BGM_02", L"sound\\BGM_Stage1.wav");
	//	pSound->SetVolume(100);
	//	pSound->SetPosition(45.f);
	//	pSound->Play(true);
	//}

	//if (KEY_TAP(KEY::F))
	//{
	//	CCamera::GetInst()->FadeIn(2.5f);
	//}

	//if (KEY_TAP(KEY::G))
	//{
	//	CCamera::GetInst()->FadeOut(2.5f);
	//}
}