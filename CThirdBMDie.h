#pragma once
#include "CState.h"
class CThirdBMDie :
	public CState
{
	GENERATED_OBJECT(CState);
public:
	CThirdBMDie();
	virtual void finaltick(float _DT);
	virtual void Enter();
	virtual void Exit();

	~CThirdBMDie();
	CLONE(CThirdBMDie);
};

