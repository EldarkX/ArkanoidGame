#pragma once

#include "Modules/ObjectModule/Object/Actor/SpriteActor.h"
#include "Utils/Delegate/MulticastDelegate.h"

class CCollisionComponent;
class CLinearMovementComponent;

class ABall : public ASpriteActor
{
public:
									ABall();

	virtual void					Tick(float deltaTime) override;
	virtual void					OnCollision(class AActor* AnotherActor, CCollisionComponent* AnotherCollisionComponent);
	
	CLinearMovementComponent		*GetMovementComponent() const { return MovementComponent; }
	CCollisionComponent				*GetCollisionComponent() const { return Collision; }
	
	void							ResetBall();

	virtual							~ABall() {}
public:
	DelegateLib::MulticastDelegate1<ABall*>	mOnBallFallOut;
protected:							
	CLinearMovementComponent*	MovementComponent;
	CCollisionComponent*		Collision;
	
	float						InitSpeed = 400.f;

	bool						isCollided = false;
};									

