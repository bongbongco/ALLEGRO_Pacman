#pragma once
#include <vector>
#include <string>
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_ttf.h"


enum Direction {N, S, W, E}; // 방향 - 위, 아래, 왼쪽, 오른쪽
enum State {ZZZ, SPEED, NORMAL, GRACE}; // 상태 - 스턴, 부스터, 보통, 무적
const int kDisplayWidth = 1088; // 화면 가로 폭
const int kDisplayHeight = 704; // 화면 세로 폭
const int kTileX = 17; // 가로 타일 수
const int kTileY = 11; // 세로 타일 수
const int kTileWidth = 64; // 타일 넓이
const int kTileHeight = 64; // 타일 높이
const int kWall = 0; // 벽
const int kPoint = 1; // 포켓몬볼
const int kEmpty = 2; // 공백
const int kRocketNumber = 3; // 로켓단 수
const int kBoostMod = 4; // 부스터 속도
const int kBoostDuration = 1200; // 부스터 기간
const int kStunDuration = 300; // 스턴 기간