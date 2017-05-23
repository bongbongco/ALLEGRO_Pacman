#include "Node.h"


CNode *CNode::FindPath(int _startX, int _startY, int _targetX, int _targetY, bool _first) {
	m_openList = new CNode[kMax];
	m_closeList = new CNode **[kTileY + 1]; // Y
	for (int i = 0; i <= kTileY; i++) {
		m_closeList[i] = new CNode*[kTileX + 1]; // X
		for (int j = 0; j < kTileX; j++) {
			m_closeList[i][j] = nullptr;
		}
	}

		CNode *newNode = new CNode;

		_startX = _startX / kTileWidth; // 좌표/타일 너비(64)
		_startY = _startY / kTileHeight; // 좌표/타일 높이(64)
		_targetX = _targetX / kTileWidth;
		_targetY = _targetY / kTileHeight;

		m_startX = _startX;
		m_startY = _startY;
		m_targetX = _targetX;
		m_targetY = _targetY;

		newNode->m_g = 0; // 시작점에서 새로운 점까지의 거리
		newNode->m_h = 10 * (abs(_startX - _targetX) + abs(_startY - _targetY)); // 최종목적지까지 이동비용
		newNode->m_f = newNode->m_g + newNode->m_h; // 비용

		newNode->m_parent = NULL;
		newNode->m_x = _startX;
		newNode->m_y = _startY;

		m_openList[0].m_f = newNode->m_f;
		m_openList[0].m_parent = newNode;

	while (true) { // 길 찾기
		if (EmptyCheck() == true) { // OpenList가 비었다면
			return nullptr;
		}

		CNode *newParent = MinimumF(); // 최소값 F를 가지는 Node  
		Erase(newParent); // 선택된 노드를 OpenList에서 제거
		m_closeList[abs(newParent->m_y)][abs(newParent->m_x)] = newParent; // 선택된 Node를 CloseList에 삽입

		if (newParent->m_x == m_targetX && newParent->m_y == m_targetY) { // 목적지에 도달했다면
			delete m_openList;
			delete m_closeList;
			return newParent;
		}
		int movingX = newParent->m_x;
		int movingY = newParent->m_y;
		
		//N - 이동 가중치 10
		MakeNode(newParent, 10, movingX, movingY - 1);
		//E - 이동 가중치 10
		MakeNode(newParent, 10, movingX + 1, movingY);
		//S - 이동 가중치 10
		MakeNode(newParent, 10, movingX, movingY + 1);
		//W - 이동 가중치 10
		MakeNode(newParent, 10, movingX - 1, movingY);
	}
	return nullptr;
}
CNode *CNode::MinimumF() { // OpenList 최소 F 값
	int minimumValue = 999999;
	int minimumIndex;

	for (int i = 0; i < kMax; i++) {
		if ((m_openList[i].m_f < minimumValue) && (m_openList[i].m_f != NULL)) {
			minimumValue = m_openList[i].m_f;
			minimumIndex = i;
		}
	}
	return m_openList[minimumIndex].m_parent;
}
bool CNode::EmptyCheck() { // OpenList empty check
	for (int i = 0; i < kMax; i++) {
		if (m_openList[i].m_f != NULL) {
			return false;
		}
	}
	return true;
}

void CNode::Erase(CNode *_target) { // OpenList에서 제거
	for (int i = 0; i < kMax; i++) {
		if (m_openList[i].m_parent == _target) {
			m_openList[i].m_f = NULL;
			m_openList[i].m_parent = NULL;
			return;
		}
	}
	return;
}
bool CNode::InsertNode(CNode *_parent) { // True : OpenList, False : CloseList
	for (int i = 0; i < kMax; i++) {
		if (m_openList[i].m_f == NULL) {
			m_openList[i].m_f = _parent->m_f;
			m_openList[i].m_parent = _parent;
			return true;
		}
	}
	return false;
}
CNode *CNode::Search(int _x, int _y, bool _list) { // True : OpenList, False : CloseList
	if (_list == false) {
		if (m_closeList[_y][_x] != NULL) {
			return m_closeList[_y][_x];
		}
		return NULL;
	}
	else if (_list == true) {
		for (int i = 0; i < kMax; i++) {
			if (m_openList[i].m_f != NULL) {
				if (m_openList[i].m_parent->m_x == _x &&
					m_openList[i].m_parent->m_y == _y) {

					return m_openList[i].m_parent;
				}
			}
		}
		return NULL;
	}
	return NULL;

}
void CNode::MakeNode(CNode *_parent, int _movingCost, int _x, int _y) { // 부모인자로 노드 생성
	if (_x < 0 || _x >= kTileX) { // x축 최소, 최대 값 한정 
		return;
	}
	if (_y < 0 || _y >= kTileY) { // y축 최소, 최대 값 한정
		return;
	}

	if (m_blueprint[_y][_x] == kWall) { // 벽(갈 수 없음)
		return;
	}

	CNode *newNode = new CNode; // Node 셋팅

	newNode->m_parent = _parent;
	newNode->m_x = _x;
	newNode->m_y = _y;

	newNode->m_h = 10 * (abs(_x - m_targetX) + abs(_y - m_targetY));
	newNode->m_g = _parent->m_g + _movingCost;
	newNode->m_f = newNode->m_h + newNode->m_g;

	CNode *parent = Search(_x, _y, false); //CloseList 검색
	if (parent != NULL) {
		if (parent->m_f > newNode->m_f) {
			parent->m_f = newNode->m_f;
			parent->m_g = newNode->m_g;
			parent->m_h = newNode->m_h;
			parent->m_parent = newNode->m_parent;
		}
		delete newNode;
		return;
	}

	parent = Search(_x, _y, true); //OpenList 검색
	if (parent != NULL) {
		if (parent->m_f > newNode->m_f) {
			parent->m_f = newNode->m_f;
			parent->m_g = newNode->m_g;
			parent->m_h = newNode->m_h;
			parent->m_parent = newNode->m_parent;
		}
		delete newNode;
		return;
	}
	InsertNode(newNode); // OpenList에 삽입
	return;
}

void CNode::SetBlueprint(int **_bluePrint) {
	m_blueprint = _bluePrint;
}