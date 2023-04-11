#pragma once

#include "Modules/ObjectModule/Object/Actor/SpriteActor.h"

class CCollisionComponent;
class CLinearMovementComponent;
class CPlayerController;

class APlayer : public ASpriteActor
{
public:
								APlayer();

	virtual void				Tick(float DeltaTime) override;

	CCollisionComponent*		GetCollisionComponent() const { return Collision; }
	CLinearMovementComponent*	GetMovementComponent() const { return MovementComponent; }
	CPlayerController*			GetPlayerController() const { return PlayerController; }

protected:
	CCollisionComponent*		Collision;
	CLinearMovementComponent*	MovementComponent;
	CPlayerController*			PlayerController;
private:
	float						InitSpeed = 500.f;
};