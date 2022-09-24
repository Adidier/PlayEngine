#pragma once
class GameObject
{
public:
	int id = 0;
	virtual void Draw() = 0;
	virtual void Update(unsigned int delta) = 0;
	virtual void OnTriggerEnter(void *ptr) = 0;
};

