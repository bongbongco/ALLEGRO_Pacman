#include <cstdio>
#include "allegro5\allegro.h"
#include "GameManager.h"

int main(void) {
	CGameManager GameManager;
	GameManager.Init(); // ���� �ʱ�ȭ
	GameManager.Play(); // ���� �÷���
	return 0;
}