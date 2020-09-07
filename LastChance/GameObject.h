#pragma once
class GameObject
{
public:
	virtual void Draw() = 0;
	virtual void Update(unsigned int delta) = 0;
};

