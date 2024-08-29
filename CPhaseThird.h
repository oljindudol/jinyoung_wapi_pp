#pragma once
#include "CLevel.h"
class CPhaseThird :
	public CLevel
{
public:

	~CPhaseThird();
	virtual void init() override;
	virtual void enter() override;
	virtual void exit() override;

	virtual void tick() override;
};

