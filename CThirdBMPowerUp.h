#pragma once
#include "CState.h"
class CThirdBMPowerUp :
	public CState
{
	GENERATED_OBJECT(CState);
public:
	CThirdBMPowerUp();
	virtual void finaltick(float _DT);
	virtual void Enter();
	virtual void Exit();

	~CThirdBMPowerUp();
	CLONE(CThirdBMPowerUp);
};

