#pragma once
#include "Component.h"
#include <iostream>
class CCollision : public CComponent {
public:
	CCollision(CObject *_object) : CComponent(_object) {}

	virtual void Update() {}
	virtual void Render() {
		std::cout << "Component Render()" << std::endl;
	}
};