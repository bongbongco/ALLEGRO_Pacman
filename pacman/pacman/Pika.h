#pragma once
#include "Common.h"
#include "Component.h"
#include "Object.h"
#include "Transform.h"
#include "ControllListener.h"
#include "ImageManager.h"
#include "MapManager.h"
#include "Solid.h"
#include "Rocket.h"
#include "Speed.h"
#include "Point.h"
#include "Node.h"
#include <vector>
#include <iostream>
#include <string>
#include "allegro5\allegro_image.h"
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_ttf.h"


class CPika : public CComponent, public CControllListener {
private:
	int m_stunFrames;
	int m_speedMod;
	int m_speedBoostFrames;
	int m_graceFrames;
	std::vector<CObject *> *m_otherObject;
	bool m_stunFlag;
	bool m_boostFlag;
	int m_life;
public:
	int m_score;
	Direction m_direction;

	CPika(CObject *_object) : CComponent(_object) {
		m_speedMod = 2;
		m_speedBoostFrames = 0;
		m_otherObject = nullptr;
		m_score = 0;
		m_stunFrames = 0;
		m_graceFrames = 0;
		m_direction = W;
		m_boostFlag = false;
		m_stunFlag = false;
		m_life = 3;
	}
	
	int Move(int _x, int _y);
	void SetVector(std::vector<CObject *> *_objects);

	void StateUpdate(State _state);
	void Boost();
	void Stun();
	void StageClear();

	void SetDirectionRocket(int _x, int _y);

	void HealthCheck();

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