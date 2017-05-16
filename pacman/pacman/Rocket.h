#pragma once
#include "Common.h"
#include "Component.h"
#include "Transform.h"
#include "Object.h"
#include "Sprite.h"
#include "Solid.h"

class CRocket : public CComponent {//, public CSprite {
private:
	Direction m_direction;
	int m_label;
public : 
	CRocket(CObject *_object) : CComponent(_object) { //, CSprite(_object) {
		CTransform *transform = GetObject()->GetTransform();
		if (transform->x == 0) {
			transform->x = kDisplayWidth / 2 - 8;
		}
		if (transform->y == 0) {
			transform->y = kDisplayHeight / 2 + 8;
		}
	}

	virtual void Update();
	virtual void Render() {}
	void SetLabel(int _label) {
		m_label = _label;
	}

	int GetLabel() {
		return m_label;
	}

	void Move(int _x, int _y);
};

