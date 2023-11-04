#include "pch.h"
#include "CState.h"

CState::CState()
	: m_pSM(nullptr)
	, m_acctime(0.f)
	, m_skillortsign(-1)
	, m_pPlayer(nullptr)
{
}

CState::~CState()
{
}
