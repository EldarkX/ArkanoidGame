#pragma once

#include "Actors/Block.h"

enum class EBuffType
{
	None,
	BallBigSize,
	BallSmallSize,
	BallSpeedUp,
	BallSlowDown
};

class ABuffBlock : public Block
{
public:
	void	OnCollision(AActor* AnotherActor, CCollisionComponent* AnotherCollisionComponent) override;

private:
	EBuffType	BuffType = EBuffType::None;
};