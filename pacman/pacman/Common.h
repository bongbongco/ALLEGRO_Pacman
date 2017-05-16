#pragma once
#include <vector>
#include <string>

enum Direction {N, S, W, E};
const int kDisplayWidth = 960; // ȭ�� ���� ��
const int kDisplayHeight = 640; // ȭ�� ���� ��
const int kTileX = 15; // ���� Ÿ�� ��
const int kTileY = 10; // ���� Ÿ�� ��
const int kTileWidth = 64; // Ÿ�� ����
const int kTileHeight = 64; // Ÿ�� ����
const int kWall = 0; // ��
const int kPoint = 1; // ���ϸ�
const int kEmpty = 2; // ����
const int kRocketNumber = 3; // ���ϴ� ��
const int kBoostMod = 2;
const int kBoostDuration = 120;
const int kStunDuration = 45;
