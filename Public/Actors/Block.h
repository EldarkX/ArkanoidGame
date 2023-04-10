#pragma once

#include "Modules/ObjectModule/Object/Actor/SpriteActor.h"

class CCollisionComponent;
class AActor;

class Block : public ASpriteActor
{
public:
							Block();

	virtual void			OnCollision(AActor* AnotherActor, CCollisionComponent* AnotherCollisionComponent);
	CCollisionComponent*	GetCollisionComponent() const {return Collision;}	

	virtual					~Block() {}

protected:
	CCollisionComponent*	Collision;
};