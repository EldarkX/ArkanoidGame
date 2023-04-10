#pragma once

#include "Modules/ObjectModule/Object/Actor/SpriteActor.h"
#include "Utils/Delegate/MulticastDelegate.h"

class CCollisionComponent;
class CLinearMovementComponent;

class Ball : public ASpriteActor
{
public:
									Ball();

	virtual void					Tick(float deltaTime) override;
	virtual void					OnCollision(class AActor* AnotherActor, CCollisionComponent* AnotherCollisionComponent);
	
	CLinearMovementComponent		*GetMovementComponent() const { return MovementComponent; }
	CCollisionComponent				*GetCollisionComponent() const { return Collision; }
	
	virtual							~Ball() {}
public:
	DelegateLib::MulticastDelegate1<Ball*>	mOnBallFallOut;
protected:							
	CLinearMovementComponent*	MovementComponent;
	CCollisionComponent*		Collision;
									
	bool						isCollided = false;
};									

