#include "pch.h"
#include "CBlindness.h"

#include "CSkillMgr.h"
#include "CLevelMgr.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CAssetMgr.h"
#include "CEngine.h"


CBlindness::CBlindness()
	:m_pPlayer(nullptr)
	, m_pMask(nullptr)
{
	m_s1 = L"second";
	m_s2 = L"blindness";
	m_s3 = L"use";

	m_skillname = m_s1 + m_s2 + m_s3;

	//몇번째 스킬인지
	m_skillnum = CSkillMgr::GetInst()->FindNextSkillNumber(m_skillname);

	SetName(m_skillname + L"_" + std::to_wstring(m_skillnum));

	SetScale(Vec2(256, 256));

	//애니메이션
	m_Animator =
		AddComponent<CAnimator>(GetName() + L"Animator");

	m_Animator->
		CreateAnimation(m_s1, m_s2, m_s3,
			Vec2(0.f, GetScale().y / -2), 1.f, -1, ORT_LEFT)->Setoffset(Vec2(0.f,-80.f));

	m_pMask = CAssetMgr::GetInst()->LoadTexture(L"blindnessmask", L"texture\\anim\\second\\blindness\\blind.png");

	m_skilllayer = LAYER::WORLD_STATIC;
	duration = 5.f;
	cooltime = 0.f;
	m_att = 5.f;
	m_debuff = DEBUFF::NONE;


	m_vRes = CEngine::GetInst()->GetResolution();
}

void CBlindness::tick(float _DT)
{
	Super::tick(_DT);

	SetPos(m_pPlayer->GetPos());
}

void CBlindness::activate(Vec2 _beginpos, ORIENTATION _ort)
{
	m_pPlayer = CLevelMgr::GetInst()->GetPlayer();
	m_Animator->Play(m_s1 + m_s2 + m_s3);


	Super::activate(_beginpos, _ort);
}

void CBlindness::begin()
{
}


void CBlindness::render(HDC _dc)
{
	Super::render(_dc);


	SELECT_PEN(_dc, BK_PEN);
	SELECT_BRUSH(_dc, (HBRUSH)GetStockObject(BLACK_BRUSH));


	Vec2 lt = GetRenderPos() + Vec2(GetScale().x /-2 ,GetScale().y /-2) - Vec2(0.f, m_pPlayer->GetScale().y);
	Vec2 rt = GetRenderPos() + Vec2(GetScale().x / 2 ,GetScale().y /-2) - Vec2(0.f, m_pPlayer->GetScale().y);
	Vec2 lb = GetRenderPos() + Vec2(GetScale().x /-2 ,GetScale().y/  2) - Vec2(0.f, m_pPlayer->GetScale().y);
	Vec2 rb = GetRenderPos() + Vec2(GetScale().x / 2 ,GetScale().y/  2) - Vec2(0.f, m_pPlayer->GetScale().y);

	//zero to lb
	Rectangle(_dc, 0, 0
		,(int)lb.x, (int)m_vRes.y);

	//rt.x,0 to res.x,res.x
	Rectangle(_dc, (int)rt.x, 0
		, (int)m_vRes.x, (int)m_vRes.y);

	//lt.x,0 to rt
	Rectangle(_dc, (int)lt.x, 0
		, (int)rt.x, (int)rt.y);

	//lb to r.x , res.y
	Rectangle(_dc, (int)lb.x, (int)lb.y
		, (int)rb.x, (int)m_vRes.y);


	SettexturetoDc(_dc, m_pMask, GetRenderPos() - GetScale()/2 - Vec2(0.f,m_pPlayer->GetScale().y));

}

CBlindness::CBlindness(const CBlindness& _Origin)
{
}

CBlindness::~CBlindness()
{
}
