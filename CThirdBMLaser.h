#pragma once
#include "CState.h"
class CThirdBMLaser :
	public CState
{
	GENERATED_OBJECT(CState);
public:
	CThirdBMLaser();
	virtual void finaltick(float _DT);
	virtual void Enter();
	virtual void Exit();

	~CThirdBMLaser();
	CLONE(CThirdBMLaser);
};

