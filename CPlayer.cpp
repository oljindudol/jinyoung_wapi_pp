#include "pch.h"
#include "CPlayer.h"

#include "CTimeManager.h"
#include "CPal.h"
#include "CKeyMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CProjectile.h"

#include "CPathMgr.h"
#include "CEngine.h"

#include "CGuided.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CLogMgr.h"

#include "components.h"
#include "CPlatform.h"

#include "CSkillMgr.h"

#include "CAssetmgr.h"
#include "CSound.h"

#include "CPlayerIdle.h"
#include "CPlayerMove.h"
#include "CPlayerOnAir.h"
#include "CPlayerDown.h"
#include "CPlayerAttNorm.h"

#include "monsters.h"


/*
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnim.h"*/

class CCollider;


using std::wstring;

CPlayer::CPlayer()
	: m_Collider(nullptr)
	, m_Animator(nullptr)
	, m_Movement(nullptr)
	, hp(100)
	, mp(100)
	, att(5)
	, def(1000)
	, m_acctime(0.f)
	//m_Speed(500.f)
	//, m_Image(nullptr)
{



	SetName(L"Player");
	//이미지가 존재하는 상대경로 (contents 폴더로 부터)
	//힙메모리에할당
	//wstring strPath = CPathMgr::GetContentDir();
	//strPath+= L"texture\\Fighter.bmp";

	// 애니메이터 컴포넌트 추가
	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"PlayerAtlas", L"texture\\link_alpha.bmp");


	m_Animator = AddComponent<CAnimator>(L"Animator");
	m_Animator->CreateAnimation(L"common", L"pinkbean", L"idle", Vec2(20.f, -45.f));
	m_Animator->CreateAnimation(L"common", L"pinkbean", L"move", Vec2(20.f, -45.f), 3.f);
	m_Animator->CreateAnimation(L"common", L"pinkbean", L"doublejump", Vec2(0.f, -45.f),2.f);
	m_Animator->CreateAnimation(L"common", L"pinkbean", L"onair", Vec2(0.f, -45.f), 1.f,-1);
	m_Animator->CreateAnimation(L"common", L"pinkbean", L"stab", Vec2(0.f, -55.f), 1.f, -1);

	m_Animator->CreateAnimation(L"common", L"pinkbean", L"down", Vec2(-30.f, -20.f), 1.f, -1);


	m_Animator->Play(L"commonpinkbeanidle");





	//m_Animator->CreateAnimation(L"WalkDown", pAtlas, Vec2(0.f, 520.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 10);
	//m_Animator->CreateAnimation(L"WalkLeft", pAtlas, Vec2(0.f, 650.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 10);
	//m_Animator->CreateAnimation(L"WalkUp", pAtlas, Vec2(0.f, 780.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 10);
	//m_Animator->CreateAnimation(L"WalkRight", pAtlas, Vec2(0.f, 910.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 10);	
	//m_Animator->CreateAnimation(L"IdleDown", pAtlas, Vec2(0.f, 0.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 3);
	//m_Animator->CreateAnimation(L"IdleLeft", pAtlas, Vec2(0.f, 130.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 3);
	//m_Animator->CreateAnimation(L"IdleUp", pAtlas, Vec2(0.f, 260.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 1);
	//m_Animator->CreateAnimation(L"IdleRight", pAtlas, Vec2(0.f, 390.f), Vec2(120, 130), Vec2(0.f, -60.f), 0.05f, 3);
	//m_Animator->SaveAnimations(L"animdata");


	m_Animator->LoadAnimation(L"animdata\\IdleDown.txt");
	m_Animator->LoadAnimation(L"animdata\\IdleLeft.txt");
	m_Animator->LoadAnimation(L"animdata\\IdleRight.txt");
	m_Animator->LoadAnimation(L"animdata\\IdleUp.txt");
	m_Animator->LoadAnimation(L"animdata\\WalkDown.txt");
	m_Animator->LoadAnimation(L"animdata\\WalkLeft.txt");
	m_Animator->LoadAnimation(L"animdata\\WalkRight.txt");
	m_Animator->LoadAnimation(L"animdata\\WalkUp.txt");



	//m_Animator = AddComponent<CAnimator>(L"Animator");

	// 충돌체 컴포넌트 추가
	m_Collider = AddComponent<CCollider>(L"PlayerCollider");
	//m_Collider->SetOffsetPos(Vec2(0.f, 10.f));
	m_Collider->SetScale(Vec2(80.f, 80.f));
	m_Collider->SetOffsetPos(Vec2(0.f, -40.f));
	//AddComponent<CAnimator>();
	//AddComponent<CMovement>();
	// 이미지가 존재하는 상대경로(constent 폴더로부터)
	//m_pTexture = CAssetMgr::GetInst()->LoadTexture(L"PlayerTexture", L"texture\\fighter.bmp");


	// Movement 컴포넌트 추가
	m_Movement = AddComponent<CMovement>(L"PlayerMovement");
	m_Movement->SetMass(1.f);
	m_Movement->SetInitSpeed(200.f);
	m_Movement->SetMaxSpeed(200.f);
	m_Movement->SetFrictionScale(2200.f);

	m_Movement->UseGravity(true);
	m_Movement->SetGravity(Vec2(0.f, 2500.f));
	m_Movement->SetGround(false);


	m_PlayerState = AddComponent<CStateMachine>(L"PlayerState");
	m_PlayerState->AddState((UINT)PLAYER_STATE::IDLE, new CPlayerIdle);
	m_PlayerState->AddState((UINT)PLAYER_STATE::MOVE, new CPlayerMove);
	m_PlayerState->AddState((UINT)PLAYER_STATE::ON_AIR, new CPlayerOnAir);
	m_PlayerState->AddState((UINT)PLAYER_STATE::DOWN, new CPlayerDown);
	m_PlayerState->AddState((UINT)PLAYER_STATE::ATT_NM, new CPlayerAttNorm);
	m_PlayerState->ChangeState((UINT)PLAYER_STATE::IDLE);

}

