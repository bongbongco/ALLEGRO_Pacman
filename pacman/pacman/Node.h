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
	CNode *m_parent; // �θ��� ���
	int m_x, m_y; // ��ǥ
	int m_f; // ���� Ÿ�ϱ��� �� �̵� ���
	int m_g; // ��������� ���� ������ �̵� ���
	int m_h; // ���� ��Ʈ���� ���������� �̵� ���
	const int kMax = 9999;
	Direction m_direction; // ����
	CNode *m_openList;// = new CNode;
	CNode ***m_closeList;// [kTileY + 1][kTileX + 1];

	CNode() {
		m_startX = 0, m_startY = 0, m_targetX = 0, m_targetY = 0;
		m_blueprint = nullptr;
		m_parent = nullptr; // �θ��� ���
		m_x = 0, m_y = 0; // ��ǥ
		m_f = 0; // ���� Ÿ�ϱ��� �� �̵� ���
		m_g = 0; // ��������� ���� ������ �̵� ���
		m_h = 0; // ���� ��Ʈ���� ���������� �̵� ���
		m_direction = N;
	}

	static CNode& Instance() {
		static CNode gInstance;
		return gInstance;
	}

	CNode *FindPath(int _startX, int _startY, int _endX, int _endY, bool _first = true);
	CNode *MinimumF(); // OpenList �ּ� F ��
	bool EmptyCheck(); // OpenList empty check
	void Erase(CNode *_target); // OpenList���� ����
	bool InsertNode(CNode *_p); // True : OpenList, False : CloseList
	CNode *Search(int _x, int _y, bool _list); // True : OpenList, False : CloseList
	void MakeNode(CNode *_parent, int _movingCost, int _x, int _y); // �θ����ڷ� ��� ����
	void SetBlueprint(int **_blueprint);
	Direction CNode::FindDirection(int _startX, int _startY, int _endX, int _endY, Direction _direction);
};
