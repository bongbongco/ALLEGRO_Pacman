#include <cstdio>
#include "allegro5\allegro.h"
#include "GameManager.h"

int main(void) {
	CGameManager GameManager;
	GameManager.Init(); // 게임 초기화
	GameManager.Play(); // 게임 플레이
	return 0;
}