#pragma once
#include "Common.h"
#include "Component.h"
#include "Transform.h"
#include "Object.h"
#include "Sprite.h"


class CRocket : public CSprite {
public : 
	CRocket(CObject *_object) : CSprite(_object) {
		CTransform *transform = GetObject()->GetTransform();
		if (transform->x == 0) {
			transform->x = kDisplayWidth / 2 - 8;
		}
		if (transform->y == 0) {
			transform->y = kDisplayHeight / 2 + 8;
		}
	}

	virtual void Update() {}
	//virtual void Render() {}
};

