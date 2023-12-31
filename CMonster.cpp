#include "pch.h"
#include "CMonster.h"

#include "CCollider.h"
#include "CProjectile.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CNormalMonIdle.h"
#include "CNormalMonTrace.h"
#include "CMonsterMgr.h"


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
	, m_MonsterLayer((UINT)LAYER::MONSTER)
{
	m_Info.MaxHp = 50000;
	m_Info.HP = m_Info.MaxHp;

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
	, m_attacked(false)
	, m_MonsterLayer(_Origin.m_MonsterLayer)
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
		//state변경에 실패햇을경우(regen이 없을경우)
		if (nullptr != m_AI->FindState((UINT)ENORMAL_MON_STATE::REGEN))
		{
			m_AI->ChangeState((UINT)ENORMAL_MON_STATE::REGEN);
		}
		else
		{
			m_AI->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
		}
	}

	// 레벨에참여
	CTaskMgr::GetInst()->AddTask(FTask{ CREATE_OBJECT, (UINT_PTR)m_MonsterLayer, (UINT_PTR)this });

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
	CTaskMgr::GetInst()->AddTask(FTask{ CREATE_OBJECT, (UINT_PTR)m_MonsterLayer, (UINT_PTR)this });
}

UINT CMonster::GetCurstateNum()
{
	if (nullptr != m_AI)
	{
		return m_AI->GetCurStateNum();
	}
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

void CMonster::GetDamaged(float _damagepercent, int damagecnt)
{
	//dead이거나 regen일경우 무시
	if ((UINT)ENORMAL_MON_STATE::REGEN == m_AI->GetCurStateNum()
		|| (UINT)ENORMAL_MON_STATE::DIE == m_AI->GetCurStateNum())
	{
		return;
	}


	float linedamage = m_Info.MaxHp * _damagepercent;

	//데미지 출력 배율
	int multi = 283472323;
	float yoffset = 30.f;

	Vec2 tScale = Vec2();



	//아이온 일때
	if (L"firstion" == m_monstername)
	{

		float resthp = m_Info.HP - linedamage * damagecnt;
		if (resthp > 0.f)
		{
			m_Info.HP = resthp;
		}
		else
		{
			auto yaldavec = CMonsterMgr::GetInst()->FindMonster(L"firstyalda");
			CMonster* yalda = nullptr;
			if (nullptr != yaldavec)
				yalda = (*yaldavec)[0];

			m_Info.HP = 0.f;
			m_AI->ChangeState((UINT)ENORMAL_MON_STATE::DIE);
			if(nullptr != yalda)
				yalda->m_AI->ChangeState((UINT)ENORMAL_MON_STATE::DIE);
		}
		tScale = GetScale();
	}
	//얄다바오트 일때
	else if (L"firstyalda" == m_monstername)
	{
		auto ion =CLevelMgr::GetInst()->GetCurLevelMon();
		if (nullptr == ion)
			return;

		float resthp = ion->m_Info.HP - linedamage * damagecnt;
		if (resthp > 0.f)
		{
			ion->m_Info.HP = resthp;
		}
		else
		{
			ion->m_Info.HP = 0.f;
			ion->m_AI->ChangeState((UINT)ENORMAL_MON_STATE::DIE);
			m_AI->ChangeState((UINT)ENORMAL_MON_STATE::DIE);
		}
		tScale = GetScale();
	}
	//일반 몬스터일때
	else
	{
		float resthp = m_Info.HP - linedamage * damagecnt;
		if (resthp > 0.f)
		{
			m_Info.HP = resthp;
		}
		else
		{
			m_Info.HP = 0.f;
			m_AI->ChangeState((UINT)ENORMAL_MON_STATE::DIE);
		}
		tScale = Vec2(GetScale().x, GetScale().y) / 2;
	}

	for (int i = 0; i < damagecnt; i++)
	{
		long long damage = (long long)(linedamage * (1.f + RandomPercentHtH() * 0.025) * multi);
		//타격 데미지스킨을 출력한다
		CSkillMgr::GetInst()->PrintDamageRedSkin(GetPos()
			- Vec2(tScale.x, tScale.y + yoffset * i)
			, damage, i);
	}

	return;
}