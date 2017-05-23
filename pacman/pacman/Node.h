#pragma once
#include "Common.h"
#include "MapManager.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <cmath>

class CNode {
public:
	int m_startX, m_startY, m_targetX, m_targetY;
	int **m_blueprint;
	CNode *m_parent; // 부모의 노드
	int m_x, m_y; // 좌표
	int m_f; // 현재 타일까지 총 이동 비용
	int m_g; // 출발점부터 현재 노드까지 이동 비용
	int m_h; // 현재 노트부터 목적지까지 이동 비용
	const int kMax = 9999;
	Direction m_direction; // 방향
	CNode *m_openList;// = new CNode;
	CNode ***m_closeList;// [kTileY + 1][kTileX + 1];

	CNode() {
		m_startX = 0, m_startY = 0, m_targetX = 0, m_targetY = 0;
		m_blueprint = nullptr;
		m_parent = nullptr; // 부모의 노드
		m_x = 0, m_y = 0; // 좌표
		m_f = 0; // 현재 타일까지 총 이동 비용
		m_g = 0; // 출발점부터 현재 노드까지 이동 비용
		m_h = 0; // 현재 노트부터 목적지까지 이동 비용
		m_direction = N;
	}

	static CNode& Instance() {
		static CNode gInstance;
		return gInstance;
	}

	CNode *FindPath(int _startX, int _startY, int _endX, int _endY, bool _first = true);
	CNode *MinimumF(); // OpenList 최소 F 값
	bool EmptyCheck(); // OpenList empty check
	void Erase(CNode *_target); // OpenList에서 제거
	bool InsertNode(CNode *_p); // True : OpenList, False : CloseList
	CNode *Search(int _x, int _y, bool _list); // True : OpenList, False : CloseList
	void MakeNode(CNode *_parent, int _movingCost, int _x, int _y); // 부모인자로 노드 생성
	void SetBlueprint(int **_blueprint);
	Direction CNode::FindDirection(int _startX, int _startY, int _endX, int _endY, Direction _direction);
};
