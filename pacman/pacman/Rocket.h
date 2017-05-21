#pragma once
#include "Common.h"
#include "Component.h"
#include "Transform.h"
#include "Object.h"
#include "Sprite.h"
#include "Solid.h"
#include "Pika.h"
#include "Node.h"
#include <utility>


class CRocket : public CComponent {
private:                                                                                                                    
	Direction m_direction;
	CNode *m_telescope;
	int m_label;
	std::vector<CObject *> *m_otherObject;
	int m_speed;
	int m_prevX;
	int m_prevY;
public : 
	CRocket(CObject *_object) : CComponent(_object) {
		m_direction = E;
		m_speed = 1;
	}
	void SetVector(std::vector<CObject *> *_objects);
	void SetDirection(Direction _direction);
	Direction GetDirection();
	void SetNode(CNode *_telescope);
	virtual void Update();
	virtual void Render() {}
	void SetLabel(int _label) {
		m_label = _label;
	}
	int GetLabel() {
		return m_label;
	}
	void SetSpeed(int _speed);
	int Move(int _x, int _y);

	std::pair<int, int> GetPrevLocation();
};

