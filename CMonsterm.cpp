#include "pch.h"
#include "CMonster.h"

#include "CTimeManager.h"
#include "CPal.h"
#include "CKeyman.h"



CMonster::CMonster()
	: m_Speed(500.f)
{
}

CMonster::~CMonster()
{
}


void CMonster::tick(float _DT)
{
	Vec2 vPos = GetPos();

	// 키입력이 발생하면 움직인다.
	if (KEY_PRESSED(A))
	{
		vPos.x += m_Speed * _DT;
	}

	if (KEY_PRESSED(D))
	{
		vPos.x -= m_Speed * _DT;
	}

	if (KEY_PRESSED(W))
	{
		vPos.y += m_Speed * _DT;
	}

	if (KEY_PRESSED(S))
	{
		vPos.y -= m_Speed * _DT;
	}

	SetPos(vPos);
}


void CMonster::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	SelectObject(_dc, CPal::GetInst()->getHPen(RED));
	SelectObject(_dc, CPal::GetInst()->getHBrush(RED));


	Ellipse(_dc
		, int(vPos.x - vScale.x / 2)
		, int(vPos.y - vScale.y / 2)
		, int(vPos.x + vScale.x / 2)
		, int(vPos.y + vScale.y / 2));

}