CPlayer::CPlayer(const CPlayer& _Origin)
	: CObj(_Origin)
	, m_Collider(nullptr)
	, m_Animator(nullptr)
	, m_Movement(nullptr)
	, hp(_Origin.hp)
	, mp(_Origin.mp)
	, att(_Origin.att)
	, def(_Origin.def)
	, m_acctime(0.f)
{
	m_Collider = GetComponent<CCollider>();
	m_Animator = GetComponent<CAnimator>();
	m_Movement = GetComponent<CMovement>();
}



CPlayer::~CPlayer()
{
	//DeleteObject(hLoadBit);
	//DeleteObject(m_Image);
	//DeleteDC(m_ImageDC);
}

void CPlayer::tick(float _DT)
{
	Super::tick(_DT);

	Vec2 vPos = GetPos();


	//if (L"commonpinkbeanstab" == m_Animator->GetCurAnimName())
	//{
	//	m_acctime += _DT;

	//	if (0.6f < m_acctime)
	//	{
	//		m_Movement->IsGround() ? 
	//			m_Animator->Play(L"commonpinkbeanidle") :
	//			m_Animator->Play(L"commonpinkbeanonair");
	//		m_acctime = 0.f;
	//	}

	//}
	//else 
	//{


	////if (KEY_TAP(KEY::F1)) {
	////	int a = 0;
	////}

	//if (KEY_PRESSED(KEY::LEFT))
	//{
	//	ort = ORT_LEFT;
	//	if (m_Movement->IsGround()) {
	//		if (L"commonpinkbeanmove" != m_Animator->GetCurAnimName())
	//		{
	//			m_Animator->Play(L"commonpinkbeanmove");
	//		}
	//	}
	//	if (400.f > abs(m_Movement->GetVelocity().x)) 
	//	{
	//		m_Movement->AddForce(Vec2(-1000.f, 0.f));
	//	}
	//}

	//if (KEY_RELEASED(KEY::LEFT))
	//{
	//	if (m_Movement->IsGround()) {
	//		m_Animator->Play(L"commonpinkbeanidle");
	//	}
	//}




	//if (KEY_PRESSED(KEY::RIGHT))
	//{
	//	ort = ORT_RIGHT;
	//	if (m_Movement->IsGround()) {
	//		if (L"commonpinkbeanmove" != m_Animator->GetCurAnimName())
	//		{
	//			m_Animator->Play(L"commonpinkbeanmove");
	//		}
	//	}
	//	if (400.f > abs(m_Movement->GetVelocity().x))
	//	{
	//		m_Movement->AddForce(Vec2(1000.f, 0.f));
	//	}
	//}



	//if (KEY_RELEASED(KEY::RIGHT))
	//{
	//	if (m_Movement->IsGround()) {
	//		m_Animator->Play(L"commonpinkbeanidle");
	//	}
	//}


	//if (KEY_PRESSED(KEY::UP))
	//{

	//}
	//if (KEY_RELEASED(KEY::UP))
	//{
	//}

	//if (KEY_PRESSED(KEY::DOWN))
	//{
	//	if (m_Movement->IsGround()) {
	//		m_Animator->Play(L"commonpinkbeandown");
	//	}
	//}
	//if (KEY_RELEASED(KEY::DOWN))
	//{
	//	if (m_Movement->IsGround()) {
	//		m_Animator->Play(L"commonpinkbeanidle");
	//	}
	//}

	//if (KEY_TAP(C))
	//{
	//	CSkillMgr::GetInst()->ActivateSkill(L"commonpinkbeanphantomblow", GetPos(), ort);
	//	m_Animator->Play(L"commonpinkbeanstab");
	//}

	//if (KEY_TAP(N))
	//{

	//	CAssetMgr* pAssetMgr = CAssetMgr::GetInst();
	//	CSound* pSound = pAssetMgr->LoadSound(L"BGM_01", L"sound\\TheWorld’sEnd.wav");
	//	if (pAssetMgr->IsPlaying(pSound))
	//	{
	//		pSound->Stop(false);
	//	}
	//	else
	//	{
	//		pSound->Play(true);
	//	}
	//	
	//}

	//if (KEY_TAP(LALT))
	//{

	//	if (m_Movement->IsGround())
	//	{
	//		m_Movement->SetVelocity(Vec2(m_Movement->GetVelocity().x, -750.f));
	//	}
	//	else if (2 > m_Movement->GetJmpCnt() && !(KEY_PRESSED(KEY::UP)))
	//	{

	//		CSkillMgr::GetInst()->ActivateSkill(L"commonpinkbeandoublejump", GetPos(), ort);

	//		++(m_Movement->GetJmpCnt());
	//		float xvel = 700.f;
	//		if (ort == ORT_LEFT) xvel *= (-1);
	//		m_Movement->SetVelocity(Vec2(xvel, m_Movement->GetVelocity().y - 300.f));
	//	}
	//	else if (2 > m_Movement->GetJmpCnt() && (KEY_PRESSED(KEY::UP)))
	//	{
	//		++(m_Movement->GetJmpCnt());
	//		m_Movement->SetVelocity(Vec2(m_Movement->GetVelocity().x, m_Movement->GetVelocity().y - 1000.f));
	//	}
	//	else
	//	{

	//	}

	//}

	//}

	if (KEY_TAP(M))
	{
		CBackGround* pBack = CLevelMgr::GetInst()->GetCurLevel()->m_BackGround;
		bool bBack = CLevelMgr::GetInst()->GetCurLevel()->m_BackOn;

		// pback 이 설정되어있고 백그라운드off이라면
		// 켜준다
		if (nullptr != pBack && !bBack)
		{
			CTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT,(UINT_PTR)LAYER::BACKGROUND ,(UINT_PTR)pBack});
			CLevelMgr::GetInst()->GetCurLevel()->m_BackOn = true;
		}
		// pback 이 설정되어있고 백그라운드on이라면
		// 꺼준다
		else if (nullptr != pBack && bBack) 
		{
			CTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::EXPEL_OBJECT, (UINT_PTR)pBack });
			CLevelMgr::GetInst()->GetCurLevel()->m_BackOn = false;
		}



		//CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

		//CGuided* pProjectile = new CGuided;

		//Vec2 ProjectilePos = GetPos();
		//ProjectilePos.y -= GetScale().y / 2.f;

		//pProjectile->SetSpeed(500.f);
		//pProjectile->SetAngle(PI / 2.f);
		//pProjectile->SetPos(ProjectilePos);
		//pProjectile->SetScale(Vec2(25.f, 25.f));
		//pProjectile->SetDir(Vec2(0.f, -1.f));

		//CTaskMgr::GetInst()->AddTask(FTask{ CREATE_OBJECT, PLAYER_PJ, (UINT_PTR)pProjectile });

		//		
		//LOG(WARNING, L"경고");		
	}
	//SetPos(vPos);
}


