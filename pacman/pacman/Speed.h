#pragma once
#include "Common.h"
#include "Component.h"
#include <iostream>
class CSpeed : public CComponent{
public:
	bool state;
	int m_speed;
	int m_duration;

	CSpeed(CObject *_object) : CComponent(_object) {
		state = true;
		m_speed = kBoostMod;
		m_duration = kBoostDuration;
	}

	int GetSpeed() {
		return m_speed;
	}

	virtual void Update() {}
	virtual void Render() {}
};