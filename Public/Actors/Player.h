#pragma once

#include "Modules/ObjectModule/Object/Actor/SpriteActor.h"

class CCollisionComponent;
class CLinearMovementComponent;
class CPlayerController;

class Player : public ASpriteActor
{
public:
								Player();

	virtual void				Tick(float DeltaTime) override;

	CCollisionComponent*		GetCollisionComponent() const { return Collision;}
	CLinearMovementComponent*	GetMovementComponent() const { return MovementComponent; }
	CPlayerController*			GetPlayerController() const { return PlayerController; }

protected:
	CCollisionComponent*		Collision;
	CLinearMovementComponent*	MovementComponent;
	CPlayerController*			PlayerController;
private:
	float						PlayerHalfWidth;
	float						PlayerHalfHeight;
};