#pragma once

#include "Modules/ObjectModule/Object/Actor/SpriteActor.h"

class CCollisionComponent;
class AActor;

class ABlock : public ASpriteActor
{
public:
							ABlock();

	virtual void			OnCollision(AActor* AnotherActor, CCollisionComponent* AnotherCollisionComponent);
	CCollisionComponent*	GetCollisionComponent() const {return Collision;}	

	virtual					~ABlock() {}

protected:
	CCollisionComponent*	Collision;
};