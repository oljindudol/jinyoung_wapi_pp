#include "pch.h"
#include "CWall.h"


CWall::CWall()
	: m_Collider(nullptr)
{
}

CWall::CWall(const CWall& _Origin)
	: CObj(_Origin)
	, m_Collider(nullptr)
{
}

CWall::~CWall()
{
}


void CWall::tick(float _DT)
{
}

void CWall::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	Vec2 OwnPos = _OwnCol->GetPos();
	Vec2 OwnprevPos = _OwnCol->GetPrevPos();
	Vec2 OwnScale = _OwnCol->GetScale();
	Vec2 OtherPos = _OtherCol->GetPos();
	Vec2 OtherScale = _OtherCol->GetScale();

	// ���� ���� ���� ������ ���� ���� ����
	// ���� ����  , ��밡 �����ʿ������� +
	// ���� ������, �����̸�		 -
	int ortsign = (OtherPos.x - OwnprevPos.x)>0 ? +1 : -1 ;


	// ���� ����  , ��밡 �����ʿ������� true
	// ��������� �հ���� 
	bool ortbool = (OtherPos.x - OwnprevPos.x) > 0 ? true : false;

	float wallend = OwnPos.x +  (OwnScale.x / 2.f) *ortsign;
	float otherend = OtherPos.x - (OtherScale.x / 2.f) * ortsign;

	// (���� ���ʱ���) ��end�� otherend ���� �����ʿ������� (�����վ�����)
	bool throu = otherend < wallend ? true : false;

	//ortbool: ���� �������ϰ�� �������ش�
	if (throu == ortbool)
	{
		float up = (_OwnCol->GetScale().x / 2.f +
			_OtherCol->GetScale().x / 2.f -
			abs(_OwnCol->GetPos().x
				- _OtherCol->GetPos().x)
			) / 2.f;

		_OtherObj->SetPos(Vec2(_OtherObj->GetPos().x + (up*ortsign), _OtherObj->GetPos().y));
	}
	
}

void CWall::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	CMovement* mov = _OtherObj->GetMovement();

	if (nullptr != mov)
	{
		Vec2 v = mov->GetVelocity();
		mov->SetVelocity(Vec2(v.x, 0.f));
	}
}

