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

	CNode *m_parent; // �θ��� ���
	int m_x, m_y; // ��ǥ
	int m_f; // ���� Ÿ�ϱ��� �� �̵� ���
	int m_g; // ��������� ���� ������ �̵� ���
	int m_h; // ���� ��Ʈ���� ���������� �̵� ���
	const int kMax = 1000;

	static CNode& Instance() {
		static CNode gInstance;
		return gInstance;
	}

	CNode *FindPath(int _startX, int _startY, int _endX, int _endY, bool _first = false);
	CNode *MinimumF(); // OpenList �ּ� F ��
	bool EmptyCheck(); // OpenList empty check
	void Erase(CNode *_target); // OpenList���� ����
	bool ClassifyNode(CNode *_p); // True : OpenList, False : CloseList
	CNode *Search(int _x, int _y, bool _list); // True : OpenList, False : CloseList
	void MakeNode(CNode *_parent, int _movingCost, int _x, int _y); // �θ����ڷ� ��� ����
};

class CMapManager {
private:
	std::ifstream m_mapFileIn; // �� ���� ���� ���� ����
	char m_tmp[kTileX + 1]; // �� ���� �迭
	int **m_blueprint; // ���赵
public:
	static CMapManager& Instance() {
		static CMapManager gInstance;
		return gInstance;
	}

	int** LoadLevel(const char *_mapFilePath);
	int DecodeScatch(char _scatch);
};