//void CPlayer::render(HDC _dc)
//{
//	Vec2 vPos = GetRenderPos();
//	Vec2 vScale = GetScale();
//	SelectObject(_dc, CPal::GetInst()->getHPen(BLACK));
//	SelectObject(_dc, CPal::GetInst()->getHBrush(BLACK));
//	
//
//	UINT width = m_pTexture->GetWidth();
//	UINT height = m_pTexture->GetHeight();
//
//
//	TransparentBlt(_dc
//		, (int)vPos.x - width / 2
//		, (int)vPos.y - height / 2
//		, width
//		, height
//		, m_pTexture->GetDC()
//	/*BitBlt(_dc, (int)vPos.x - m_BitmapInfo.bmWidth / 2
//				, (int)vPos.y - m_BitmapInfo.bmHeight / 2
//				, m_BitmapInfo.bmWidth
//				, m_BitmapInfo.bmHeight
//				, m_ImageDC
//				, 0, 0, SRCCOPY);*/
//	//TransparentBlt(_dc, (int)vPos.x - m_BitmapInfo.bmWidth / 2
//	//	, (int)vPos.y - m_BitmapInfo.bmHeight / 2
//	//	, m_BitmapInfo.bmWidth
//	//	, m_BitmapInfo.bmHeight
//	//	, m_ImageDC
//		, 0, 0
//		, width
//		, height
//		//, m_BitmapInfo.bmWidth
//		//, m_BitmapInfo.bmHeight
//		, RGB(255, 0, 255));
//
//	Super::render(_dc);
//
//	//Rectangle(_dc
//	//	, int(vPos.x - vScale.x / 2)
//	//	, int(vPos.y - vScale.y / 2)
//	//	, int(vPos.x + vScale.x / 2)
//	//	, int(vPos.y + vScale.y / 2));
//
//}

