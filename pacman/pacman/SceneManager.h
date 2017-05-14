#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "allegro5\allegro_image.h"
#include "allegro5\allegro.h"
#include "Scene.h"
#include "MapManager.h"
#include "ImageManager.h"
#include "Common.h"
#include "Component.h"
#include "Object.h"
#include "Transform.h"
#include "Sprite.h"
#include "Collision.h"
#include "Pacman.h"
#include "Ghost.h"


class CSceneManager : public CScene {
private:
	const std::string kAllegroImageInitError;
	int **m_blueprint;
	ALLEGRO_BITMAP *m_tileImage;
	ALLEGRO_BITMAP *m_pointImage;
	ALLEGRO_BITMAP *m_pacmanImage;
	CPacman *m_pacman;
	//std::vector<CGhost*> m_ghosts;
public:
	std::vector<CObject *> m_objects;
	CSceneManager() :kAllegroImageInitError("Allegro �̹��� �߰� ��� �ʱ�ȭ ����") {};

	virtual void Init();
	virtual void Update();
	virtual void Render();

	int RemoveObject(CObject *_object);
};