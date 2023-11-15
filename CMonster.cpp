#include "pch.h"
#include "CMonster.h"

#include "CCollider.h"
#include "CProjectile.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CNormalMonIdle.h"
#include "CNormalMonTrace.h"


CMonster::CMonster()
	: m_s1(L"")
	, m_s2(L"")
	, m_monstername(L"")
	, m_monsternum(0)
	, m_Info{}
	, m_Collider(nullptr)
	, m_AI(nullptr)
	, m_Animator(nullptr)
	, m_Movement(nullptr)
	, m_OnActivate(false)
	, m_attacked(false)
{
}

CMonster::CMonster(const CMonster& _Origin)
	: CObj(_Origin)
	, m_s1(L"")
	, m_s2(L"")
	, m_monstername(L"")
	, m_monsternum(0)
	, m_Info(_Origin.m_Info)
	, m_Collider(nullptr)
	, m_AI(nullptr)
	, m_Animator(nullptr)
	, m_Movement(nullptr)
	, m_OnActivate(false)
{
}

CMonster::~CMonster()
{

}

void CMonster::begin()
{
	m_Collider->InitColCnt();
}

void CMonster::Spawn(Vec2 _Spawnpos)
{
	SetPos(_Spawnpos);

	m_Info.HP = m_Info.MaxHp;

	m_OnActivate = true;

	SetLive();

	// 애니메이션 play
	if (nullptr != m_Animator)
	{
		m_Animator->Play(m_monstername + L"idle");
	}

	// 컬라이더 초기화

	// 그라운드설정 off
	if (nullptr != m_Movement)
	{
		m_Movement->SetGround(false);
	}


	// 상태 변화
	if (nullptr != m_AI)
	{
		m_AI->ChangeState((UINT)ENORMAL_MON_STATE::REGEN);
	}

	// 레벨에참여
	CTaskMgr::GetInst()->AddTask(FTask{ CREATE_OBJECT, (UINT_PTR)LAYER::MONSTER, (UINT_PTR)this });

}

void CMonster::SpawnRuleMon()
{
	SetPos(Vec2(0,0));

	m_OnActivate = true;

	SetLive();

	if (nullptr != m_AI)
	{
		m_AI->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
	}

	// 레벨에참여
	CTaskMgr::GetInst()->AddTask(FTask{ CREATE_OBJECT, (UINT_PTR)LAYER::MONSTER, (UINT_PTR)this });
}


void CMonster::tick(float _DT)
{
	Super::tick(_DT);
}


//void CMonster::render(HDC _dc)
//{
//	//Vec2 vRenderPos = GetRenderPos();
//	//Vec2 vScale = GetScale();
//
//	//BLENDFUNCTION blend = {};
//	//blend.BlendOp = AC_SRC_OVER;
//	//blend.BlendFlags = 0;
//
//	//blend.SourceConstantAlpha = 255; // 0 ~ 255
//	//blend.AlphaFormat = AC_SRC_ALPHA; // 0
//
//	//AlphaBlend(_dc
//	//	, int(vRenderPos.x - m_Texture->GetWidth() / 2.f)
//	//	, int(vRenderPos.y - m_Texture->GetHeight() / 2.f)
//	//	, m_Texture->GetWidth()
//	//	, m_Texture->GetHeight()
//	//	, m_Texture->GetDC()
//	//	, 0, 0
//	//	, m_Texture->GetWidth()
//	//	, m_Texture->GetHeight()
//	//	, blend);
//
//	Super::render(_dc);
//}


void CMonster::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	Super::BeginOverlap(_OwnCol, _OtherObj, _OtherCol);
}

void CMonster::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	Super::Overlap(_OwnCol, _OtherObj, _OtherCol);

}

void CMonster::EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	Super::EndOverlap(_OwnCol, _OtherObj, _OtherCol);
}
