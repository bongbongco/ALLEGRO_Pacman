#pragma once

class CControllListener {
public:
	virtual void Up() {}
	virtual void Down() {}
	virtual void Left() {}
	virtual void Right() {}

	virtual ~CControllListener() {}
};