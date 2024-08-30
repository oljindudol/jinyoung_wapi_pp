#pragma once
#include "CState.h"
class CThirdBMPush :
	public CState
{
	GENERATED_OBJECT(CState);
public:
	CThirdBMPush();
	virtual void finaltick(float _DT);
	virtual void Enter();
	virtual void Exit();

	~CThirdBMPush();
	CLONE(CThirdBMPush);
};

