#include "MapManager.h"


int **CMapManager::LoadLevel(const char *_mapFilePath) {
	try {
		m_mapFileIn.open(_mapFilePath); // �� ���� �б�
	}
	catch (const std::ifstream::failure& e) {
		std::cout << "Map ���� ���� ���� " << e.what() <<std::endl;
	}

	m_blueprint = new int *[kTileY + 1]; // ���赵 �迭
	for (int i = 0; i < kTileY; ++i) {
		m_blueprint[i] = new int[kTileX];

		if (!m_mapFileIn.eof()) {
			m_mapFileIn.getline(m_tmp, kTileX + 1); // �� ����ġ ���� ���� �� �б�
		}

		for (int j = 0; j < kTileX; ++j) {
			m_blueprint[i][j] = DecodeScatch(m_tmp[j]); // �� ����ġ�� ���� ���·� ��ȯ�Ͽ� ���赵�� ����
		}
	}
	return m_blueprint;
}

int CMapManager::DecodeScatch(char _scatch) {
	switch (_scatch) {
	case '=':
		return kWall; // ��
	case '.':
		return kPoint; // ����Ʈ
	case ' ':
		return kEmpty;  // ����
	default:
		return kEmpty;
	}
}

CNode *CNode::FindPath(int _startX, int _startY, int _endX, int _endY, bool _first) {
	if (_first == true) { // ������

		CNode *newNode = new CNode;

		m_startX = _startX;
		m_startY = _startY;
		m_endX = _endX;
		m_endY = _endY;

		newNode->m_g = 0;
		newNode->m_h = 10 * (abs(_startX - _endX) + abs(_startY - _endY)); // ����ź �Ÿ�
		newNode->m_f = newNode->m_g + newNode->m_h;

		newNode->m_parent = NULL;
		newNode->m_x = _startX;
		newNode->m_y = _startY;

		gOpenList[0].m_f = m_f;
		gOpenList[0].m_parent = newNode;
	}

	while (true) { // �� ã��
		if (EmptyCheck() == true) { // OpenList�� ����ٸ�
			return nullptr;
		}

		CNode *newParent = MinimumF(); // �ּҰ� F�� ������ Node  
		Erase(newParent);
		gCloseList[newParent->m_y][newParent->m_x] = newParent;

		if (newParent->m_x == m_endX && newParent->m_y == m_endY) { // �������� �����ߴٸ�
			return newParent;
		}
		int movingX = newParent->m_x;
		int movingY = newParent->m_y;

		MakeNode(newParent, 10, movingX, movingY - 1);
		//3��
		MakeNode(newParent, 10, movingX + 1, movingY);
		//6��
		MakeNode(newParent, 10, movingX, movingY + 1);
		//9��
		MakeNode(newParent, 10, movingX - 1, movingY);

		//2��
		MakeNode(newParent, 14, movingX + 1, movingY - 1);
		//5��
		MakeNode(newParent, 14, movingX + 1, movingY + 1);
		//8��
		MakeNode(newParent, 14, movingX - 1, movingY + 1);
		//11��
		MakeNode(newParent, 14, movingX - 1, movingY - 1);
	}
	return nullptr;
}
CNode *CNode::MinimumF() { // OpenList �ּ� F ��
	int minimumValue = 999999;
	int minimumIndex;

	for (int i = 0; i < kMax; i++) {
		if ((gOpenList[i].m_f < minimumValue) && (gOpenList[i].m_f != NULL)) {
			minimumValue = gOpenList[i].m_f;
			minimumIndex = i;
		}
	}
	return gOpenList[minimumIndex].m_parent;
}
bool CNode::EmptyCheck() { // OpenList empty check
	for (int i = 0; i < kMax; i++) {
		if (gOpenList[i].m_f != NULL) {
			return false;
		}
	}
	return true;
}

void CNode::Erase(CNode *_target) { // OpenList���� ����
	for (int i = 0; i < kMax; i++) {
		if (gOpenList[i].m_parent == _target) {
			gOpenList[i].m_f = NULL;
			gOpenList[i].m_parent = NULL;
			return;
		}
		return;
	}
}
bool CNode::ClassifyNode(CNode *_parent) { // True : OpenList, False : CloseList
	for (int i = 0; i < kMax; i++) {
		if (gOpenList[i].m_f == NULL) {
			gOpenList[i].m_f = _parent->m_f;
			gOpenList[i].m_parent = _parent;
			return true;
		}
	}
	return false;
}
CNode *CNode::Search(int _x, int _y, bool _list) { // True : OpenList, False : CloseList
	if (_list == false) {
		if (gCloseList[_y][_x] != NULL) {
			return gCloseList[_y][_x];
		}
		return NULL;
	}
	else if (_list == true) {
		for (int i = 0; i < kMax; i++) {
			if (gOpenList[i].m_f != NULL) {
				if (gOpenList[i].m_parent->m_x == _x &&
					gOpenList[i].m_parent->m_y == _y) {

					return gOpenList[i].m_parent;
				}
			}
		}
		return NULL;
	}
	return NULL;

}
void CNode::MakeNode(CNode *_parent, int _movingCost, int _x, int _y) { // �θ����ڷ� ��� ����
	int **m_blueprint = CMapManager::Instance().LoadLevel("level1.txt"); // ���赵 ����

	if (_x < 0 || _x > kTileX) { // x�� �ּ�, �ִ� �� ���� 
		return;
	}
	if (_y < 0 || _y > kTileY) { // y�� �ּ�, �ִ� �� ����
		return;
	}

	if (m_blueprint[_y][_x] == kWall) { // ��(�� �� ����)
		return;
	}

	CNode *newNode = new CNode; // Node ����

	newNode->m_parent = _parent;
	newNode->m_x = _x;
	newNode->m_y = _y;

	newNode->m_h = 10 * (abs(_x - m_endX) + abs(_y - m_endY));
	newNode->m_g = _parent->m_g + _movingCost;
	newNode->m_f = newNode->m_h + newNode->m_g;

	CNode *parent = Search(_x, _y, false); //CloseList �˻�
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

	parent = Search(_x, _y, true); //OpenList �˻�
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

	ClassifyNode(newNode); // OpenList�� �з�
	return;
}