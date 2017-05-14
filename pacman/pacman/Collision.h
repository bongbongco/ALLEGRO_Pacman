#pragma once
#include "Component.h"

class CCollision : public CComponent {
public:
	CCollision(CObject *_object) : CComponent(_object) {}

	virtual void Update() {}
	virtual void Render() {}
};