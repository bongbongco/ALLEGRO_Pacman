#pragma once
#include <vector>
#include <string>
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_ttf.h"


enum Direction {N, S, W, E};
enum State {ZZZ, SPEED, NORMAL};
const int kDisplayWidth = 1088; // ȭ�� ���� ��
const int kDisplayHeight = 704; // ȭ�� ���� ��
const int kTileX = 16; // ���� Ÿ�� ��
const int kTileY = 11; // ���� Ÿ�� ��
const int kTileWidth = 64; // Ÿ�� ����
const int kTileHeight = 64; // Ÿ�� ����
const int kWall = 0; // ��
const int kPoint = 1; // ���ϸ�
const int kEmpty = 2; // ����
const int kRocketNumber = 3; // ���ϴ� ��
const int kBoostMod = 2;
const int kBoostDuration = 1200;
const int kStunDuration = 200;