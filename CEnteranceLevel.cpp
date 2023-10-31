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

#include "CBackGround.h"

void CEnteranceLevel::init()
{
	// ������
	CBackGround* pBackGround = nullptr;

	pBackGround = new CBackGround;
	pBackGround->SetPos(Vec2(800.f, 450.f));
	pBackGround->SetScale(Vec2(1990.f, 767.f));
	AddObject(BACKGROUND, pBackGround);


	// �÷��̾� ����
	CPlayer* pPlayer = new CPlayer;

	pPlayer->SetPos(Vec2(500.f, 200.f));
	pPlayer->SetScale(Vec2(50.f, 50.f));

	AddObject(PLAYER, pPlayer);

	// ���� ����
	CMonster* pMonster = nullptr;

	pMonster = new CMonster;
	pMonster->SetPos(Vec2(900.f, 500.f));
	pMonster->SetScale(Vec2(100.f, 100.f));
	AddObject(MONSTER, pMonster);

	// �÷��� ��ġ
	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(800.f, 900.f));
	AddObject(PLATFORM, pPlatform);


	// ī�޶� ����
	Vec2 vLookAt = CEngine::GetInst()->GetResolution();
	vLookAt /= 2.f;
	CCamera::GetInst()->SetLookAt(vLookAt);

	// �浹 ����
	CCollisionMgr::GetInst()->CheckCollision(MONSTER, PLAYER);
	CCollisionMgr::GetInst()->CheckCollision(PLAYER_PJ, MONSTER);
	CCollisionMgr::GetInst()->CheckCollision(PLAYER, PLATFORM);
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

	CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"BGM_01", L"sound\\TheWorld��sEnd.wav");
	pSound->SetVolume(100);
	pSound->SetPosition(45.f);
	pSound->Play(true);
}

void CEnteranceLevel::exit()
{
	DeleteAllObjects();
}

void CEnteranceLevel::tick()
{
	CLevel::tick();

	// Enter Ű�� ������ StartLevel �� ��ȯ
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