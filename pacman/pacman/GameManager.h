#pragma once
#include "SceneManager.h"


class CGameManager {
private:
	// 제거 예정
	CGameManager(CGameManager const&);// 제거 예정
	void operator=(CGameManager const&);// 제거 예정

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

	static CGameManager& Instance() {
		static CGameManager gInstance;
		return gInstance;
	}

	CGameManager():kAllegroInitError("Allegro 초기화 실패"),
		kAllegroCreateDisplayError("Allegro Display 생성 실패"),
		kAllegroCreateEventQueueError("Allegro Event 생성 실패"),
		kAllegroCreateTimerError("Allegro Timer 생성 실패"),
		kAllegroInstallKeyboard("Allegro Keyboard 설치 실패"),
		kFps(60) {
	
		m_display = NULL;
		m_eventQueue = NULL;
		m_timer = NULL;
	}

	void Init();
	void Intro();
	void Play();
	void Retry();
	void End();
	CSceneManager *GetSceneManager() {
		return &m_sceneManager;
	}
};