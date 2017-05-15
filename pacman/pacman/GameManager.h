#pragma once
#include <iostream>
#include <string>
#include "allegro5\allegro.h"
#include "Common.h"
#include "SceneManager.h"
#include "ControllManager.h"

class CGameManager {
private:
	const std::string kAllegroInitError;
	const std::string kAllegroCreateDisplayError;
	const std::string kAllegroCreateEventQueueError;
	const std::string kAllegroCreateTimerError;
	const std::string kAllegroInstallKeyboard;
	const double kFps;

	ALLEGRO_DISPLAY *m_display;
	ALLEGRO_EVENT_QUEUE *m_eventQueue;
	ALLEGRO_TIMER *m_timer;
	ALLEGRO_EVENT m_event;
	ALLEGRO_TIMEOUT m_timeout;
	bool m_whatHappen;
public:
	CSceneManager m_sceneManager;

	CGameManager():kAllegroInitError("Allegro 초기화 실패"),
		kAllegroCreateDisplayError("Allegro Display 생성 실패"),
		kAllegroCreateEventQueueError("Allegro Event 생성 실패"),
		kAllegroCreateTimerError("Allegro Timer 생성 실패"),
		kAllegroInstallKeyboard("Allegro Keyboard 설치 실패"),
		kFps(60) {
	
		m_display = NULL;
		m_eventQueue = NULL;
		m_timer = NULL;
	};

	void Init();
	void Play();
	CSceneManager *GetSceneManager() {
		return &m_sceneManager;
	}
};