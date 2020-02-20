#include "GameObject.h"
std::list<GameObject*>  GameObject::gameObjectsActive;
GameObject::GameObject()
{

	gameObjectsActive.push_front(this);
	
}

void GameObject::Update()
{
}

void GameObject::PosUpdate()
{
}

std::list<GameObject*> GameObject::GetAllGameObjects()
{
	return gameObjectsActive;
}
