#pragma once
#ifndef __BULLETPOOL__
#define __BULLETPOOL__
#include "Bullet.h"
#include <vector>
//#include <list>
class BulletPool
{
public:
	BulletPool(int);
	~BulletPool();

	Bullet* Spawn();
	void Despawn(Bullet*);
	void ResetAll();
	std::vector<Bullet*> all;
	std::vector<Bullet*> active;
	std::vector<bool> activeColliding;

	std::vector<Bullet*> inactive;
	
};
#endif /* defined (__BULLETPOOL__) */
