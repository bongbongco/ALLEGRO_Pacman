#include <cstdio>
#include "allegro5\allegro.h"
#include "GameManager.h"

int main(void) {
	CGameManager::Instance().Init(); // ���� �ʱ�ȭ
	CGameManager::Instance().Intro(); // ���� ȭ��
	CGameManager::Instance().Play(); // ���� �÷���
	return 0;
}