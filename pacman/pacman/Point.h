#pragma once
#include "Component.h"
#include <iostream>

class CPoint : public CComponent {
public:
	bool state;
	CPoint(CObject *_object) : CComponent(_object) {
		state = true;
	}

	virtual void Update() {}
	virtual void Render() {}
};