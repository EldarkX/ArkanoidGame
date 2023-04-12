#pragma once

#include "Modules/ObjectModule/Object/Actor/SpriteActor.h"

class CCollisionComponent;
class AActor;

class ABlock : public ASpriteActor
{
public:
							ABlock();

	CCollisionComponent*	GetCollisionComponent() const {return Collision;}	
	virtual void			OnCollision(AActor* AnotherActor, CCollisionComponent* AnotherCollisionComponent);

	void					OnStartBeingPendingToKillCallback(AActor* Actor);

	virtual					~ABlock() {}

protected:
	CCollisionComponent*	Collision;
};