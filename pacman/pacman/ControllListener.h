#pragma once

class CControllListener {
public:
	virtual void Up() = 0;
	virtual void Down() = 0;
	virtual void Left() = 0;
	virtual void Right() = 0;

	virtual ~CControllListener() {}
};