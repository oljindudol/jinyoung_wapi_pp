#include "pch.h"
#include "CMovement.h"
#include "CLogMgr.h"
#include "CObj.h"

CMovement::CMovement(CObj* _Owner)
	: CComponent(_Owner)
	, m_Mass(1.f)
	, m_InitSpeed(0.f)
	, m_MaxSpeed(0.f)
	, m_FrictionScale(0.f)
	, m_UseGravity(0.f)
	, m_Ground(false)
	, m_jumpcount(0)
{

}

CMovement::~CMovement()
{

}

void CMovement::finaltick(float _DT)
{
	m_Accel = m_Force / m_Mass;

	// 중력옵션 사용하는 경우
	if (m_UseGravity && !m_Ground)
	{
		m_Accel += m_GravityForce;
	}

	// 정지에 가까운 상태일 경우
	//if (m_Velocity.Length() < 100.f && m_Velocity.Length()!=0.f)
	//	if (!m_Accel.IsZero())
	//		LOG(LOG_LEVEL::LOG, std::to_wstring(m_Velocity.Length()).c_str());

	if (m_Velocity.Length() < 150.f)
	{
		if (!m_Accel.IsZero())
		{
			//LOG(LOG_LEVEL::LOG, L"speedinit");
			Vec2 vAccelDir = m_Accel;
			vAccelDir.Normalize();
			m_Velocity = vAccelDir * m_InitSpeed;
		}
	}
	else
	{
		m_Velocity += m_Accel * _DT;
	}


	// 최대 속도 제한
	//if (fabs(m_Velocity.x) > m_MaxSpeed)
	//{
	//	m_Velocity.x = (m_Velocity.x / abs(m_Velocity.x)) * m_MaxSpeed;
	//}



	// 물체에 적용되고있는 힘이 없으면 마찰력을 적용시킨다.
	if (  m_Velocity.x != 0.f && m_Ground&& m_Force.IsZero())
	{
		float fFriction = -m_Velocity.x;
		fFriction /= abs(fFriction);

		fFriction *= m_FrictionScale;

		float fFrictionAccel = (fFriction / m_Mass) * _DT;
		if (abs(m_Velocity.x) < abs(fFrictionAccel))
		{
			m_Velocity = Vec2(0.f, m_Velocity.y);
		}
		else
		{
			m_Velocity.x += fFrictionAccel;
		}
	}
	else if (m_Velocity.x != 0.f && m_Ground && !(m_Force.IsZero()))
	{
		float fFriction = -m_Velocity.x;
		fFriction /= abs(fFriction);
		
		if (m_MaxSpeed > m_Velocity.x) 
		{
			fFriction *= (m_FrictionScale / 3.f);
		}
		else
		{
			fFriction *= (m_FrictionScale / 4.f);
		}


		float fFrictionAccel = (fFriction / m_Mass) * _DT;
		if (abs(m_Velocity.x) < abs(fFrictionAccel))
		{
			m_Velocity = Vec2(0.f, m_Velocity.y);
		}
		else
		{
			m_Velocity.x += fFrictionAccel;
		}
	}

	Vec2 vObjPos = GetOwner()->GetPos();
	vObjPos += m_Velocity * _DT;
	GetOwner()->SetPos(vObjPos);

	// 힘 리셋
	m_Force = Vec2(0.f, 0.f);
}