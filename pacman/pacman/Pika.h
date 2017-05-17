#pragma once
#include "Common.h"
#include "Component.h"
#include "Object.h"
#include "Transform.h"
#include "ControllListener.h"
#include "ImageManager.h"
#include "Solid.h"
#include "Rocket.h"
#include "Speed.h"
#include "Point.h"
#include <vector>
#include <iostream>
#include "allegro5\allegro_image.h"


class CPika : public CComponent, public CControllListener {
private:
	int m_stunFrames;
	int m_speedMod;
	int m_speedBoostFrames;
	std::vector<CObject *> *m_otherObject;
public:
	int m_score;
	Direction m_direction;

	//std::vector<CObject *> *m_otherObject;

	CPika(CObject *_object) : CComponent(_object) {
		m_speedMod = 1;
		m_speedBoostFrames = 0;
		m_otherObject = nullptr;
		m_score = 0;
		m_stunFrames = 0;
		m_direction = E;
	}
	
	int Move(int _x, int _y);
	void SetVector(std::vector<CObject *> *_objects);

	void Boost(CSpeed *_speed);
	void Stun();

	virtual void Update();
	virtual void Render() {}

	virtual void Up() {
		m_direction = N;
	}
	virtual void Down() {
		m_direction = S;
	}
	virtual void Left() {
		m_direction = W;
	}
	virtual void Right() {
		m_direction = E;
	}
};