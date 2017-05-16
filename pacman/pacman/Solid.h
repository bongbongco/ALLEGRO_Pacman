#pragma once
#include "Component.h"
#include <iostream>
class CSolid : public CComponent {
public:
	CSolid(CObject *_object) : CComponent(_object) {}

	virtual void Update() {}
	virtual void Render() {}
};