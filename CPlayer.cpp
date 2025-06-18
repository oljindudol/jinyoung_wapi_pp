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
#include "CPlayerAttSp.h"

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
#include "CPlayerDead.h"

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
	, level(290)
	, maxhp(50000)
	, hp(50000)
	, maxmp(20000)
	, mp(20000)
	, att(5)
	, def(1000)
	, m_acctime(0.f)
	, m_invincible_time(0.f)
	, completemission(false)
	//m_Speed(500.f)
	//, m_Image(nullptr)
{
	SetName(L"Player");
	//이미지가 존재하는 상대경로 (contents 폴더로 부터)
	//힙메모리에할당
	//wstring strPath = CPathMgr::GetContentDir();
	//strPath+= L"texture\\Fighter.bmp";

	// Movement 컴포넌트 추가
	m_Movement = AddComponent<CMovement>(L"PlayerMovement");
	m_Movement->SetMass(1.f);
	m_Movement->SetInitSpeed(200.f);
	m_Movement->SetMaxSpeed(200.f);
	m_Movement->SetFrictionScale(2200.f);

	m_Movement->UseGravity(true);
	m_Movement->SetGravity(Vec2(0.f, 2500.f));
	m_Movement->SetGround(false);

	m_Animator = AddComponent<CAnimator>(L"Animator");
	m_Animator->CreateAnimation(L"common", L"pinkbean", L"idle", Vec2(13.f, -41.f));
	m_Animator->CreateAnimation(L"common", L"pinkbean", L"move", Vec2(20.f, -45.f), 3.f);
	m_Animator->CreateAnimation(L"common", L"pinkbean", L"doublejump", Vec2(0.f, -45.f), 2.f);
	m_Animator->CreateAnimation(L"common", L"pinkbean", L"onair", Vec2(0.f, -45.f), 1.f, -1);
	m_Animator->CreateAnimation(L"common", L"pinkbean", L"stab", Vec2(0.f, -55.f), 1.f, -1);

	m_Animator->CreateAnimation(L"common", L"pinkbean", L"down", Vec2(-30.f, -20.f), 1.f, -1);

	m_Animator->CreateAnimation(L"common", L"pinkbean", L"move", Vec2(20.f, -45.f), 3.f);
	m_Animator->CreateAnimation(L"common", L"pinkbean", L"dead", Vec2(20.f, -45.f), 1.f, 18);

	m_Animator->Play(L"commonpinkbeanidle");

	// 충돌체 컴포넌트 추가
	m_Collider = AddComponent<CCollider>(L"PlayerCollider");
	//m_Collider->SetOffsetPos(Vec2(0.f, 10.f));
	m_Collider->SetScale(Vec2(80.f, 80.f));
	m_Collider->SetOffsetPos(Vec2(0.f, -40.f));
	//AddComponent<CAnimator>();
	//AddComponent<CMovement>();
	// 이미지가 존재하는 상대경로(constent 폴더로부터)
	//m_pTexture = CAssetMgr::GetInst()->LoadTexture(L"PlayerTexture", L"texture\\fighter.bmp");

	m_PlayerState = AddComponent<CStateMachine>(L"PlayerState");
	m_PlayerState->AddState((UINT)PLAYER_STATE::IDLE, new CPlayerIdle);
	m_PlayerState->AddState((UINT)PLAYER_STATE::MOVE, new CPlayerMove);
	m_PlayerState->AddState((UINT)PLAYER_STATE::ON_AIR, new CPlayerOnAir);
	m_PlayerState->AddState((UINT)PLAYER_STATE::DOWN, new CPlayerDown);
	m_PlayerState->AddState((UINT)PLAYER_STATE::ATT_NM, new CPlayerAttNorm);
	m_PlayerState->AddState((UINT)PLAYER_STATE::DEAD, new CPlayerDead);
	m_PlayerState->AddState((UINT)PLAYER_STATE::ATT_SP, new CPlayerAttSp);

	m_PlayerState->ChangeState((UINT)PLAYER_STATE::IDLE);

	InitDebuff();
}

