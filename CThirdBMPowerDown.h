#pragma once
#include "CState.h"
class CThirdBMPowerDown :
	public CState
{
	GENERATED_OBJECT(CState);
public:
	CThirdBMPowerDown();
	virtual void finaltick(float _DT);
	virtual void Enter();
	virtual void Exit();

	~CThirdBMPowerDown();
	CLONE(CThirdBMPowerDown);
};

