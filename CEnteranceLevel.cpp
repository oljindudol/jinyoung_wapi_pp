#include "pch.h"
#include "CEnteranceLevel.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CPlatform.h"

#include "CEngine.h"
#include "CCamera.h"
#include "CCollisionMgr.h"

#include "CKeyMgr.h"
#include "CLevelMgr.h"

#include "CAssetMgr.h"
#include "CSound.h"

#include "CMonsterMgr.h"

#include "CBackGround.h"


CEnteranceLevel::~CEnteranceLevel()
{


}

void CEnteranceLevel::init()
{
	// 배경생성
	//CBackGround* pBackGround = nullptr;

	m_BackGround = new CBackGround;
	m_BackGround->SetPos(Vec2(800.f, 450.f));
	m_BackGround->SetScale(Vec2(1990.f, 767.f));

	m_BackGround->SetTextre(CAssetMgr::GetInst()->LoadTexture(L"Stage0", L"texture\\Stage0.png"));
	m_BackOn = true;
	AddObject(BACKGROUND, m_BackGround);



	// 플레이어 생성
	CPlayer* pPlayer = new CPlayer;

	pPlayer->SetPos(Vec2(500.f, 200.f));
	pPlayer->SetScale(Vec2(50.f, 50.f));

	AddObject(PLAYER, pPlayer);

	// 몬스터 매니저에 이관
	// 몬스터 생성
	//ion* p_ion = nullptr;

	//p_ion = new ion;
	//p_ion->SetPos(Vec2(900.f, 800.f));
	//p_ion->SetScale(Vec2(100.f, 100.f));
	//AddObject(MONSTER, p_ion);



	CPlatform* pPlatform2 = new CPlatform;
	pPlatform2->SetPos(Vec2(800.f, 700.f));
	AddObject(PLATFORM_DEBUG, pPlatform2);
	CCollider* platforcol2 = pPlatform2->AddComponent<CCollider>(L"PlatformCollider2");
	platforcol2->SetScale(Vec2(1000.f, 20.f));

	// 플랫폼 설치
	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(800.f, 900.f));
	AddObject(PLATFORM, pPlatform);
	CCollider* platforcol1 = pPlatform->AddComponent<CCollider>(L"PlatformCollider1");
	platforcol1->SetScale(Vec2(2000.f, 250.f));


	// 카메라 설정
	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;
	CCamera::GetInst()->SetLookAt(vLookAt);

	// 충돌 설정
	//CCollisionMgr::GetInst()->CheckCollision(MONSTER, PLAYER);
	//CCollisionMgr::GetInst()->CheckCollision(PLAYER_PJ, MONSTER);
	//CCollisionMgr::GetInst()->CheckCollision(PLAYER, PLATFORM);
	//CCollisionMgr::GetInst()->CheckCollision(MONSTER, PLATFORM);


	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"BGM_01", L"sound\\TheWorld’sEnd.wav");
	pSound->SetVolume(20);
	pSound->SetPosition(45.f);
	pSound->Play(true);
}

void CEnteranceLevel::enter()
{
	init();
	//CCamera::GetInst()->FadeOut(3.f);
	//CCamera::GetInst()->FadeIn(0.3f);

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
	DeleteAllObjects();
}

void CEnteranceLevel::tick()
{
	CLevel::tick();

	// Enter 키가 눌리면 StartLevel 로 변환
	if (KEY_TAP(KEY::_1))
	{
		float perc = (float)rand() / (float)32767;


		CMonsterMgr::GetInst()->SpwanMonster(L"firstion", Vec2((1600.f*perc), 200.f));
	}



	// Enter 키가 눌리면 StartLevel 로 변환
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::EDITOR_LEVEL);
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