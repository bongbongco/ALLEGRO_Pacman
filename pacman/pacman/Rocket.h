#pragma once
#include "Common.h"
#include "Component.h"
#include "Transform.h"
#include "Object.h"
#include "Sprite.h"
#include "Solid.h"
#include "Pika.h"


class CRocket : public CComponent {//, public CSprite {
private:
	Direction m_direction;
	int m_label;
	std::vector<CObject *> *m_otherObject;
public : 
	CRocket(CObject *_object) : CComponent(_object) { //, CSprite(_object) {
		
		/*
		CTransform *transform = GetObject()->GetTransform();

		if (transform->x == 0) {
			transform->x = kDisplayWidth / 2 - 8;
		}
		if (transform->y == 0) {
			transform->y = kDisplayHeight / 2 + 8;
		}
		*/
	}
	void SetVector(std::vector<CObject *> *_objects);

	virtual void Update();
	virtual void Render() {}
	void SetLabel(int _label) {
		m_label = _label;
	}

	int GetLabel() {
		return m_label;
	}

	int Move(int _x, int _y);
};

