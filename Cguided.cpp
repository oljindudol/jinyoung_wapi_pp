#include "pch.h"
#include "CGuided.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CMonster.h"
#include "CTimeManager.h"

#include "CCollider.h"

CGuided::CGuided()
	: m_Target(nullptr)
	, m_fMass(1.f)
	, m_fRotateSpeed(PI)
{

}

CGuided::CGuided(const CGuided& _Origin)
	: m_Target(nullptr)
	, m_fMass(_Origin.m_fMass)
	, m_vAccel(_Origin.m_vAccel)
	, m_vVelocity(_Origin.m_vVelocity)
	, m_vForce(_Origin.m_vForce)
	, m_vDir(_Origin.m_vDir)
	, m_fRotateSpeed(_Origin.m_fRotateSpeed)
{
}


CGuided::~CGuided()
{
}

void CGuided::begin()
{
	Super::begin();

	GetCollider()->SetScale((GetScale()));
}


void CGuided::tick(float _DT)
{
	Super::tick(_DT);

	if (!IsValid(m_Target))
	{
		FindTarget();
	}

	if (!IsValid(m_Target))
	{
		Vec2 vPos = GetPos();

		vPos.x += m_vDir.x * GetSpeed() * DT;
		vPos.y += m_vDir.y * GetSpeed() * DT;

		SetPos(vPos);
	}
	else
	{

		//update1();
		//update2();
		update3();
	}
}


void CGuided::update2()
{
	// 힘에 의한 움직임
	// 1. 타겟을 향하는 방향으로 100의 크기의 힘을 설정
	float Force = 1000.f;
	Vec2 vForce = m_Target->GetPos() - GetPos();
	vForce.Normalize() *= Force;

	// 가속도 구하기
	// F = M * A
	// A = F / M
	m_vAccel = vForce / m_fMass;

	// 가속도에 의해서 시간당 속도가 변화함
	m_vVelocity += m_vAccel * DT;

	// 거리 = 속도 * 시간
	Vec2 vPos = GetPos();
	vPos += m_vVelocity * DT;

	SetPos(vPos);
}





void CGuided::update1()
{
	// 유도탄에서 몬스터를 향하는 방향을 구한다.
	Vec2 vPos = GetPos();


	Vec2 vDir = m_Target->GetPos() - GetPos();
	vDir.Normalize();

	vPos.x += vDir.x * GetSpeed() * DT;
	vPos.y += vDir.y * GetSpeed() * DT;

	SetPos(vPos);
}

void CGuided::update3()
{
	m_vDir.Normalize();

	// 목적지를 향하는 방향벡터
	Vec2 vDest = m_Target->GetPos() - GetPos();
	vDest.Normalize();

	// 현재 진행 방향과 목적지를 향하는 방향을 내적해서 둘 사이의 각도를 구한다.
	// m_vDir 과 vDest 를 내적, vA ● vB == |vA| * |vB| * cos(@)
	float fDot = m_vDir.x * vDest.x + m_vDir.y * vDest.y;
	float fAngle = acosf(fDot);

	// 진행 방향과 목적지를 향하는 방향이 각도 1도 이내에 들어오면 더이상 진행방향을 회전하지 않는다.
	if (fAngle > PI / 90.f)
	{
		// 타겟을 향해서 방향을 회전한다.
		if (GetRotateClock(m_vDir, vDest))
		{
			m_vDir = Rotate(m_vDir, m_fRotateSpeed * DT);
		}
		else
		{
			m_vDir = Rotate(m_vDir, -m_fRotateSpeed * DT);
		}
	}

	// 현재 방향을 향해서 이동한다.
	float fSpeed = GetSpeed();

	m_vVelocity = m_vDir * fSpeed;

	Vec2 vPos = GetPos();
	vPos += m_vVelocity * DT;
	SetPos(vPos);
}



void CGuided::FindTarget()
{
	// 현재 레벨에 있는 오브젝트들 중에서 CMonster 로부터 파생된 객체목록을 받아온다.
	//vector<CMonster*> vecMon;
	//CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	//pCurLevel->GetObjects<CMonster>(vecMon);
	
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	const vector<CObj*>& vecMon = pCurLevel->GetObjects(LAYER::MONSTER);

	// 몬스터 목록 중, 유도탄과 더 가까운 몬스터를 타겟으로 지정한다.
	if (vecMon.size() == 1)
	{
		//m_Target = vecMon[0];
		m_Target = dynamic_cast<CMonster*>(vecMon[0]);

		// Level 의 Monster Layer 에 Monster 가 아닌 다른 클래스타입의 객체가 들어있었다.
		assert(m_Target);
	}
	else if (vecMon.empty())
	{
		return;
	}
	else
	{
		float fMax = 2000.f;

		for (size_t i = 0; i < vecMon.size(); ++i)
		{
			float fDistance = GetPos().Distance(vecMon[i]->GetPos());

			if (fMax > fDistance)
			{
				fMax = fDistance;
				m_Target = dynamic_cast<CMonster*>(vecMon[i]);

				// Level 의 Monster Layer 에 Monster 가 아닌 다른 클래스타입의 객체가 들어있었다.
				assert(m_Target);
				//m_Target = vecMon[i];
			}
		}
	}
}

void CGuided::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	if (dynamic_cast<CMonster*>(_OtherObj))
	{
		Destroy();
	}
}
