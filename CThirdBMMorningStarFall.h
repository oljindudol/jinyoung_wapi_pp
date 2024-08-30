#pragma once
#include "CState.h"
class CThirdBMMorningStarFall :
	public CState
{
	GENERATED_OBJECT(CState);
public:
	CThirdBMMorningStarFall();
	virtual void finaltick(float _DT);
	virtual void Enter();
	virtual void Exit();

	~CThirdBMMorningStarFall();
	CLONE(CThirdBMMorningStarFall);
};