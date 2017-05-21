#include <cstdio>
#include "allegro5\allegro.h"
#include "GameManager.h"

int main(void) {
	CGameManager::Instance().Init(); // 게임 초기화
	CGameManager::Instance().Intro(); // 시작 화면
	CGameManager::Instance().Play(); // 게임 플레이
	return 0;
}