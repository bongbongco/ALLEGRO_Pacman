#pragma once
#include "allegro5\allegro.h"
#include "Common.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

class CNode {
public:
	int m_startX, m_startY, m_endX, m_endY;

	CNode *m_parent; // 부모의 노드
	int m_x, m_y; // 좌표
	int m_f; // 현재 타일까지 총 이동 비용
	int m_g; // 출발점부터 현재 노드까지 이동 비용
	int m_h; // 현재 노트부터 목적지까지 이동 비용
	const int kMax = 1000;

	static CNode& Instance() {
		static CNode gInstance;
		return gInstance;
	}

	CNode *FindPath(int _startX, int _startY, int _endX, int _endY, bool _first = false);
	CNode *MinimumF(); // OpenList 최소 F 값
	bool EmptyCheck(); // OpenList empty check
	void Erase(CNode *_target); // OpenList에서 제거
	bool ClassifyNode(CNode *_p); // True : OpenList, False : CloseList
	CNode *Search(int _x, int _y, bool _list); // True : OpenList, False : CloseList
	void MakeNode(CNode *_parent, int _movingCost, int _x, int _y); // 부모인자로 노드 생성
};

class CMapManager {
private:
	std::ifstream m_mapFileIn; // 맵 설계 파일 읽을 변수
	char m_tmp[kTileX + 1]; // 맵 가로 배열
	int **m_blueprint; // 설계도
public:
	static CMapManager& Instance() {
		static CMapManager gInstance;
		return gInstance;
	}

	int** LoadLevel(const char *_mapFilePath);
	int DecodeScatch(char _scatch);
};