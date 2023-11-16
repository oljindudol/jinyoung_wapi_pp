#include "pch.h"
#include "ChainAttack.h"
#include "CSkillMgr.h"
#include "CLevelMgr.h"
#include "CPlayer.h"

void ChainAttack::tick(float _DT)
{
	Super::tick(_DT);
	if (m_activedtime > 1.86f)
	{
		m_Collider->SetOffsetPos(Vec2(m_Collider->GetOffsetPos().x , 4000.f));
			return;
	}
	if (m_activedtime < 0.78f)
	{
		m_Collider->SetOffsetPos(Vec2(m_Collider->GetOffsetPos().x, 4000.f));
			return;
	}

	if (m_activedtime > 0.78f)
	{
		m_Collider->SetOffsetPos(Vec2(m_Collider->GetOffsetPos().x, -500.f));
		return;
	}
	

}

ChainAttack::ChainAttack()
{
	m_s1 = L"first";
	m_s2 = L"rulemon";
	m_s3 = L"chainattack";

	m_skillname = m_s1 + m_s2 + m_s3;

	//몇번째 스킬인지
	m_skillnum = CSkillMgr::GetInst()->FindNextSkillNumber(m_skillname);

	SetName(m_skillname + L"_" + std::to_wstring(m_skillnum));

	//컬라이더
	m_Collider =
		AddComponent<CCollider>(GetName() + L"Collider");
	m_Collider->SetScale(Vec2(100.f, 1300.f));
	m_Collider->m_vOffsetPos = (Vec2(-15.f, -500.f));

	//pNewSkill -> m_Collider->SetOffsetPos(Vec2(0.f, 0.f));

	//애니메이션
	m_Animator =
		AddComponent<CAnimator>(GetName() + L"Animator");

	m_Animator->
		CreateAnimation(m_s1, m_s2, m_s3,
			Vec2(0.f, 0.f), 1.f, -1, ORT_LEFT);

	for (int i = 20; i > -20; i-=2)
	{
		m_Animator->
			CreateRotatedAnimation(m_s1, m_s2, m_s3,
				i, Vec2( -500.f * tanf(0.0174533f * i), -500.f), 1.f, -1, ORT_LEFT);
	}


	//m_Animator->Play(m_s1 + m_s2 + m_s3 + L"_20");

	m_skilllayer = LAYER::MONSTER_PJ;
	duration = 1.5f;
	cooltime = 0.f;
	m_att = 5.f;
	m_debuff = DEBUFF::NONE;
}

ChainAttack::ChainAttack(const ChainAttack& _Origin)
{
	//m_Animator->get
}

void ChainAttack::activate(Vec2 _beginpos, ORIENTATION _ort)
{

	float perc = (float)rand()/ (float)32767;
	int rot = 20 - 2*((int)(20 * perc));

	m_Animator->Play(m_s1 + m_s2 + m_s3 + L"_" + std::to_wstring(rot));
	//m_Animator->Play(m_s1 + m_s2 + m_s3 );

	SetRotation((float)rot* -0.0174533f);
	m_Collider->SetOffsetPos(Vec2(  -15.f -500.f * tanf(0.0174533f * rot), -2000.f));
	Super::activate(_beginpos, _ort);

}

void ChainAttack::begin()
{
	m_Collider->InitColCnt();

}




void ChainAttack::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (LAYER::PLAYER == (UINT)_OtherObj->GetLayerIdx())
	{
		CLevelMgr::GetInst()->GetPlayer()->GetDamaged(0.15f, DEBUFF::DESTUCTION);
	}
}



ChainAttack::~ChainAttack()
{
}

