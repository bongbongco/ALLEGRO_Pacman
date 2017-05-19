#pragma once
#include "Common.h"
#include "Component.h"
#include "Transform.h"
#include "Object.h"
#include "Sprite.h"
#include "Solid.h"
#include "Pika.h"


class CRocket : public CComponent {
private:                                                                                                                    
	Direction m_direction;
	int m_label;
	std::vector<CObject *> *m_otherObject;
public : 
	CRocket(CObject *_object) : CComponent(_object) {
		
	}
	void SetVector(std::vector<CObject *> *_objects);
	void SetDirection(Direction _direction);

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