CPlayer::CPlayer(const CPlayer& _Origin)
	: CObj(_Origin)
	, m_Collider(nullptr)
	, m_Animator(nullptr)
	, m_Movement(nullptr)
	, level(_Origin.level)
	, maxhp(_Origin.maxhp)
	, hp(_Origin.hp)
	, maxmp(_Origin.maxmp)
	, mp(_Origin.mp)
	, att(_Origin.att)
	, def(_Origin.def)
	, m_acctime(0.f)
	, m_PlayerState(nullptr)
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

	m_invincible_time -= _DT;

	//디버그용 자동회복
	if (hp < 25000.f
		&& (UINT)PLAYER_STATE::DEAD != getStateMachine()->GetCurStateNum())
	{
		hp = maxhp;
		m_acctime = 0.f;
	}

	if (KEY_TAP(KEY::Q))
	{
		if (m_invincible_time > 0.f)
		{
			m_invincible_time = 0.f;
		}
		else
		{
			m_invincible_time = 3.f;
		}
	}

	if (KEY_TAP(KEY::C))
	{
		hp = maxhp;
		m_PlayerState->ChangeState((UINT)PLAYER_STATE::IDLE);
	}

	//if (KEY_TAP(KEY::F10))
	//{
	//	hp = 0.f;
	//	m_PlayerState->ChangeState((UINT)PLAYER_STATE::DEAD);
	//}

	if (KEY_TAP(KEY::R))
	{
		PushDebuff(DEBUFF::DARKSITE);
	}
	ProcessDebuff();

	//if (KEY_TAP(KEY::GRAVE))
	//{
	//	m_Movement->SetVelocity(Vec2(0, 0));
	//}
	//if (KEY_PRESSED(KEY::GRAVE))
	//{
	//	m_Movement->UseGravity(false);
	//}
	//if (KEY_RELEASED(KEY::GRAVE))
	//{
	//	if (false == m_Movement->IsGround())
	//	{
	//		m_Movement->UseGravity(true);
	//	}
	//}

	//if (KEY_TAP(KEY::T))
	//{
	//	PushDebuff(DEBUFF::CREATION);
	//}
	//if (KEY_TAP(KEY::Y))
	//{
	//	PushDebuff(DEBUFF::DESTUCTION);
	//}

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
		(UINT)LAYER::PLATFORM_DEBUG == _OtherObj->GetLayerIdx())
	{
		Vec2 playerprevpos = _OwnCol->GetPrevPos();
		Vec2 playerscale = _OwnCol->GetScale();
		Vec2 platpos = _OtherCol->GetPos();
		Vec2 platscale = _OtherCol->GetScale();

		float playerbottom = (playerprevpos.y) * -1;
		float plattop = (platpos.y + platscale.y / 2.f) * -1;

		bool above = (platscale.x + playerscale.x) / 2.f >=
			abs(playerprevpos.x - platpos.x);

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
		float playerbottom = (_OwnCol->GetPrevPos().y) * -1;
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

void CPlayer::begin()
{
	m_Collider->InitColCnt();
	m_acctime = 0.f;

	InitDebuff();
}

void CPlayer::GetDamaged(float _percentdmg, DEBUFF _debuff)
{
	if (m_invincible_time > 0.f)
		return;

	//dead일 경우 무시
	if ((UINT)PLAYER_STATE::DEAD == m_PlayerState->GetCurStateNum() || m_invincible_time > 0.f)
	{
		return;
	}
	PushDebuff(_debuff);

	//TODO : DEBUFF::무적일 경우 무시

	//TODO:*파괴디버프 보정 추가
	int damage = (int)(maxhp * _percentdmg * (1.f + RandomPercentHtH() * 0.025));

	int resthp = hp - damage;

	//피격 데미지스킨을 출력한다
	CSkillMgr::GetInst()->PrintDamageVioletSkin(GetPos() - Vec2(GetScale().x / .7f, GetScale().y / .4f), damage);

	if (resthp > 0.f)
	{
		hp = resthp;
	}
	else
	{
		hp = 0;

		m_PlayerState->ChangeState((UINT)PLAYER_STATE::DEAD);
	}

	return;
}

void CPlayer::InitDebuff()
{
	m_Debuff.resize(0);

	//다크사이트
	FDebuff debuff = {};
	debuff.Debuff = DEBUFF::DARKSITE;
	debuff.Duration = 360.f;
	debuff.Acctime = 0.f;
	debuff.Active = false;
	if (false == HasDebuff(debuff.Debuff))
	{
		m_Debuff.push_back(debuff);
	}

	debuff.Debuff = DEBUFF::CREATION;
	debuff.Duration = 5.f;
	debuff.Acctime = 0.f;
	debuff.Active = false;
	if (false == HasDebuff(debuff.Debuff))
	{
		m_Debuff.push_back(debuff);
	}

	debuff.Debuff = DEBUFF::DESTUCTION;
	debuff.Duration = 5.f;
	debuff.Acctime = 0.f;
	debuff.Active = false;
	if (false == HasDebuff(debuff.Debuff))
	{
		m_Debuff.push_back(debuff);
	}

	debuff.Debuff = DEBUFF::INABILITY;
	debuff.Duration = 3.f;
	debuff.Acctime = 0.f;
	debuff.Active = false;
	if (false == HasDebuff(debuff.Debuff))
	{
		m_Debuff.push_back(debuff);
	}
}

void CPlayer::ProcessDebuff()
{
	// 디버프 이벤트 처리
	for (auto& e : m_DebuffEvent)
	{
		auto iter = m_Debuff.begin();
		for (; m_Debuff.end() != iter; ++iter)
		{
			if (e == iter->Debuff)
				break;
			else
				continue;
		}

		// 푸쉬된 버프이벤트가 버프배열에 존재하지않을시 무시.
		if (m_Debuff.end() == iter)
			continue;
		else
		{
			if (DEBUFF::DARKSITE == iter->Debuff)
			{
				if (true == iter->Active)
				{
					iter->Active = false;
				}
				else
				{
					iter->Acctime = 0.f;
					iter->Active = true;
				}
			}
			if (DEBUFF::CREATION == iter->Debuff)
			{
				iter->Acctime = 0.f;
				if (false == iter->Active)
				{
					iter->Active = true;
					m_pCreation = CSkillMgr::GetInst()->ActivateSkill(L"commondebuffcreation", CCamera::GetInst()->GetLookAt());
				}
			}
			if (DEBUFF::DESTUCTION == iter->Debuff)
			{
				iter->Acctime = 0.f;
				if (false == iter->Active)
				{
					iter->Active = true;
					m_pDestuction = CSkillMgr::GetInst()->ActivateSkill(L"commondebuffdestruction", CCamera::GetInst()->GetLookAt());
				}
			}
			if (DEBUFF::INABILITY == iter->Debuff)
			{
				iter->Acctime = 0.f;
				if (false == iter->Active)
				{
					iter->Active = true;
					m_pInablity = CSkillMgr::GetInst()->ActivateSkill(L"commondebuffinability", CCamera::GetInst()->GetLookAt());
				}
			}

		}
	}
	m_DebuffEvent.resize(0);

	auto dt = DT;

	// 지속시간 처리
	for (auto& e : m_Debuff)
	{
		if (false == e.Active)
		{
			continue;
		}
		else
		{
			e.Acctime += dt;
			if (e.Duration < e.Acctime)
			{
				e.Active = false;
				e.Acctime = 0.f;

				if (DEBUFF::CREATION == e.Debuff && nullptr != m_pCreation)
				{
					m_pCreation->Destroy();
				}
				if (DEBUFF::DESTUCTION == e.Debuff && nullptr != m_pDestuction)
				{
					m_pDestuction->Destroy();
				}
				if (DEBUFF::INABILITY == e.Debuff && nullptr != m_pInablity)
				{
					m_pInablity->Destroy();
				}
			}
		}
	}

	// 디버프 효과처리

	for (auto& e : m_Debuff)
	{
		if (DEBUFF::DARKSITE == e.Debuff)
		{
			if (true == e.Active)
				m_Animator->SetAlpha(120);
			else
				m_Animator->SetAlpha(255);
		}

		if (DEBUFF::CREATION == e.Debuff)
		{
			if (true == e.Active)
			{
				auto iter = m_Debuff.begin();
				for (; m_Debuff.end() != iter; ++iter)
				{
					if (DEBUFF::DESTUCTION == iter->Debuff)
					{
						break;
					}
				}
				//파괴버프가 배열에 존재하고 ,활성화 일시,
				// 1. 창조,파괴버프를 해제한다.
				// 2. 저주사를 실행한다.
				// 3. 봉인상태이상
				if (m_Debuff.end() != iter && true == iter->Active)
				{
					// 창조 해제
					if (nullptr != m_pCreation)
						m_pCreation->Destroy();
					e.Acctime = 0.f;
					e.Active = false;
					// 파괴 해제
					if (nullptr != m_pDestuction)
						m_pDestuction->Destroy();
					iter->Acctime = 0.f;
					iter->Active = false;
					// 저주사
					DeathByCurse();
					// 봉인상태이상
					PushDebuff(DEBUFF::INABILITY);
				}
			}
		}

	}
}

void CPlayer::PushDebuff(DEBUFF _debuff)
{
	m_DebuffEvent.push_back(_debuff);
}

bool CPlayer::IsDebuffActive(DEBUFF _debuff)
{
	bool ret = false;
	for (auto& e : m_Debuff)
	{
		if (_debuff == e.Debuff)
		{
			if (true == e.Active)
				ret = true;
			break;
		}
	}
	return ret;
}

bool CPlayer::HasDebuff(DEBUFF _debuff)
{
	bool ret = false;
	for (auto& e : m_Debuff)
	{
		if (_debuff == e.Debuff)
		{
			ret = true;
			break;
		}
	}
	return ret;
}

void CPlayer::RenderDebuff()
{
}

#include "CUIMgr.h"
void CPlayer::DeathByCurse()
{
	//데스카운트 깍기
	FRule* pRule = CLevelMgr::GetInst()->GetpRule();
	--(pRule->DeathCount);

	//부활메세지 출력1 : 데스카운트가 1이상일때
	if (pRule->DeathCount >= 1)
	{
	}
	//부활메세지 출력2 : 데스카운트가 1보다 작을때
	else
	{

	}

	CSkillMgr::GetInst()->ActivateSkill(L"commondebuffdeathbycurse", CCamera::GetInst()->GetLookAt());
}
