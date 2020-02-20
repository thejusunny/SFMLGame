#pragma once
#include <SFML\Graphics.hpp>
#include<list>
class GameObject
{
private:
	static std::list<GameObject*> gameObjectsActive;

public:
	GameObject();
	void Update();
	void PosUpdate();
	static std::list<GameObject*> GetAllGameObjects();

};

