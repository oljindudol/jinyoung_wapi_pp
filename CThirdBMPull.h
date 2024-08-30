#pragma once
#include "CState.h"
class CThirdBMPull :
	public CState
{
	GENERATED_OBJECT(CState);
public:
	CThirdBMPull();
	virtual void finaltick(float _DT);
	virtual void Enter();
	virtual void Exit();

	~CThirdBMPull();
	CLONE(CThirdBMPull);
};