void CPlayer::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	Super::BeginOverlap(_OwnCol, _OtherObj, _OtherCol);

	if ((UINT)LAYER::PLATFORM == _OtherObj->GetLayerIdx() ||
		(UINT)LAYER::PLATFORM_DEBUG == _OtherObj->GetLayerIdx() )
	{
		Vec2 playerprevpos = _OwnCol->GetPrevPos();
		Vec2 playerscale = _OwnCol->GetScale();
		Vec2 platpos = _OtherCol->GetPos();
		Vec2 platscale = _OtherCol->GetScale();

		float playerbottom = (playerprevpos.y ) * -1;
		float plattop = (platpos.y + platscale.y / 2.f) * -1;

		bool above = (platscale.x + playerscale.x) /2.f  >=
			abs(playerprevpos.x- platpos.x);

		if (playerbottom >= plattop && above)
		{
			m_Movement->SetGround(true);
		}

	}

}



void CPlayer::EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	Super::EndOverlap(_OwnCol, _OtherObj, _OtherCol);

	if ((UINT)LAYER::PLATFORM == _OtherObj->GetLayerIdx() ||
		(UINT)LAYER::PLATFORM_DEBUG == _OtherObj->GetLayerIdx())
	{
		float playerbottom = (_OwnCol->GetPrevPos().y ) * -1;
		float plattop = (_OtherCol->GetPos().y + _OtherCol->GetScale().y / 2.f) * -1;


		if (playerbottom >= plattop)
		{
			m_Movement->SetGround(false);
		}

	}


}

void CPlayer::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	Super::Overlap(_OwnCol, _OtherObj, _OtherCol);

}
