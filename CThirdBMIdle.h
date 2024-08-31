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
	void ActivatePower();

	class CBlackMage3* m_pBlackMage3 = nullptr;

	~CThirdBMIdle();
	CLONE(CThirdBMIdle);
};

