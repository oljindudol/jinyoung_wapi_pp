#pragma once
#include "CState.h"
class CThirdBMIdle :
	public CState
{
	GENERATED_OBJECT(CState);
public:
	CThirdBMIdle();
	virtual void finaltick(float _DT);
	virtual void Enter();
	virtual void Exit();

	~CThirdBMIdle();
	CLONE(CThirdBMIdle);
};

