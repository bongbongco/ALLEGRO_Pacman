#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_ttf.h"
#include "allegro5\allegro_image.h"
#include "allegro5\allegro.h"
#include "Scene.h"
#include "Common.h"
#include "Component.h"
#include "Object.h"
#include "Transform.h"
#include "Sprite.h"
#include "Solid.h"
#include "Rocket.h"
#include "Pika.h"


class CSceneManager : public CScene {
private:
	const std::string kAllegroImageInitError;
	int **m_blueprint;

	CPika *m_pika;
	std::vector<CRocket *> m_rockets;
	std::vector<const char *> m_rocketImageName;
public:
	std::vector<CObject *> m_objects;
	CSceneManager() :kAllegroImageInitError("Allegro 이미지 추가 기능 초기화 실패") {}

	static CSceneManager& Instance() {
		static CSceneManager gInstance;
		return gInstance;
	}

	virtual void Init();
	virtual void Update();
	virtual void Render();

	int RemoveObject(CObject *_object);
};