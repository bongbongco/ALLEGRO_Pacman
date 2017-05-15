#pragma once
#include "Common.h"
#include "Component.h"
#include <iostream>
class CSpeed : public CComponent{
public:
	int m_speed;
	int m_duration;

	CSpeed(CObject *_object) : CComponent(_object) {
		m_speed = kBoostMod;
		m_duration = kBoostDuration;
	}

	virtual void Update() {}
	virtual void Render() {}
};