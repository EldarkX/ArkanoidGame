#pragma once

#include "Modules/ObjectModule/Object/Actor/SpriteActor.h"
#include "BuffBlock.h"

class CCollisionComponent;
class CLinearMovementComponent;

class ABuff : public ASpriteActor
{

public:

								ABuff();

	void						SetBuffType(EBuffType newBuffType);
	EBuffType					GetBuffType() const { return BuffType; }

	virtual void				OnCollision(class AActor* AnotherActor, class CCollisionComponent* AnotherCollisionComponent);

	CCollisionComponent*		Collision;
	CLinearMovementComponent*	MovementComponent;

protected:

	virtual void				Tick(float deltaTime) override;

private:

	EBuffType					BuffType = EBuffType::BallBigSize;
};