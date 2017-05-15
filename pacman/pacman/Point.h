#pragma once
#include "Component.h"
#include <iostream>

class CPoint : public CComponent {
public:
	CPoint(CObject *_object) : CComponent(_object) {
	}

	virtual void Update() {}
	virtual void Render() {
		std::cout << "Point Render()" << std::endl;
	}
};