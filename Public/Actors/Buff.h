#pragma once

#include "Modules/ObjectModule/Object/Actor/SpriteActor.h"
#include "Core/BuffManager.h"

class CCollisionComponent;
class CLinearMovementComponent;

class ABuff : public ASpriteActor
{
public:
								ABuff();

	virtual void				Tick(float deltaTime) override;

	void						SetBuffType(EBuffType newBuffType);
	EBuffType					GetBuffType() const { return BuffType; }

	CCollisionComponent*		GetCollisionComponent() const { return Collision; }
	CLinearMovementComponent*	GetMovementComponent() const { return MovementComponent; }

	virtual void				OnCollision(class AActor* AnotherActor, class CCollisionComponent* AnotherCollisionComponent);
protected:
	CCollisionComponent*		Collision;
	CLinearMovementComponent*	MovementComponent;
private:
	float						InitSpeed = 150.f;
	EBuffType					BuffType = EBuffType::None;

};
